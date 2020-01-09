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
#include "LoptaUUstima.h"

class Putanja: public QGraphicsObject {
    Q_OBJECT
public:
    Putanja(int precnik, int brojLopti, QGraphicsObject *parent=0);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void ubrzaj(int k);
    void zaustaviLopte();
    int getIndeksLopte(Lopta* lopta);
    QVector<int> indeksi;
    Lopta* susedne(Lopta * lopta);
    void resetuj_kolizije_lopti();
    void unisti_loptu(Lopta*lopta);
    bool prazneLopte();
signals:
    void pomeri_se(QPointF);
public slots:
    void create();
    void dodaj_loptu(Lopta*);
private:
    QList<QPointF> tacke;
    QPointF krajnja;
    QVector<Lopta*> lopte;
    QTimer *timer;
    int count = 0;
    int maxSize;
    int precnik;
    bool ind_udareno=false;
};



#endif // PUTANJA_H
