/************
Autor:      CodeSeekerLabs

Projekt:    Bibliothek
            Ein Programm zur Verwaltung einer Bibliothek mit zurgriff auf eine Datenbank

Klasse:     UserDialog
            Erstellt das Fenster mit dem Benutzer interagieren können

Datum:      10.09.2024
*************/

#include "userdialog.h"
#include "ui_userdialog.h"

#include "itemcategory.h"

#include <QtSql>
#include <QTableView>

UserDialog::UserDialog(const QString& memid, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserDialog)
{
    ui->setupUi(this);

    this->bookModel=nullptr;
    this->loanModel=nullptr;
    this->tmodel=nullptr;



    //Verbindung zur Datenbank herstellen
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Bibliothek");
    db.setUserName("root");
    db.setPassword("");// Passwort eintragen

    //Verbindung öffnen
    if(!db.open()){
        //Wenn Verbinfung nicht göffnet werden kann, fehler anzeigen
        qDebug()<<"Can't open Database: \"Bibliothek\" \n"
               <<db.lastError().text();
    }else{
        qDebug()<<"Opened Database: \"Bibliothek\" successfully";
    }


    //Benutzer ID testen
    //Dazu in einer query abfragen nach Benutzer ID suchen
    QSqlQuery query;
    query.prepare("SELECT * FROM BibMem WHERE Member_ID = :id");
    query.bindValue(":id", memid);

    //query ausführen
    if (!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
    } else {
        //wenn .next()=true dann ist ID vorhanden
        if(query.next()){
            qDebug()<<"ID gefunden";
            this->memid=memid;//ID kann gesetzt werden
            ui->tabWidget->setTabText(0,query.value("Last_Name").toString());//Tab überschrift wird auf Nachnamen gesetzt
        }else{
            //sonst wird Datenbank geschlossen und eine Fehlermeldung erzeugt
            db.close();
            qDebug()<<"ID NOT FOUND; Closed Database";
            throw std::invalid_argument("ID NOT FOUND");
        }

    }

    //Methoden um inhalt der Tabs zu erzeugen
    this->getUser();

    this->getBooks();

    this->getLoans();

}

UserDialog::~UserDialog()
{
    delete ui;
    delete this->bookModel;
    delete this->loanModel;
    delete this->tmodel;
    db.close();
    qDebug()<<"Closed Database: \"Bibliothek\" successfully";
}


/*
 * Fragt die Benutzerdaten ab und zeigt diese an
 *
*/
void UserDialog::getUser(){

    //in BibMem nach Beutzer suchen
    QSqlQuery getUser;
    getUser.prepare("SELECT * FROM BibMem WHERE Member_ID = :memid");
    getUser.bindValue(":memid", this->memid);

    //query ausführen
    if(getUser.exec()){
        //Benutzerdaten anzeigen
        getUser.next();
        ui->labelMemID->setText(getUser.value("Member_ID").toString());
        ui->labelFName->setText(getUser.value("First_Name").toString());
        ui->labelLName->setText(getUser.value("Last_Name").toString());
        ui->labelPhone->setText(getUser.value("Phone_Num").toString());
        ui->labelEMail->setText(getUser.value("Email").toString());
        ui->labelStreet->setText(getUser.value("Street").toString());
        ui->labelPCode->setText(getUser.value("Post_Code").toString());
        ui->labelCity->setText(getUser.value("City").toString());

    }else{
        qDebug() << "Query Error:" << getUser.lastError().text();
    }

}


/*
 * Fragt die geliehen Bücher ab und zeigt diese an
 *
*/
void UserDialog::getLoans(){

    //Query string erstellen
    //alle geliehenen Bücher des Nutzers mit weieren Buchdaten sollen angezeigt werden
    QString queryStr = QString("SELECT Loans.BookID,\n"
                               "Loans.Loan_Date AS Geliehen_Am,\n"
                               "Loans.Return_Date AS Zurück_Am,\n"
                               "Book.Title,\n"
                               "Book.Author AS Autor,\n"
                               "Book.ISBN,\n"
                               "Book.Year_Pub AS Erschienen_Am,\n"
                               "Book.Category AS Kategorie\n"
                               "FROM Loans\n"
                               "INNER JOIN Book ON Loans.BookID = Book.Book_ID\n"
                               "WHERE Loans.MemID = '%1'").arg(this->memid);

    //Modell erstellen
    delete this->loanModel;
    loanModel = new QSqlQueryModel();
    loanModel->setQuery(queryStr, db);

    // Fehlerbehandlung für die Abfrage
    if (loanModel->lastError().isValid()) {
        //Wenn Abfrage fehlschlägt wird methode beendet
        qDebug() << "Fehler bei der Abfrage:" << loanModel->lastError().text();
        return;
    }

    //Modell in der TableView anzeigen
    ui->tableLoans->setEditTriggers(QAbstractItemView::NoEditTriggers);//die View als Nicht bearbeitbar setzen
    ui->tableLoans->setModel(loanModel);//bind model to QTableView
    ui->tableLoans->show();
}


/*
 * Fragt alle Bücher ab und zeigt diese an
 *
*/
void UserDialog::getBooks(){
    //alle Bücher anzeigen
    QString queryStr = QString("SELECT * FROM Book");

    //Modell erstellen
    delete this->bookModel;
    bookModel = new QSqlQueryModel();
    bookModel->setQuery(queryStr, db);

    //Modell in der View anzeigen
    ui->tableBooks->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableBooks->setModel(bookModel);//bind model to QTableView
    ui->tableBooks->show();
}

/*
 * Erstellt Filter für die Anzeige der Bücher
 *
*/
void UserDialog::loadFilters(){
    bool setYear=false;
    bool setCategory=false;
    bool setAuthor=false;
    bool setTitle=false;

    //ein Modell erstellen und alle Bücher anzeigen
    delete this->tmodel;
    tmodel = new QSqlTableModel(this,db);
    tmodel->setTable("Book");
    QString filter ="";//Filter String erstellen

    //Wenn Elektrotechnik gesetzt ist
    if(ui->radBtnElek->isChecked()){
        setCategory=true;//eine Kategorie wurde gesetzt
        //Dem Filter wird die Kategorie Elektrotechnik hinzugefügt
        filter=filter+QString("Category = %1").arg(static_cast<int>(ItemCategory::Cat::Elektrotechnik));
        qDebug()<<"Set Filter: \"Elektrotechnik\" ";
    }

    //Wenn Maschinenbau gesetzt ist
    if(ui->radBtnMechan->isChecked()){
        //Wenn bereits eine Kategorie gestzt wurde
        //sollen diese mit OR zusammengefügt werden, sodass alle gesetzten Kategorien gesucht werden
        if(setCategory){
            filter=filter+" OR ";
        }

        setCategory=true;//eine Kategorie wurde gesetzt
        //Dem Filter wird die Kategorie Maschinenbau hinzugefügt
        filter=filter+QString("Category = %1").arg(static_cast<int>(ItemCategory::Cat::Maschinenbau));
        qDebug()<<"Set Filter: \"Maschinenbau\" ";
    }

    //Wenn Informatik gesetzt ist
    if(ui->radBtnInfo->isChecked()){
        //Wenn bereits eine Kategorie gestzt wurde
        //sollen diese mit OR zusammengefügt werden, sodass alle gesetzten Kategorien gesucht werden
        if(setCategory){
            filter=filter+" OR ";
        }

        setCategory=true;//eine Kategorie wurde gesetzt
        //Dem Filter wird die Kategorie informatik hinzugefügt
        filter=filter+QString("Category = %1").arg(static_cast<int>(ItemCategory::Cat::Informatik));
        qDebug()<<"Set Filter: \"Informatik\" ";
    }

    //Wenn BWL gesetzt ist
    if(ui->radBtnBwl->isChecked()){
        //Wenn bereits eine Kategorie gestzt wurde
        //sollen diese mit OR zusammengefügt werden, sodass alle gesetzten Kategorien gesucht werden
        if(setCategory){
            filter=filter+" OR ";
        }

        setCategory=true;//eine Kategorie wurde gesetzt
        //Dem Filter wird die Kategorie BWL hinzugefügt
        filter=filter+QString("Category = %1").arg(static_cast<int>(ItemCategory::Cat::Betriebswirtschaft));
        qDebug()<<"Set Filter: \"Betriebswirtschaft\" ";
    }

    //Wenn Rechtswiss. gesetzt ist
    if(ui->radBtnLaw->isChecked()){
        //Wenn bereits eine Kategorie gestzt wurde
        //sollen diese mit OR zusammengefügt werden, sodass alle gesetzten Kategorien gesucht werden
        if(setCategory){
            filter=filter+" OR ";
        }

        setCategory=true;//eine Kategorie wurde gesetzt
        //Dem Filter wird die Kategorie Rechtswissenschaften hinzugefügt
        filter=filter+QString("Category = %1").arg(static_cast<int>(ItemCategory::Cat::Rechtswissenschaften));
        qDebug()<<"Set Filter: \"Rechtswissenschaften\" ";
    }


    //Weitere Filter die mit UND Verknüpft werden

    //Wenn ein Jahrgang ausgewählt wurde
    if(ui->lineYearFilter->text().toInt()>0){
        //Wenn bereits eine Kategorie gestzt wurde
        //sollen diese mit AND zusammengefügt werden, sodass allen gesetzten Kategorien UND dem Jahr gesucht wird
        if(setCategory){
            filter="("+filter+") AND ";
        }

        setYear=true;//Jahrgang gesetzt
        filter=filter+QString("Year_Pub = %1").arg(ui->lineYearFilter->text().toInt());
    }


    //Wenn ein Autor ausgewählt wurde
    if(ui->lineAuthorFilter->text()!=""){
        //Wenn bereits eine Kategorie oder das Jahr gesetzt wurde
        //sollen diese mit AND zusammengefügt werden, sodass nach allen gesetzten Kategorien UND dem Jahr UND dem Autor gesucht wird
        if(setCategory||setYear){
            filter="("+filter+") AND ";
        }

        setAuthor=true;//Autor gesetzt
        filter=filter+QString("Author LIKE '%%1%'").arg(ui->lineAuthorFilter->text());
    }

    //Wenn ein Titel ausgewählt wurde
    if(ui->lineTitelFilter->text()!=""){
        //Wenn bereits eine Kategorie oder das Jahr oder der Autor gesetzt wurde
        //sollen diese mit AND zusammengefügt werden, sodass nach allen gesetzten Kategorien
        //UND dem Jahr UND dem Autor UND dem Titel gesucht wird
        if(setCategory||setYear||setAuthor){
            filter="("+filter+") AND ";
        }

        setTitle=true;//Titel gesetzt
        filter=filter+QString("Title LIKE '%%1%'").arg(ui->lineTitelFilter->text());
    }

    //Wenn ein Verlag ausgewählt wurde
    if(ui->linePublFilter->text()!=""){
        //Wenn bereits eine Kategorie oder das Jahr oder der Autor oder der Titel gesetzt wurde
        //sollen diese mit AND zusammengefügt werden, sodass nach allen gesetzten Kategorien
        //UND dem Jahr UND dem Autor UND dem Titel UND dem Verlag gesucht wird
        if(setCategory||setYear||setAuthor||setTitle){
            filter="("+filter+") AND ";
        }
        
        filter=filter+QString("Publisher LIKE '%%1%'").arg(ui->linePublFilter->text());
    }




    tmodel->setFilter(filter);//Filter setzten
    tmodel->select();//Ergebnis auswählen

    //Ergebnis anzeigen in TableView
    ui->tableBooks->setEditTriggers(QAbstractItemView::NoEditTriggers);// nicht bearbeitbar
    ui->tableBooks->setModel(tmodel);
    ui->tableBooks->show();
}







