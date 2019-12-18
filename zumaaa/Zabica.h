#ifndef ZABICA_H
#define ZABICA_H

#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
#include <QEvent>
#include "LoptaUUstima.h"

class Zabica:public QObject, public QGraphicsRectItem{
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
     int precnik=50;
    QPointF centar;
   // LoptaUUstima* lopta;

};

#endif // ZABICA_H
