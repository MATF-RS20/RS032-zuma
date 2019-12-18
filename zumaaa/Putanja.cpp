#include "Putanja.h"
#include <QGraphicsScene>
#include <QDebug>
extern QGraphicsScene *scene;

Putanja::Putanja(int precnik, int brojLopti, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , maxSize(brojLopti)
    , precnik(precnik)
{
    //zadajemo listu tacaka
    tacke << QPointF(500, 100) << QPointF(500, 300) << QPointF(100, 300) << QPointF(100, 100) << QPointF(300, 100) << QPointF(300, 200);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(create()));

    timer->start(2000);
}

QRectF Putanja::boundingRect() const
{
    return QRectF(x(), y(), 800, 600);
}

void Putanja::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

}

void Putanja::create() {
    // Ako nam je velicina jednaka maximalnoj velicini stajemo sa pravljenjem novih
    if(lopte.size() >= maxSize) {
        timer->stop();
        return;
    }
    // pravimo novu loptu i dodajemo je u listu i na scenu
    Lopta *lopta = new Lopta(precnik, tacke);
    lopte.append(lopta);
    scene()->addItem(lopta);
    connect(this, SIGNAL(pomeri_se(QPointF)), lopta, SLOT(move_back(QPointF)));
}

void Putanja::dodaj_loptu(QPointF tacka)
{
    //qDebug()<<tacka;
    foreach (auto x, lopte) {
        qDebug()<<(x)->pos();
        emit pomeri_se(tacka);
    }
    timer = new QTimer(this);
}
