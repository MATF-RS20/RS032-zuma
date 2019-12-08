#include "Putanja.h"
#include <QGraphicsScene>

extern QGraphicsScene *scene;

Putanja::Putanja(QGraphicsItem *parent) {
    Q_UNUSED(parent);
    //zadajemo listu tacaka
    tacke << QPointF(500, 100) << QPointF(500, 300) << QPointF(100, 300) << QPointF(100, 100) << QPointF(300, 100) << QPointF(300, 200);

    maxSize = 10;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(create()));

    timer->start(2000);
}

void Putanja::create() {
    // Ako nam je velicina jednaka maximalnoj velicini stajemo sa pravljenjem novih
    if(lopte.size() >= maxSize) {
        timer->stop();
        return;
    }
    // pravimo novu loptu i dodajemo je u listu i na scenu
    Lopta *lopta = new Lopta(tacke);
    lopte.append(lopta);
    scene()->addItem(lopta);
}
