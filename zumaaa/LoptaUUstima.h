#ifndef LOPTAUUSTIMA_H
#define LOPTAUUSTIMA_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QEvent>
#include <QMouseEvent>
#include <QPixmap>

//da bi mogli slotovi da se koriste mora klasa da nasledjuje QObject i da ima ovaj Q_Object makro na pocetku klase
class LoptaUUstima: public QGraphicsObject{
        Q_OBJECT
public:
    LoptaUUstima(int x, int y, int precnik, QPointF p);
    // Seter za a i b
    void postaviAB(double a, double b);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    void setBoja(int indeks);
signals:
    void sudar(QPointF); //ispali ovaj signal kad kliknem, a ne kad se sudare..
public slots:
    void move();
private:
    // Privatne promenljive za pomeranje lopte
    double a, b;
    qreal size=50;
    QPixmap boja;


};

#endif // LOPTAUUSTIMA_H

