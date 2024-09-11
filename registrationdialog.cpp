/************
Autor:      CodeSeekerLabs

Projekt:    Bibliothek
            Ein Programm zur Verwaltung einer Bibliothek mit zurgriff auf eine Datenbank

Klasse:     RegistratioDialog
            Erstellt das Fenster mit dem sich die Benutzer anmelden können

Datum:      10.09.2024
*************/

#include "registrationdialog.h"
#include "ui_registrationdialog.h"

RegistrationDialog::RegistrationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);
    this->memID="";
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}


/*
 * setzt die eingegebene Benutzer ID und akzeptiert den Dialog
 *
*/
void RegistrationDialog::okButton(){
    this->memID=ui->lineMemID->text();
    accept();
}

/*
 * gibt die eingegebene Benutzer ID zurück
 *
*/
QString RegistrationDialog::getMemID() const{
    return this->memID;
}
