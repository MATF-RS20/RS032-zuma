#include "Lopta.h"
#include <QTimer>
#include <QtMath>
#include <QDebug>

Lopta::Lopta(QGraphicsItem *parent)
{
    tacke << QPointF(800, 0);
    tacke << QPointF(750, 0);
    tacke << QPointF(700, 10);
    tacke << QPointF(700, 10);
    tacke << QPointF(650, 20);

    index = 0;
    krajnja = tacke[0];
    rotateToPoint(krajnja);

    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(150);
}

void Lopta::rotateToPoint(QPointF p)
{
    QLineF ln(pos(), p);
    setRotation(-1*ln.angle());
}

void Lopta::move()
{   //ako smo blizu jedne tacke, prelazimo na narednu
    QLineF ln(pos(), krajnja);
    if(ln.length()<5){
        index++;
        if (index >= tacke.size()){
            return;
        }
//        qDebug() << tacke.size();
        krajnja=tacke[index];
        rotateToPoint(krajnja);
    }
    int korak = 5;
    double theta = rotation();
    double dy = korak * qSin(qDegreesToRadians(theta));
    double dx = korak * qCos(qDegreesToRadians(theta));
    setPos(x()+dx, y()+dy);

}
