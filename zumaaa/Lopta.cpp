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

    //ako smo blizu jedne tacke (5px), prelazimo na narednu
    QLineF ln(pos(), krajnja);
    if(ln.length()<5){

        if(!ideUnatrag)  //ako idemo unatrag, vracammo se na prethodnu ciljnu tacku
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

    if(abs(x()-krajnja.x())<=size/2){
        smer = 'v';
        if(krajnja.y()-y()>=0)
            orij='d';
        else
            orij='g';
    }
    if(abs(y()-krajnja.y())<=size/2){
        smer='h';
        if(x()-krajnja.x()>=0)
            orij='l';
        else
            orij='d';
    }
    setPos(x()+id1*dx, y()+id2*dy);
}

void Lopta::move_back(QPointF tacka)
{

    //qDebug()<<"smer je"<<smer<<orij<<indexBoje<<tacka;

    if(smer=='h'){

        if(tacka.x()-x()<=0 && orij=='l'){
            ideUnatrag=true;
         }else if(tacka.x()-x()>=0 && orij=='d'){
            timer->stop();
          }
    }else if(smer=='v'){
        if(tacka.x()-x()<=0 && orij=='g'){
            timer->stop();
         }else if(tacka.x()-x()>=0 && orij=='d'){
            timer->stop();
          }
    }

    //tacka.x() > this->x() ? id1= -1 : 1;
    //tacka.y() > this->y() ? id2= -1 : 1;


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



