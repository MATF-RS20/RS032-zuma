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
    Zabica(int x, int y, int size, int precnik, QGraphicsObject *parent = 0);
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

public:
   int indexBoje = 0;
   LoptaUUstima* loptaUsta;

};

#endif // ZABICA_H
