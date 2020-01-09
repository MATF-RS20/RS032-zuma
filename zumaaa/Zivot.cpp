#include "Zivot.h"
#include <QFont>
#include "Game.h"


extern Game* game;


//ovo znaci da je QGraphicsTextItem bazicna klasa za nasu klasu score, nad njom se gradi, ona i dodeli roditelja ako prosledimo
Zivot::Zivot(QGraphicsItem *parent): QGraphicsTextItem(parent){
    zivot=3;
    //crtamo ga
    setPlainText(QString("Zivot: ")+QString::number(zivot));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("times", 16));
}


void Zivot::increase()
{
    zivot++;  //igrac dobija novi zivot ako se njegov skor dovoljno uvecao
    setPlainText(QString("Zivot: ")+QString::number(zivot));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("times", 16));

}
void Zivot::decrease()
{
    zivot--;

    //prekinuti igru, npr postaviti da loptice ulete brzo u rupu
    //mogao bi npr da se smannji zivot za svaku lopticu koja upadne u rupu

    setPlainText(QString("Zivot: ")+QString::number(zivot));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("times", 16));
}

int Zivot::getZivot()
{
    return zivot;
}
