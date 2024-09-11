/************
Autor:      CodeSeekerLabs

Projekt:    Bibliothek
            Ein Programm zur Verwaltung einer Bibliothek mit zurgriff auf eine Datenbank

Klasse:     AdiminDialog
            Erstellt das Fenster mit dem die Verwaltung interagieren kann

Datum:      10.09.2024
*************/

#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include <QtSql>





namespace Ui {
class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = nullptr);
    ~AdminDialog();

private slots:
    void showHome();
    void editUser();
    void editItem();
    void returnItem();
    void showInventory();
    void showUser();
    void showLoans();

    void acceptItem();

    void addItem();
    void delItem();
    void changeItem();

    void addUser();
    void delUser();
    void changeUser();


    void loadItemFilters();
    void loadUserFilters();
    void loadLoansFilters();


private:
    Ui::AdminDialog *ui;
    QSqlQueryModel *qmodel;
    QSqlTableModel *tmodel;
    QSqlDatabase db;

    void createInvenTable();
    void createUserTable();
    void createLoansTable();
};

#endif // ADMINDIALOG_H
