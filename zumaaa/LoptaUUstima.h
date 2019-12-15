#ifndef LOPTAUUSTIMA_H
#define LOPTAUUSTIMA_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QEvent>
#include <QMouseEvent>

//da bi mogli slotovi da se koriste mora klasa da nasledjuje QObject i da ima ovaj Q_Object makro na pocetku klase
class LoptaUUstima: public QObject, public QGraphicsEllipseItem{
        Q_OBJECT
public:
    LoptaUUstima(int x, int y, int precnik, QPointF p);

    // Seter za a i b
    void postaviAB(double a, double b);
public slots:
    void move();

private:

    // Privatne promenljive za pomeranje lopte
    double a, b;

};

#endif // LOPTAUUSTIMA_H

