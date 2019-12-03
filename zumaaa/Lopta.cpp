#include "Lopta.h"
#include <QTimer>
#include <QtMath>
#include <QDebug>

Lopta::Lopta(QGraphicsItem *parent)
{
    Q_UNUSED(parent);

    setRect(0, 0, 50, 50); // dimenzije lopte na 50x50
    setPos(500,100); // pocetna tacka nase lopte

    // lista tacaka ka kojima se lopta krece
    tacke << QPointF(500, 300) << QPointF(100, 300) << QPointF(100, 100) << QPointF(300, 100) << QPointF(300, 200);
    // bitno! svo kretanje i rotacije su postavljene na centar lopte
    setTransformOriginPoint(25, 25);
    // inicijalizacija elemenata
    index = 0;
    krajnja = tacke[0];
    // rotiramo da se krecemo ka prvoj tacki
    //TODO: mozda bolje ime za krajnja, jer se odnosi na
    // trenutnu destinaciju, kao ciljnaTacka npr
    rotateToPoint(krajnja);
    // dodat timer
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(200);
}
// funkcija rotacije ka ciljnoj tacki
void Lopta::rotateToPoint(QPointF p)
{
    QLineF ln(pos(), p);
    setRotation(-1*ln.angle());
}
// funkcija koja se poziva pri timeru
void Lopta::move()
{   //ako smo blizu jedne tacke (5px), prelazimo na narednu
    QLineF ln(pos(), krajnja);
    if(ln.length()<5){
        index++;
        // ako vise nemamo tacaka stajemo
        if (index >= tacke.size()){
            return;
        }
        // postavljamo naredni cilj i rotiramo se ka njemu
        krajnja=tacke[index];
        rotateToPoint(krajnja);
    }
    // krecemo se za broj koraka u odnosu na trenutnu rotaciju
    int korak = 5;
    double theta = rotation();
    double dy = korak * qSin(qDegreesToRadians(theta));
    double dx = korak * qCos(qDegreesToRadians(theta));
    setPos(x()+dx, y()+dy);
}
