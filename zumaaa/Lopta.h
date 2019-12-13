#ifndef LOPTA_H
#define LOPTA_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QObject>
#include <QList>  //omogucen lista<<element za ubacanje
#include <QPointF>

class Lopta: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
public:
    Lopta(QGraphicsItem * parent=0);
    Lopta(QList<QPointF> tacke, QGraphicsItem * parent=0);
    void rotateToPoint(QPointF p);
    void postaviTacke(QList<QPointF> ps);
    void kolizija_crna_rupa();
    ~Lopta() = default;
public slots:
    void move();
private:
    QList<QPointF> tacke;
    QPointF krajnja;
    int index; //indeks tacke u listi ka kojoj trenutno idemo
    double size;
};


#endif // LOPTA_H
