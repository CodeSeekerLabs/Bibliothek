/************
Autor:      CodeSeekerLabs

Projekt:    Bibliothek
            Ein Programm zur Verwaltung einer Bibliothek mit zurgriff auf eine Datenbank

Klasse:     ItemChangeDialog
            Erstellt ein Fenster in dem die Daten eines Buchs geändert werden können

Datum:      10.09.2024
*************/

#include "itemchangedialog.h"
#include "ui_itemchangedialog.h"

#include <QtSql>

ItemChangeDialog::ItemChangeDialog(QSqlTableModel *t, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ItemChangeDialog)
{
    ui->setupUi(this);
    this->table= t;

    //zeigt das übergebene TableModel in der View an, kann dadurch bearbeitet werden
    ui->tableChangeItem->setModel(table);
    ui->tableChangeItem->show();
}

ItemChangeDialog::~ItemChangeDialog()
{
    delete ui;
}
