#ifndef ZABICA_H
#define ZABICA_H

#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
#include <QEvent>
#include <QGraphicsObject>
#include "LoptaUUstima.h"

class Zabica : public QGraphicsObject {
    Q_OBJECT
public:
//void mouseMoveEvent(QMouseEvent * event);
    Zabica(int x, int y, int height, int weight, int precnik, QGraphicsItem *parent = 0);
//    int x, y;

public slots:
    void rotiraj(QMouseEvent*);
    void klik(QMouseEvent*);

signals:
    void Mouse_Move();
    void Mouse_Pos();
    void Mouse_Left();
private:
    int precnik;
    QPointF centar;
    QPixmap boja;
    qreal size=200;
    int index = 0;
    //LoptaUUstima* lopta;
public:
    int x;
    int y;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void promeni_boju();
    QRectF boundingRect() const override;

};

#endif // ZABICA_H
