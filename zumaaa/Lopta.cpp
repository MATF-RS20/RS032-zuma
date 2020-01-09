#include "Lopta.h"
#include <QTimer>
#include <QtMath>
#include <random>
#include <iterator>
#include <QDebug>
#include "CrnaRupa.h"
#include "Putanja.h"
#include "Game.h"
#include <QtMultimedia/QMediaPlayer>

extern Game * game;

Lopta::Lopta(int precnik, QList<QPointF> tacke_, QGraphicsObject *parent)
: QGraphicsObject(parent),
  size(precnik),
  tacke(tacke_)
{
    // generisemo boju lopte
    generisi_boju();
    // inicijalizujemo parametre
    ideUnatrag = false;
    pocetniStop = false;
    doUdara = false;
    index = 0;
    pocetna_dim = size;

    setPos(tacke[0]); // pocetna tacka nase lopte je prva tacka iz liste tacke
    index++;
    krajnja = tacke[index]; // ovim samo kazemo da je destinacija naredna tacka

    // inicijalizujemo da se sve transformacije odnose na centar lopte
    setTransformOriginPoint(precnik/2, precnik/2);

    // rotiramo da se krecemo ka prvoj tacki
    // trenutnu destinaciju, kao ciljnaTacka
    rotateToPoint(krajnja);

    // dodat timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);

    // Ubacivanje zvuka kotrljanja lopti
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/sounds/rolling.ogg"));
    player->setVolume(10);
    connect(timer, SIGNAL(timeout()), player, SLOT(play()));

}

// funkcija rotacije ka ciljnoj tacki
void Lopta::rotateToPoint(QPointF p)
{
    QLineF ln(pos(), p);
    setRotation(-1*ln.angle());
}

void Lopta::kolizija_crna_rupa()
{
    QList<QGraphicsItem *> items = collidingItems();
    for(int i = 0; i < items.size(); ++i) {
        if(typeid(*(items[i])) == typeid(CrnaRupa)) {

            game->putanja->ubrzaj(6);

            if(size > pocetna_dim/4) {
                setScale(size/pocetna_dim);
                size -= 1;

            }
            else {
                isDeleted = true;
//                delete this;
                if(game->putanja->prazneLopte())
                {
                    // postavljanje zvuka upadanja lopte
                    QMediaPlayer *player = new QMediaPlayer;
                    player->setMedia(QUrl("qrc:/sounds/sounds/kraj.ogg"));
                    player->setVolume(40);
                    player->play();

                    game->zivot->decrease();
                }
            }
        }
    }

}
// funkcija koja se poziva pri timeru
void Lopta::move()
{
    kolizija_crna_rupa();

    //ako lopta ide unatrag proveravamo dal je udarila u neku koja ide napred i resetujemo indikatore
    if(ideUnatrag){
        QList<QGraphicsItem *> colliding_items= collidingItems();
       // qDebug()<<colliding_items.size();

        foreach(auto &x ,colliding_items){
           if(typeid(*x)==typeid(Lopta) && !static_cast<Lopta*>(x)->ideUnatrag){
               krajnja=tacke[index];
               id1=1;
               id2=1;
               ideUnatrag=false;
               if(static_cast<Lopta*>(x)->indexBoje==this->indexBoje){
                   qDebug()<<"iste boje kasniji sudar";
                   //Lopta* poslednja=game->putanja->susedne(static_cast<Lopta*>(x));
               }

           }
        }
    }

    //ako smo blizu jedne tacke (5px), prelazimo na narednu
    QLineF ln(pos(), krajnja);
    if(ln.length()<5){

        if(!ideUnatrag)  //ako idemo unatrag, vracamo se na prethodnu ciljnu tacku
            index++;
        else
            index--;
//        if(index < 0) index = 0; // za svaki slucaj xD

        if (index >= tacke.size()){
            return;
        }
        // postavljamo naredni cilj i rotiramo se ka njemu
        krajnja=tacke[index];
        rotateToPoint(krajnja);
    }

    // krecemo se za broj koraka u odnosu na trenutnu rotaciju

    double theta = rotation();
    double dy = korak * qSin(qDegreesToRadians(theta));
    double dx = korak * qCos(qDegreesToRadians(theta));

    setPos(x()+id1*dx, y()+id2*dy);
}

void Lopta::move_back(QPointF tacka)
{
    Q_UNUSED(tacka);
    //tacka koja ide unatrag vraca se ka prethodnoj tacki dok ne udari u lopte sa putanje

    ideUnatrag=true;
    krajnja=tacke[index-1];
    id1=-1;
    id2=-1;
}

void Lopta::move_back(int id)
{
    //tacka koja ide unatrag vraca se ka prethodnoj tacki dok ne udari u lopte sa putanje
//    QPointF transliraj(id*size/2, 0);
    rotateToPoint(tacke[index-1]);
    double theta = rotation();
    double dy = size * qSin(qDegreesToRadians(theta));
    double dx = size * qCos(qDegreesToRadians(theta));

    setPos(x()+id*dx, y()+id*dy);
    rotateToPoint(krajnja);
    qDebug()<<"pre "<<pos();
//    setPos(x()+id*size/2, y());
    qDebug()<<"posle "<<pos();


}

void Lopta::setIndexBoje(int indeks)
{
   boja = niz_slika[indeks];

}

void Lopta::stopTimer()
{
 timer->stop();
}

void Lopta::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(0, 0, size, size, boja);
}

QRectF Lopta::boundingRect() const
{
    return QRectF(0, 0, size, size);
}

void Lopta::generisi_boju()
{
    indexBoje = rand() % 4;
    boja=niz_slika[indexBoje];
}

void Lopta:: setKorak(int k){ korak=k; }

//nisam jos sigurna dal ce nam trebati ovaj metod..
void Lopta::setIndex(int novi_indeks)
{
    index_u_nizu=novi_indeks;
}

void Lopta::setReverse()
{
    ideUnatrag=true;
    doUdara=true;
    pocetniStop=true;
    ostaloVremena=500; //u milisendama hocu
    ostaloDuzine=0;
}
void Lopta::setReverse(float distance)  ///preko rastojanja do prethodne lopte vidimo koliko ce dugo da ide unatrag
{
    ideUnatrag=true;
    doUdara=true;
    pocetniStop=true;
    ostaloVremena=0; //u milisendama hocu
    ostaloDuzine=distance;
}

bool Lopta::poredi(const Lopta *other)
{
    if(this->indexBoje==other->indexBoje)
        return true;
    return false;
}



