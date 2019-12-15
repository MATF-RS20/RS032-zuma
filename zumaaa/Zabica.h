#ifndef ZABICA_H
#define ZABICA_H

#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QDebug>
#include <QWidget>
#include <QEvent>

class Zabica:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
//void mouseMoveEvent(QMouseEvent * event);  
    Zabica(int x, int y, int height, int weight, QGraphicsItem *parent = 0);
//    int x, y;

public slots:
    void rotiraj(QMouseEvent*);
    void klik(QMouseEvent*);

signals:
    void Mouse_Move();
    void Mouse_Pos();
    void Mouse_Left();
private:
    QPointF centar;
};

#endif // ZABICA_H
