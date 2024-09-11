/************
Autor:      CodeSeekerLabs

Projekt:    Bibliothek
            Ein Programm zur Verwaltung einer Bibliothek mit zurgriff auf eine Datenbank

Klasse:     ItemCategory
            Klasse um eine Buchkategorie festzulegen und zurückzugeben

Datum:      10.09.2024
*************/


#ifndef ITEMCATEGORY_H
#define ITEMCATEGORY_H

#include <QString>



class ItemCategory
{

public:
    enum class Cat {
        Elektrotechnik =1,
        Maschinenbau =2,
        Informatik =3,
        Betriebswirtschaft =4,
        Rechtswissenschaften =5
    };

    static const QString toString(Cat value){
        switch (value) {
        case Cat::Elektrotechnik:
            return "Elektrotechnik";
            break;
        case Cat::Maschinenbau:
            return "Maschinenbau";
            break;
        case Cat::Informatik:
            return "Informatik";
            break;
        case Cat::Betriebswirtschaft:
            return "Betriebswirtschaft";
            break;
        case Cat::Rechtswissenschaften:
            return "Rechtswissenschaften";
            break;
        default:
            return "Unknown";
            break;
        }
    }


};

#endif // ITEMCATEGORY_H
