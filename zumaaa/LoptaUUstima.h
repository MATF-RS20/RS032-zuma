#ifndef LOPTAUUSTIMA_H
#define LOPTAUUSTIMA_H

#include <QGraphicsRectItem>
#include <QObject>

//da bi mogli slotovi da se koriste mora klasa da nasledjuje QObject i da ima ovaj Q_Object makro na pocetku klase
class LoptaUUstima: public QObject, public QGraphicsRectItem{
        Q_OBJECT
public:
    LoptaUUstima();
public slots:
    void move();
};

#endif // LOPTAUUSTIMA_H
