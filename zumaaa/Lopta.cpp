#include "Lopta.h"
#include <QTimer>
#include <QtMath>
#include <random>
#include <iterator>
#include <QDebug>
#include "CrnaRupa.h"
// Stari konstruktor
#include "Putanja.h"
#include "Game.h"

extern Game * game;

//Lopta::Lopta(QGraphicsItem *parent)
//: QGraphicsObject(parent)
//{
//   // Q_UNUSED(parent);
//    setPos(500,100); // pocetna tacka nase lopte
//    tacke << QPointF(0,0);
//    setTransformOriginPoint(25, 25);
//    index = 0;
//    krajnja = tacke[0];
//    rotateToPoint(krajnja);
//    QTimer * timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
//    timer->start(200);
//}
// Novi konstruktor, sa ovim kazem da svaka lopta ima svojstvo kretanja i ima listu tacaka kuda da se krece
Lopta::Lopta(int precnik, QList<QPointF> tacke_, QGraphicsItem *parent)
: QGraphicsObject(parent)
,size(precnik)
,ideUnatrag(false)
,pocetniStop(false)
,doUdara(false)
{
    //Q_UNUSED(parent);
    generisi_boju();
    // inicijalizujemo tacke
    tacke = tacke_;
    index = 0;
    pocetna_dim = size;

    setPos(tacke[0]); // pocetna tacka nase lopte je prva tacka iz liste tacke
    index++;
    krajnja = tacke[index]; // ovim samo kazemo da je destinacija naredna tacka
    //size = 50; // velicina je je precnik ili u nasem slucaju visina = sirina = precnik
    //boja = QPixmap("/home/tetejesandra/Desktop/Fax/zuma/RS032-zuma/zumaaa/images/roze.png");
    // inicijalizujemo da se sve transformacije odnose na centar lopte
    setTransformOriginPoint(precnik/2, precnik/2);

    // rotiramo da se krecemo ka prvoj tacki
    // trenutnu destinaciju, kao ciljnaTacka
    rotateToPoint(krajnja);
    // dodat timer
    ///TODO: timer da bude privatna promenljiva, tako da mozemo da kazemo lopta->timer->stop()
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}
/*
Lopta::Lopta(const Lopta &l2)
{
    size=l2.size;
    tacke=l2.tacke;
    index=l2.index;
    krajnja=l2.krajnja;
    setPos(l2.pos());
}*/
// funkcija rotacije ka ciljnoj tacki
void Lopta::rotateToPoint(QPointF p)
{
    QLineF ln(pos(), p);
    setRotation(-1*ln.angle());
}

void Lopta::kolizija_crna_rupa()
{
    QList<QGraphicsItem *> items = collidingItems(); // kako da proverim da li je unutar a ne samo presek?
    for(int i = 0; i < items.size(); ++i) {
        if(typeid(*(items[i])) == typeid(CrnaRupa)) {

            //smanjujemo broj zivota za svaku lopticu kojs udje u rupu
            game->zivot->decrease();

            if(size > pocetna_dim/4) {
                setScale(size/pocetna_dim); /// TODO pored scale mozda neki kontrast, da izgleda sve tamnije kako sve vise upada
                size -= 1;
            }
            else {
                delete this;
            }
        }
    }
}
// funkcija koja se poziva pri timeru
void Lopta::move()
{
    // ako smo napravili loptu iz putanje onda imamo sigurno vise od 2 tacke
    kolizija_crna_rupa();

    //ako lopta ide unatrag proveravamo dal je udarila u neku koja ide napred i resetujemo indikatore
    if(ideUnatrag){
        QList<QGraphicsItem *> colliding_items= collidingItems();
       // qDebug()<<colliding_items.size();

        foreach(auto &x ,colliding_items){
           if(typeid(*x)==typeid(Lopta) && static_cast<Lopta*>(x)->ideUnatrag==false){
               krajnja=tacke[index];
               id1=1;
               id2=1;
               ideUnatrag=false;
               if(static_cast<Lopta*>(x)->indexBoje==this->indexBoje){
                   qDebug()<<"iste boje kasniji sudar";
                   Lopta* poslednja=game->putanja->susedne(static_cast<Lopta*>(x));
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
        // ako vise nemamo tacaka stajemo
        // S obzirom da je crna rupa na kraju putanje, tj na kraju indeksa tacaka
        // i mi unistavamo loptu kad dodje do crne rupe ova provera nam vise ne treba :)
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
    //tacka koja ide unatrag vraca se ka prethodnoj tacki dok ne udari u lopte sa putanje
    qDebug()<<tacka<<this;
    ideUnatrag=true;
    krajnja=tacke[index-1];
    id1=-1;
    id2=-1;


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
    QVector <QPixmap> niz_slika;
    niz_slika.resize(4);
    niz_slika[0]=QPixmap(":/images/roze.png");
    niz_slika[1]=QPixmap(":/images/plava.png");
   // niz_slika[2]=QPixmap(":/images/zelena.png");
  //  niz_slika[3]=QPixmap(":/images/ljubicasta.png");
    indexBoje = rand() % 2;
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
}



