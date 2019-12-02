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


void Zabica::rotiraj(QMouseEvent* event)
{
    QPoint p = event->pos();
//    qDebug()<<p;

    QPointF center = this->rect().center();
//    qDebug()<<center.x();
    QPointF kvadrat = this->pos();
    double pom_x = center.x()+kvadrat.x();
    double pom_y = center.y()+kvadrat.y();
/*
     qreal angle = (180/M_PI)*qAtan2(p.y()-pom_y ,p.x()-pom_x);
     qDebug()<<angle;
     QTransform trans = transform();
     trans.translate(center.x(), center.y());
     trans.rotate(angle);
     trans.translate(-center.x(), -center.y());
     setTransform(trans);
    qreal angle = (180/M_PI)*qAtan2(p.y() + this->y,p.x() - this->x);*/

 /*   qreal angle = (180/M_PI)*qAtan2(p.y() + center.y(),p.x() + center.x());
    qDebug()<<angle<<" "<<center.x()<<" "<<center.y();
    this->setTransformOriginPoint(center.x(), center.y());*/


   // this->setRotation(angle);*/

  /*  qDebug()<<angle;
    this->setTransformOriginPoint(pom_x, pom_y);
    this->setRotation(angle);
    this->show();*/

    QLineF ln(pos(),event->pos());
    setTransformOriginPoint(center.x(), center.y());
    setRotation(-1 * ln.angle());

}

void Zabica::klik(QMouseEvent * event)
{
    //qDebug()<<"Zabica zna da si klikces miisa";
    //LoptaUUstima * lopta = new LoptaUUstima();
    //lopta->setPos(x, y);
    if(event->buttons() & Qt::RightButton){
        qDebug()<<"Promenio sam boju lopte";
    }else if(event->buttons() & Qt::LeftButton){
        qDebug()<<"Pucao sam i napravio novu loptu";
    }
    //scene()->addItem(lopta);
   // emit Mouse_Pressed();
}
