#include "Lopta.h"
#include <QTimer>
#include <QtMath>
#include <random>
#include <iterator>
#include <QDebug>
#include "CrnaRupa.h"
// Stari konstruktor

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
{
    //Q_UNUSED(parent);
    generisi_boju();
    // inicijalizujemo tacke
    tacke = tacke_;
    index = 0;
    ///TODO: posebna funkcija za postavljanje dimenzije i pozicije
    /// mozda bi bilo dobro da je to neki konstruktor
    //setRect(0, 0, precnik, precnik); // dimenzije lopte na 50x50               /////OVO MOZDA NE TREBA ZAKOMENTARISANO, ali ne moze zbog novog nasledjivanja
    setPos(tacke[0]); // pocetna tacka nase lopte je prva tacka iz liste tacke
    index++;
    krajnja = tacke[index]; // ovim samo kazemo da je destinacija naredna tacka
    //size = 50; // velicina je je precnik ili u nasem slucaju visina = sirina = precnik
    //boja = QPixmap("/home/tetejesandra/Desktop/Fax/zuma/RS032-zuma/zumaaa/images/roze.png");
    // inicijalizujemo da se sve transformacije odnose na centar lopte
    setTransformOriginPoint(25, 25);

    // rotiramo da se krecemo ka prvoj tacki
    // trenutnu destinaciju, kao ciljnaTacka
    rotateToPoint(krajnja);
    // dodat timer
    ///TODO: timer da bude privatna promenljiva, tako da mozemo da kazemo lopta->timer->stop()
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

void Lopta::kolizija_crna_rupa()
{
    QList<QGraphicsItem *> items = collidingItems(); // kako da proverim da li je unutar a ne samo presek?
    for(int i = 0; i < items.size(); ++i) {
        if(typeid(*(items[i])) == typeid(CrnaRupa)) {
            if(size > 35) { // vrednosti 35 i 50 zavise od velicine lopte i crne rupe. Mozda neki metod za to?
                setScale(size/50); /// TODO pored scale mozda neki kontrast, da izgleda sve tamnije kako sve vise upada
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
        index++;
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
    qDebug()<<"sad mi je id -1"<<tacka;
    tacka.x() > this->x() ? id1= -1 : 1;
    tacka.y() > this->y() ? id2= -1 : 1;

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
    niz_slika[2]=QPixmap(":/images/zelena.png");
    niz_slika[3]=QPixmap(":/images/ljubicasta.png");
    int indeks = rand() % 4;
    boja=niz_slika[indeks];
}
