#ifndef PUTANJA_H
#define PUTANJA_H
#include <QObject>
#include <QLine>
#include <QList>  //omogucen lista<<element za ubacanje
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QTimer>
#include "Lopta.h"

class Putanja: public QObject,public QGraphicsLineItem{
    Q_OBJECT
public:
    Putanja(QGraphicsItem *parent = 0);
public slots:
    void create();
private:
    QList<QPointF> tacke;
    QPointF krajnja;
    QList<Lopta*> lopte;
    QTimer *timer;
    int maxSize;
};

#endif // PUTANJA_H
