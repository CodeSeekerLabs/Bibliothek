/************
Autor:      CodeSeekerLabs

Projekt:    Bibliothek
            Ein Programm zur Verwaltung einer Bibliothek mit zurgriff auf eine Datenbank

Klasse:     RegistratioDialog
            Erstellt das Fenster mit dem sich die Benutzer anmelden können

Datum:      10.09.2024
*************/

#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>

namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);
    ~RegistrationDialog();

    QString getMemID() const;


private slots:
    void okButton();

private:
    Ui::RegistrationDialog *ui;
    QString memID;
};

#endif // REGISTRATIONDIALOG_H
