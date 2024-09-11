/************
Autor:      CodeSeekerLabs

Projekt:    Bibliothek
            Ein Programm zur Verwaltung einer Bibliothek mit zurgriff auf eine Datenbank

Klasse:     AdiminDialog
            Erstellt das Fenster mit dem die Verwaltung interagieren kann

Datum:      10.09.2024
*************/

#include "admindialog.h"
#include "ui_admindialog.h"

#include "itemcategory.h"
#include "itemchangedialog.h"

#include <QMessageBox>

AdminDialog::AdminDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminDialog)
{
    ui->setupUi(this);

    this->qmodel=nullptr;
    this->tmodel=nullptr;

    //Verbindung zur Datenbank herstellen
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("Bibliothek");
    db.setUserName("root");
    db.setPassword("");//Passwort eintragen

    //Verbindung öffnen
    if(!db.open()){
        //Fehler anzeigen, wenn Verbindung nicht göffnet werden kann
        qDebug()<<"Can't open Database: \"Bibliothek\" \n"
                 <<db.lastError().text();
    }else{
        qDebug()<<"Opened Database: \"Bibliothek\" successfully";
    }

    ui->stackedWidgetFilter->hide();//Filter Widget verstecken


    //Kategorien für die Auswahlboxen erstellen und setzen
    ui->boxType->addItem("Elektrotechnik", QVariant::fromValue(ItemCategory::Cat::Elektrotechnik));
    ui->boxType->addItem("Maschinenbau", QVariant::fromValue(ItemCategory::Cat::Maschinenbau));
    ui->boxType->addItem("Informatik", QVariant::fromValue(ItemCategory::Cat::Informatik));
    ui->boxType->addItem("BWL", QVariant::fromValue(ItemCategory::Cat::Betriebswirtschaft));
    ui->boxType->addItem("Rechtswiss", QVariant::fromValue(ItemCategory::Cat::Rechtswissenschaften));

}

AdminDialog::~AdminDialog()
{
    delete ui;
    delete this->qmodel;
    delete this->tmodel;
    db.close();
    qDebug()<<"Closed Database: \"Bibliothek\" successfully";

}


/*
 * zeigt Startbildschirm an
 *
*/
void AdminDialog::showHome(){

    ui->stackedWidgetFilter->hide();
    ui->stackedWidget->setCurrentWidget(ui->pageHome);

}


/*
 * zeigt Fenster zum Bearbeiten von Nutzerdaten an
 *
*/
void AdminDialog::editUser(){

    ui->stackedWidgetFilter->hide();
    ui->stackedWidget->setCurrentWidget(ui->pageNewUser);

}


/*
 * Ein neuer Benutzer wird in die Datenbank eingefügt
 *
*/
void AdminDialog::addUser(){
    //query erstellen
    // neuen Benutzer in BibMem einfügen
    QSqlQuery query;
    query.prepare("INSERT INTO BibMem (Member_ID,First_Name,Last_Name,Phone_Num,Street,Post_Code,City,Email) VALUES (:id, :fn, :ln, :pn, :s, :pc, :ci, :em)");
    query.bindValue(":id", ui->lineNewNum->text());
    query.bindValue(":fn", ui->lineNewFirstName->text());
    query.bindValue(":ln", ui->lineNewLastName->text());
    query.bindValue(":pn", ui->lineNewPhone->text());
    query.bindValue(":s", ui->lineNewStreet->text());
    query.bindValue(":pc", ui->lineNewPostCode->text());
    query.bindValue(":ci", ui->lineNewCity->text());
    query.bindValue(":em", ui->lineNewEMail->text());

    //Dialog mit Warnung erzeugen
    QMessageBox::StandardButton reply;
    //Im Dialog die eingegebenen Benutzeraten anzeigen lassen
    reply = QMessageBox::question(this, "Bestätigung", "Achtung! \n\n"
                                                       "Sie Fügen einen neuen Datansatz hinzu.\n"
                                                       "Bitte Überprüfen Sie die eingaben:\n\n"
                                                       "Benutzer ID: "+ui->lineNewNum->text()+"\n"
                                                       "Vorname: "+ui->lineNewFirstName->text()+"\n"
                                                       "Nachname: "+ui->lineNewLastName->text()+"\n"
                                                       "Telefon: "+ui->lineNewPhone->text()+"\n"
                                                       "Straße: "+ui->lineNewStreet->text()+"\n"
                                                       "PLZ: "+ui->lineNewPostCode->text()+"\n"
                                                       "Ort: "+ui->lineNewCity->text()+"\n"
                                                       "E-Mail: "+ui->lineNewEMail->text()+"\n"
                                                       "\n\n\n"
                                                       "Möchten Sie wirklich fortfahren?",
                                  QMessageBox::Yes | QMessageBox::No);

    //Wenn Dialog bestätigt wurde
    if (reply == QMessageBox::Yes) {
        // query ausführen
        if (!query.exec()) {
            qDebug() << "Error: " << query.lastError().text();
        } else {
            //Felder Leeren bei erfolgreicher ausführung
            ui->lineNewNum->clear();
            ui->lineNewFirstName->clear();
            ui->lineNewLastName->clear();
            ui->lineNewPhone->clear();
            ui->lineNewStreet->clear();
            ui->lineNewPostCode->clear();
            ui->lineNewCity->clear();
            ui->lineNewEMail->clear();
            qDebug() << "Data added successfully!";
        }
    }

}

/*
 * Ein Benutzer aus der Datenbank löschen
 *
*/
void AdminDialog::delUser(){
    //query erstellen
    //Benutzer mit eingegebener ID aus BibMem auswählen
    QSqlQuery query;
    query.prepare("SELECT * FROM BibMem WHERE Member_ID = :id");
    query.bindValue(":id", ui->lineDelUserNum->text());

    if (!query.exec()) {
        //Fehler wenn query nichtausgefüht werden kann
        qDebug() << "Error: " << query.lastError().text();
    } else {

        if(query.next()){
            qDebug() << "Found Data!";
            //Dialog mit Warnung erzeugen
            QMessageBox::StandardButton reply;
            //Im Dialog die ausgelesenen Daten anzeigen lassen
            reply = QMessageBox::question(this, "Bestätigung", "Achtung! \n\n"
                                                               "Sie sind dabei einen Datensatz zu löschen.\n"
                                                               "Folgender Datensatz wurde gefunden:\n\n"
                                                               "Benutzer ID: "+query.value("Member_ID").toString()+"\n"
                                                               "Vorname: "+query.value("First_Name").toString()+"\n"
                                                               "Nachname: "+query.value("Last_Name").toString()+"\n"
                                                               "Telefon: "+query.value("Phone_Num").toString()+"\n"
                                                               "Straße: "+query.value("Street").toString()+"\n"
                                                               "PLZ: "+query.value("Post_Code").toString()+"\n"
                                                               "Ort: "+query.value("City").toString()+"\n"
                                                               "E-Mail: "+query.value("Email").toString()+"\n"
                                                               "\n\n\n"
                                                               "Möchten Sie diesen Datensatz wirklich löschen?",
                                          QMessageBox::Yes | QMessageBox::No);

            //Bei bestätigung des Dialogs
            if (reply == QMessageBox::Yes) {
                //Query zum löschen ausführen
                QSqlQuery delquery;
                delquery.prepare("DELETE FROM BibMem WHERE Member_ID = :id");
                delquery.bindValue(":id", ui->lineDelUserNum->text());
                if (!delquery.exec()) {
                    qDebug() << "Error: " << delquery.lastError().text();
                } else {
                    qDebug() << "Data deleted successfully!";
                    ui->lineDelUserNum->clear();
                }
            }
        }


    }
}



/*
 * Ein Benutzer aus der Datenbank ändern
 *
*/
void AdminDialog::changeUser(){
    //alle Benutzer aus BibMem mit eingegebene ID anzeigen
    QSqlQuery query;
    query.prepare("SELECT * FROM BibMem WHERE Member_ID = :id");
    query.bindValue(":id", ui->lineChangeUserNum->text());

    //query ausführen
    if (!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
    } else {

        if(query.next()){
            qDebug() << "Found Data!";
            //Dialog mit Warnung erstllen und Benutzerdaten anzeigen lassen
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Bestätigung",  "Achtung! \n\n"
                                                                "Sie sind dabei einen Datensatz zu verändern.\n"
                                                                "Folgender Datensatz wurde gefunden:\n\n"
                                                                "Benutzer ID: "+query.value("Member_ID").toString()+"\n"
                                                                "Vorname: "+query.value("First_Name").toString()+"\n"
                                                                "Nachname: "+query.value("Last_Name").toString()+"\n"
                                                                "Telefon: "+query.value("Phone_Num").toString()+"\n"
                                                                "Straße: "+query.value("Street").toString()+"\n"
                                                                "PLZ: "+query.value("Post_Code").toString()+"\n"
                                                                "Ort: "+query.value("City").toString()+"\n"
                                                                "E-Mail: "+query.value("Email").toString()+"\n"
                                                                "\n\n\n"
                                                                "Möchten Sie Veränderungen an diesem Datensatz vornehmen?",
                                          QMessageBox::Yes | QMessageBox::No);

            //Bei Bestätigung der Warnung
            if (reply == QMessageBox::Yes) {

                //Modell erstellen
                delete this->tmodel;
                tmodel = new QSqlTableModel(this,db);
                tmodel->setTable("BibMem");
                tmodel->setFilter(QString("Member_ID = '%1'").arg(ui->lineChangeUserNum->text()));
                tmodel->select();

                //neues Fenster mit Tabelle und Modell erstellen
                ItemChangeDialog changedialog = ItemChangeDialog(tmodel, this);
                changedialog.exec();

                ui->lineChangeUserNum->clear();
            }
        }
    }

}

/*
 * zeigt ein Fenster zum Bearbeiten der Bücherdaten an
 *
*/
void AdminDialog::editItem(){

    ui->stackedWidgetFilter->hide();
    ui->stackedWidget->setCurrentWidget(ui->pageNewItem);

}


void AdminDialog::addItem(){
    //query erstellen zum einfügen eines Buchs
    QSqlQuery query;
    query.prepare("INSERT INTO Book (Book_ID,Status,Title,Author,Publisher,ISBN,Year_Pub,Category) VALUES (:id, :s, :t, :a, :p, :i, :y, :c)");
    query.bindValue(":id", ui->lineNewItemNum->text());
    query.bindValue(":s","available");
    query.bindValue(":t", ui->lineNewItemTitle->text());
    query.bindValue(":a", ui->lineNewItemAutor->text());
    query.bindValue(":p", ui->lineNewItemPubl->text());
    query.bindValue(":i", ui->lineNewItemISBN->text());
    query.bindValue(":y", ui->lineNewItemYear->text());
    //eingegebene Kategorie auslesen
    QVariant boxData = ui->boxType->currentData();
    ItemCategory::Cat t = boxData.value<ItemCategory::Cat>();

    //in abängigkeit der kategorie die query verändern
    switch (t) {
    case ItemCategory::Cat::Elektrotechnik:
        query.bindValue(":c", "Elektrotechnik");
        break;
    case ItemCategory::Cat::Maschinenbau:
        query.bindValue(":c", "Maschinenbau");
        break;
    case ItemCategory::Cat::Informatik:
        query.bindValue(":c", "Informatik");
        break;
    case ItemCategory::Cat::Betriebswirtschaft:
        query.bindValue(":c", "Betriebswirtschaft");
        break;
    case ItemCategory::Cat::Rechtswissenschaften:
        query.bindValue(":c", "Rechtswissenschaften");
        break;
    default:
        break;
    }

    //Dialog mit Warnung erstellen, eingebene Datan darin anzeigen
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Bestätigung", "Achtung! \n\n"
                                                       "Sie Fügen einen neuen Datansatz hinzu.\n"
                                                       "Bitte Überprüfen Sie die eingaben:\n\n"
                                                       "Buch ID: "+ui->lineNewItemNum->text()+"\n"
                                                       "Titel: "+ui->lineNewItemTitle->text()+"\n"
                                                       "Autor: "+ui->lineNewItemAutor->text()+"\n"
                                                       "Verlag: "+ui->lineNewItemPubl->text()+"\n"
                                                       "ISBN: "+ui->lineNewItemISBN->text()+"\n"
                                                       "Jahr: "+ui->lineNewItemYear->text()+"\n"
                                                       "Kategorie: "+ItemCategory::toString(t)+"\n"
                                                       "\n\n\n"
                                                       "Möchten Sie wirklich fortfahren?",
                                  QMessageBox::Yes | QMessageBox::No);


    //Bei Bestätigung
    if (reply == QMessageBox::Yes) {
        //query ausführen
        if (!query.exec()) {
            qDebug() << "Error: " << query.lastError().text();
        } else {
            //textfelder leeren
            ui->lineNewItemNum->clear();
            ui->lineNewItemTitle->clear();
            ui->lineNewItemAutor->clear();
            ui->lineNewItemPubl->clear();
            ui->lineNewItemISBN->clear();
            ui->lineNewItemYear->clear();
            qDebug() << "Data added successfully!";
        }
    }

}

/*
 * Ein Buch aus der Datenbank löschen
 *
*/
void AdminDialog::delItem(){
    //alle Bücher mit eingegebener ID anzeigen lassen
    QSqlQuery query;
    query.prepare("SELECT * FROM Book WHERE Book_ID = :id");
    query.bindValue(":id", ui->lineDelItemNum->text());

    //query ausführen
    if (!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
    } else {


        if(query.next()){
            qDebug() << "Found Data!";
            //Dialog mit Warnung erstellen, ausgelesene Daten darin anzeigen lassen
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Bestätigung", "Achtung! \n\n"
                                                               "Sie sind dabei einen Datensatz zu löschen.\n"
                                                               "Folgender Datensatz wurde gefunden:\n\n"
                                                               "Buch ID: "+query.value("Book_ID").toString()+"\n"
                                                                "Titel: "+query.value("Title").toString()+"\n"
                                                                "Autor: "+query.value("Author").toString()+"\n"
                                                                "Verlag: "+query.value("Publisher").toString()+"\n"
                                                                "ISBN: "+query.value("ISBN").toString()+"\n"
                                                                "Jahr: "+query.value("Year_Pub").toString()+"\n"
                                                                "Kategorie: "+query.value("Category").toString()+"\n"
                                                                "\n\n\n"
                                                                "Möchten Sie diesen Datensatz wirklich löschen?",
                                          QMessageBox::Yes | QMessageBox::No);


            if (reply == QMessageBox::Yes) {
                // query zum löschen erstellen und ausführen
                QSqlQuery delquery;
                delquery.prepare("DELETE FROM Book WHERE Book_ID = :id");
                delquery.bindValue(":id", ui->lineDelItemNum->text());
                if (!delquery.exec()) {
                    qDebug() << "Error: " << delquery.lastError().text();
                } else {
                    ui->lineDelItemNum->clear();
                    qDebug() << "Data deleted successfully!";
                }
            }
        }


    }



}

/*
 * Ein Buch aus der Datenbank ändern
 *
*/
void AdminDialog::changeItem(){
    //alle Bücher mit eingegebener ID anzeigen lassen
    QSqlQuery query;
    query.prepare("SELECT * FROM Book WHERE Book_ID = :id");
    query.bindValue(":id", ui->lineChangeItemNum->text());

    if (!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
    } else {

        if(query.next()){
            qDebug() << "Found Data!";
            //Dialog mit Warnung anzeigen lassen
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Bestätigung", "Achtung! \n\n"
                                                               "Sie sind dabei einen Datensatz zu verändern.\n"
                                                               "Folgender Datensatz wurde gefunden:\n\n"
                                                               "Buch ID: "+query.value("Book_ID").toString()+"\n"
                                                               "Titel: "+query.value("Title").toString()+"\n"
                                                               "Autor: "+query.value("Author").toString()+"\n"
                                                               "Verlag: "+query.value("Publisher").toString()+"\n"
                                                               "ISBN: "+query.value("ISBN").toString()+"\n"
                                                               "Jahr: "+query.value("Year_Pub").toString()+"\n"
                                                               "Kategorie: "+query.value("Category").toString()+"\n"
                                                               "\n\n\n"
                                                               "Möchten Sie Veränderungen an diesem Datensatz vornehmen?",
                                          QMessageBox::Yes | QMessageBox::No);


            if (reply == QMessageBox::Yes) {
                // Aktion ausführen

                //Modell erstellen
                delete this->tmodel;
                tmodel = new QSqlTableModel(this,db);
                tmodel->setTable("Book");
                tmodel->setFilter(QString("Book_ID = '%1'").arg(ui->lineChangeItemNum->text()));
                tmodel->select();


                //neuen Dialog mit Tabelle und Modell
                ItemChangeDialog changedialog = ItemChangeDialog(tmodel, this);
                changedialog.exec();

                ui->lineChangeItemNum->clear();

            }
        }


    }

}


/*
 * Fenster zum zurückgeben eines Buches anzeigen
 *
*/
void AdminDialog::returnItem(){

    ui->stackedWidgetFilter->hide();
    ui->stackedWidget->setCurrentWidget(ui->pageReadItem);

}


/*
 * Buch annehmen
 *
*/
void AdminDialog::acceptItem(){
    //alle Bücher mit eingegebener ID anzeigen lassen
    QSqlQuery query;
    query.prepare("SELECT * FROM Book WHERE Book_ID = :id");
    query.bindValue(":id", ui->lineBackItemNum->text());

    if (!query.exec()) {
        qDebug() << "Error: " << query.lastError().text();
    } else {


        query.next();

        //Dialog mit Warnung anzeigen lassen
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Bestätigung",  "Achtung! \n\n"
                                                           "Sie sind dabei eine Buch zurück zu nehmen.\n"
                                                           "Folgender Datensatz wurde gefunden:\n\n"
                                                           "Buch ID: "+query.value("Book_ID").toString()+"\n"
                                                           "Titel: "+query.value("Title").toString()+"\n"
                                                           "Autor: "+query.value("Author").toString()+"\n"
                                                           "Verlag: "+query.value("Publisher").toString()+"\n"
                                                           "ISBN: "+query.value("ISBN").toString()+"\n"
                                                           "Jahr: "+query.value("Year_Pub").toString()+"\n"
                                                           "Kategorie: "+query.value("Category").toString()+"\n"
                                                           "\n\n\n"
                                                           "Möchten Sie das Buch annehmen?",
                                      QMessageBox::Yes | QMessageBox::No);

        //Bei Bestätigung des Dialogs
        if (reply == QMessageBox::Yes) {
            // query zum ändern des Status ausführen
            QSqlQuery cquery;
            cquery.prepare("UPDATE Book SET Status = 'available' WHERE Book_ID = :id");
            cquery.bindValue(":id", ui->lineBackItemNum->text());
            if (!cquery.exec()) {
                qDebug() << "Error: " << cquery.lastError().text();
            } else {
                qDebug() << "Data changed successfully!";

            }


            // query zum löschen aus Loans ausführen
            QSqlQuery delquery;
            delquery.prepare("DELETE FROM Loans WHERE BookID = :id");
            delquery.bindValue(":id", ui->lineBackItemNum->text());
            if (!delquery.exec()) {
                qDebug() << "Error: " << delquery.lastError().text();
            } else {
                qDebug() << "Data deleted successfully!";
                ui->lineBackItemNum->clear();
            }
        }


    }
}

/*
 * Fenster zum anzeigen des Bücher
 *
*/
void AdminDialog::showInventory(){

    ui->stackedWidgetFilter->show();
    ui->stackedWidgetFilter->setCurrentWidget(ui->pageItemFilter);

    this->createInvenTable();
    ui->stackedWidget->setCurrentWidget(ui->pageShowItems);

}

/*
 * Tabelle mit Büchern erstellen
 *
*/
void AdminDialog::createInvenTable(){

    //Modell erstellen
    delete this->tmodel;
    tmodel = new QSqlTableModel(this,db);
    tmodel->setTable("Book");
    tmodel->select();

    //Modell in TableView anzeigen lassen
    ui->tableInventory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableInventory->setModel(tmodel);
    ui->tableInventory->show();


}

/*
 * Erstellt Filter für die Anzeige der Bücher
 *
*/
void AdminDialog::loadItemFilters(){

    bool setYear=false;
    bool setCategory=false;
    bool setAuthor=false;
    bool setTitle=false;

    //ein Modell erstellen und alle Bücher anzeigen
    delete this->tmodel;
    tmodel = new QSqlTableModel(this,db);
    tmodel->setTable("Book");
    QString filter ="";

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




    tmodel->setFilter(filter);//Filter setzen
    tmodel->select();

    ui->tableInventory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableInventory->setModel(tmodel);
    ui->tableInventory->show();
}

/*
 * Fenster zum anzeigen der Benutzer erstellen
 *
*/
void AdminDialog::showUser(){

    ui->stackedWidgetFilter->show();
    ui->stackedWidgetFilter->setCurrentWidget(ui->pageUserFilter);

    this->createUserTable();
    ui->stackedWidget->setCurrentWidget(ui->pageShowUser);

}

/*
 * Tabelle mit Benutzern erstellen
 *
*/
void AdminDialog::createUserTable(){
    //Modell erstellen
    delete this->tmodel;
    tmodel = new QSqlTableModel(this,db);
    tmodel->setTable("BibMem");
    tmodel->select();

    //Modell in Table View anzeigen
    ui->tableUser->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableUser->setModel(tmodel);
    ui->tableUser->show();


}

/*
 * Erstellt Filter für de Anzeige der Benutzer
 *
*/
void AdminDialog::loadUserFilters(){
    //ein Modell erstllen und alles aus BibMem anzeigen lassen
    delete this->tmodel;
    tmodel = new QSqlTableModel(this,db);
    tmodel->setTable("BibMem");
    QString filter ="";

    bool setMemID=false;

    //Wenn Benutzer ID eingegeben wurde
    if(ui->lineMemIDFilter->text()!=""){

        setMemID=true;//MemID gesetzt
        //Dem Filter die ID Suche hinzufügen
        filter=filter+QString("Member_ID LIKE '%%1%'").arg(ui->lineMemIDFilter->text());
    }

    //Wenn ein Nachname eingegeben wurde
    if(ui->lineLNameFilter->text()!=""){
        //Wenn bereits eine ID gesetzt wurde
        //soll diese mit AND zusammengefügt werden, sodass nach ID UND dem Nachnamen gesucht wird
        if(setMemID){
            filter="("+filter+") AND ";
        }

        filter=filter+QString("Last_Name LIKE '%%1%'").arg(ui->lineLNameFilter->text());
    }

    tmodel->setFilter(filter);
    tmodel->select();

    ui->tableUser->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableUser->setModel(tmodel);
    ui->tableUser->show();
}

/*
 * Fenster zum Anzeigen der ausgeliehenen Bücher estellen
 *
*/
void AdminDialog::showLoans(){
    ui->stackedWidgetFilter->show();
    ui->stackedWidgetFilter->setCurrentWidget(ui->pageLaonFilter);

    this->createLoansTable();
    ui->stackedWidget->setCurrentWidget(ui->pageLoans);
}

/*
 * Tabelle mit ausgeiehenen Büchern erstellen
 *
*/
void AdminDialog::createLoansTable(){
    //Modell estellen
    delete this->tmodel;
    tmodel = new QSqlTableModel(this,db);
    tmodel->setTable("Loans");
    tmodel->select();

    //Modell in TableView anzeigen
    ui->tableLoans->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableLoans->setModel(tmodel);
    ui->tableLoans->show();
}

/*
 * Erstellt Filter für die Anzeige der Ausgeliehenen Bücher
 *
*/
void AdminDialog::loadLoansFilters(){
    //ein Modell erstllen und alles aus Loans anzeigen lassen
    delete this->tmodel;
    tmodel = new QSqlTableModel(this,db);
    tmodel->setTable("Loans");
    QString filter ="";

    bool setMemID=false;

    //Wenn Benutzer ID eingegeben wurde
    if(ui->lineMemIDLoanFilter->text()!=""){

        setMemID=true;//MemID gesetzt
        filter=filter+QString("MemID LIKE '%%1%'").arg(ui->lineMemIDLoanFilter->text());
    }

    //Wenn Buch ID eingegeben wurde
    if(ui->lineBookIDFilter->text()!=""){
        //Wenn bereits eine ID gesetzt wurde
        //soll diese mit AND zusammengefügt werden, sodass nach Benutzer ID UND Buch ID gesucht wird
        if(setMemID){
            filter="("+filter+") AND ";
        }

        filter=filter+QString("BookID LIKE '%%1%'").arg(ui->lineBookIDFilter->text());
    }

    tmodel->setFilter(filter);
    tmodel->select();

    ui->tableLoans->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableLoans->setModel(tmodel);
    ui->tableLoans->show();
}




