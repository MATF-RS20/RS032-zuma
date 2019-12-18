#ifndef PUTANJA_H
#define PUTANJA_H
#include <QObject>
#include <QLine>
#include <QList>  //omogucen lista<<element za ubacanje
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QTimer>
#include <QPainter>
#include "Lopta.h"

class Putanja: public QGraphicsObject {
    Q_OBJECT
public:
    Putanja(int precnik, int brojLopti, QGraphicsItem *parent=0);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
signals:
    void pomeri_se(QPointF);
public slots:
    void create();
    void dodaj_loptu(QPointF tacka);
private:
    QList<QPointF> tacke;
    QPointF krajnja;
    QList<Lopta*> lopte;
    QTimer *timer;
    int maxSize;
    int precnik;
};

#endif // PUTANJA_H
