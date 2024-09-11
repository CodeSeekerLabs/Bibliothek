/************
Autor:      CodeSeekerLabs

Projekt:    Bibliothek
            Ein Programm zur Verwaltung einer Bibliothek mit zurgriff auf eine Datenbank

Klasse:     UserDialog
            Erstellt das Fenster mit dem Benutzer interagieren können

Datum:      10.09.2024
*************/

#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(const QString& memid,QWidget *parent = nullptr);
    ~UserDialog();

    void getUser();
    void getLoans();
    void getBooks();

private slots:
    void loadFilters();



private:
    Ui::UserDialog *ui;
    QSqlQueryModel *bookModel;
    QSqlQueryModel *loanModel;
    QSqlTableModel *tmodel;
    QSqlDatabase db;
    QString memid;



};

#endif // USERDIALOG_H
