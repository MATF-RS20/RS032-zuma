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


extern QGraphicsScene * scene;


Zabica::Zabica(int x, int y, int height, int weight, int precnik, QGraphicsItem *parent)
:QGraphicsRectItem(parent)
,precnik(precnik)
,centar(QPointF(x + height/2, y + weight/2))
//,lopta(new LoptaUUstima(x + height/2-precnik/2, y+weight/2-precnik/2, 25, pos()))
{
    Q_UNUSED(parent);
    setRect(x,y,weight,height);
   // lopta= new LoptaUUstima(centar.x()- precnik/2, centar.y()- precnik/2, precnik, pos());
    //scene()->addItem(lopta);

//    setRect(0, 0, 100, 100);
//    setPos(200, 250);
//    setTransformOriginPoint(50, 50);


//    qDebug() << centar;
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
        qDebug()<<"Promenio sam boju lopte";
        //auto x_ = centar.x() - precnik/2;
        //auto y_ = centar.y() - precnik/2;
        //lopta= new LoptaUUstima(centar.x(), centar.y(), precnik, pos());
       // lopta->promeni_boju();

    }else if(event->buttons() & Qt::LeftButton){
//        qDebug()<<"Pucao sam i napravio novu loptu";

        QPointF p =event->pos(); // pozicija klika
        /// TODO: napraviti da se zadati precnik iz Game.cpp prenese ovde
        auto x_ = centar.x() - precnik/2;
        auto y_ = centar.y() - precnik/2;
        // x_ i y_ su koordinate koje postavljaju loptu u centar zabice
        // oduzimam precnik/2 da ne bi postavio gornji levi ugao u centar zabice

        LoptaUUstima* lopta2= new LoptaUUstima(x_, y_, precnik, p);
//        double a = (( p.x()-215)/10);
//        double b = (( p.y()-265)/10);
//        std::cout<<a<<", "<<b<<"   ";
        // Setujemo a i b
//        lopta2->postaviAB(p.x(), p.y());
        QTimer* timer = new QTimer(this);
        scene()->addItem(lopta2);
        QObject::connect(timer, SIGNAL(timeout()), lopta2, SLOT(move()));
        timer->start(50);

    }



}

