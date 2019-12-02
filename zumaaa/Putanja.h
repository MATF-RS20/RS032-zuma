#ifndef PUTANJA_H
#define PUTANJA_H
#include <QObject>
#include <QLine>
#include <QList>  //omogucen lista<<element za ubacanje
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsLineItem>

class Putanja: public QObject, QGraphicsLineItem{
    Q_OBJECT
public:
    Putanja(QGraphicsItem *parent = 0);
private:
    QList<QPointF> tacke;
    QPointF krajnja;
};

#endif // PUTANJA_H
