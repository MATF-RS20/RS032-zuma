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
    Zabica(int x, int y, int size, int precnik, QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void promeni_boju();
    QRectF boundingRect() const override;
public slots:
    void rotiraj(QMouseEvent*);
    void klik(QMouseEvent*);

signals:
    void Mouse_Move();
    void Mouse_Pos();
    void Mouse_Left();
private:
    int x;
    int y;
    int size;
    int precnik;
    QPointF centar;
    QPixmap boja;
    //LoptaUUstima* lopta;

public:
   int indexBoje = 0;

};

#endif // ZABICA_H
