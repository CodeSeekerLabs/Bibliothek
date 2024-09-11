/************
Autor:      CodeSeekerLabs

Projekt:    Bibliothek
            Ein Programm zur Verwaltung einer Bibliothek mit zurgriff auf eine Datenbank

Klasse:     ItemChangeDialog
            Erstellt ein Fenster in dem die Daten eines Buchs geändert werden können

Datum:      10.09.2024
*************/

#ifndef ITEMCHANGEDIALOG_H
#define ITEMCHANGEDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ItemChangeDialog;
}

class ItemChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemChangeDialog(QSqlTableModel *t, QWidget *parent = nullptr);
    ~ItemChangeDialog();

private:
    Ui::ItemChangeDialog *ui;
    QSqlTableModel *table;
};

#endif // ITEMCHANGEDIALOG_H
