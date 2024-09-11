/************
Autor:      CodeSeekerLabs

Projekt:    Bibliothek
            Ein Programm zur Verwaltung einer Bibliothek mit zurgriff auf eine Datenbank

Klasse:     MainWindow
            Erstellt das Hauptfenster

Datum:      10.09.2024
*************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <iostream>

#include "userdialog.h"
#include "admindialog.h"
#include "registrationdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;

}

/*
 * öffnet das Fenster mit dem Benutzerinterface
 *
*/
void MainWindow::openUserInterface(){
    //Fenster zur Registration öffnen
    RegistrationDialog registration = RegistrationDialog(this);

    //wenn Dialog akzeptiert wurde
    if(registration.exec() == QDialog::Accepted){

        //try Benutzerinterface zu öffnen
        try {
            UserDialog *user= new UserDialog(registration.getMemID(),this);
            this->hide();//Hauptfenster verstecken
            user->exec();// Dialog öffnen
            QApplication::quit();//nach beenden des dialogs die Anwendung beenden
        } catch (const std::invalid_argument &e) {
            std::cerr << "Fehler: " << e.what() << std::endl;//Wenn falsche MemID eingegeben wurde,
                                                            //wird beim erstellen von UserDialog eine Exception geworfen
        }

    }


}


/*
 * öffnet das Fenster mit dem Verwaltungsinterface
 *
*/
void MainWindow::openAdminInterface(){
    AdminDialog admin = AdminDialog(this);
    this->hide();
    admin.exec();
    QApplication::quit();
}
























