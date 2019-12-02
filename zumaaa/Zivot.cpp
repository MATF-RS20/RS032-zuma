#include "Zivot.h"
#include <QFont>

//ovo znaci da je QGraphicsTextItem bazicna klasa za nasu klasu score, nad njom se gradi, ona i dodeli roditelja ako prosledimo
Zivot::Zivot(QGraphicsItem *parent): QGraphicsTextItem(parent){
    zivot=3;
    //crtamo ga
    setPlainText(QString("Zivot: ")+QString::number(zivot));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 16));
}


void Zivot::increase()
{
    zivot++;   //i ovo treba izmeniti da u zavisnosti od broj aloptica i ulancanih kolizija daje veci skor
    setPlainText(QString("Zivot: ")+QString::number(zivot));

}
void Zivot::decrease()
{
    zivot--;   //i ovo treba izmeniti da u zavisnosti od broj aloptica i ulancanih kolizija daje veci skor
    setPlainText(QString("Zivot: ")+QString::number(zivot));

}

int Zivot::getZivot()
{
    return zivot;
}
