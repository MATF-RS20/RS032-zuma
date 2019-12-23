#include "Zabica.h"
#include <QDebug>
#include <iostream>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QEvent>
#include "LoptaUUstima.h"
#include <QWidget>
#include <QPoint>
#include <QtMath>
#include <QFont>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QTimer>
#include <QSignalMapper>
#include<iostream>
#include "Game.h"


extern QGraphicsScene * scene;
//extern Game * game;


Zabica::Zabica(int x, int y, int height, int weight, int precnik, QGraphicsItem *parent)
:QGraphicsRectItem(parent)
,precnik(precnik)
,centar(QPointF(x + height/2, y + weight/2))
,x(x)
,y(y)
//,lopta(new LoptaUUstima(x + height/2-precnik/2, y+weight/2-precnik/2, 25, pos()))
{
    Q_UNUSED(parent);
    setRect(x,y,weight,height);
    //lopta= new LoptaUUstima(centar.x()- precnik/2, centar.y()- precnik/2, precnik, pos());
    //scene()->addItem(lopta);

//    setRect(0, 0, 100, 100);
//    setPos(200, 250);
//    setTransformOriginPoint(50, 50);

    promeni_boju();

//    qDebug() << centar;
}

void Zabica:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(250, 300, size, size, boja);
}

QRectF Zabica::boundingRect() const
{
    return QRectF(250, 300, size, size);
}

void Zabica::promeni_boju(){



        QVector <QPixmap> niz_slika;
        niz_slika.resize(4);
        niz_slika[0]=QPixmap(":/images/images/zabica_roze.png");
        niz_slika[1]=QPixmap(":/images/images/zabica_plava.png");
        niz_slika[2]=QPixmap(":/images/images/zabica_zelena.png");
        niz_slika[3]=QPixmap(":/images/images/zabica_ljubicasta.png");
        index = rand() % 4;
        boja= niz_slika[index];
        update(this->boundingRect());

}

void Zabica::rotiraj(QMouseEvent* event)
{

    QPointF center = this->rect().center();
    QLineF ln(centar,event->pos());
    setTransformOriginPoint(center.x(), center.y());
    setRotation(-1 * ln.angle());

}

void Zabica::klik(QMouseEvent * event)
{



    if(event->buttons() & Qt::RightButton){

        promeni_boju();
        qDebug()<<"Promenio sam boju lopte";
        //auto x_ = centar.x() - precnik/2;
        //auto y_ = centar.y() - precnik/2;
        //lopta= new LoptaUUstima(centar.x(), centar.y(), precnik, pos());
        //lopta->promeni_boju();

    }else if(event->buttons() & Qt::LeftButton){
//        qDebug()<<"Pucao sam i napravio novu loptu";

        QPointF p =event->pos(); // pozicija klika
        auto x_ = centar.x() - precnik/2;
        auto y_ = centar.y() - precnik/2;
        // x_ i y_ su koordinate koje postavljaju loptu u centar zabice
        // oduzimam precnik/2 da ne bi postavio gornji levi ugao u centar zabice

        LoptaUUstima* lopta2= new LoptaUUstima(x_,y_, precnik, p);
        lopta2->setBoja(index);
        QTimer* timer = new QTimer(this);
        scene()->addItem(lopta2);
        QObject::connect(timer, SIGNAL(timeout()), lopta2, SLOT(move()));
        timer->start(50);

        promeni_boju();

    }



}

