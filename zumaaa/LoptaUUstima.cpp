#include "LoptaUUstima.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Game.h"
#include <QEvent>
#include <QMouseEvent>
#include <QtMath>
#include <QDebug>
#include "Putanja.h"
#include "Lopta.h"

extern Game * game ; //jer u game imamo nas skor i hocemo da mu pristupimo i menjamo



LoptaUUstima::LoptaUUstima(int x, int y,  int precnik, QPointF p)
: QGraphicsObject()
,size(precnik)
,x(x)
,y(y)
{
    setTransformOriginPoint(boundingRect().center());
    QLineF ln(boundingRect().center(), p);
    setRotation(-1*ln.angle());
    connect(this, SIGNAL(sudar(Lopta*)), game->putanja , SLOT(dodaj_loptu(Lopta*)));
}

void LoptaUUstima::move()
{
    int korak=10;
    QList<QGraphicsItem *> colliding_items= collidingItems();


    foreach(auto &x ,colliding_items){
//        if(static_cast<Lopta*>(x)->isDeleted || static_cast<Lopta*>(x)->u_koliziji) break;

        //ovde ima greska, tj pukne program kad udari u dve umesto samo u jednu, vrv jer nesto obrise, pa posle hocemo da pristupimo
        if(typeid(*x)==typeid(Lopta)){
            if(static_cast<Lopta*>(x)->u_koliziji) break;

            static_cast<Lopta*>(x)->u_koliziji = true;

            if(indexBoje==static_cast<Lopta*>(x)->indexBoje){
                qDebug()<<"iste su boje";
                Lopta* poslednja=game->putanja->susedne(static_cast<Lopta*>(x));
                if(poslednja==static_cast<Lopta*>(x))
                    emit sudar(static_cast<Lopta*>(x));

                //delete x;
                game->score->increase();
                delete this;
                continue;
            }
            else if(indexBoje!=static_cast<Lopta*>(x)->indexBoje) {

                static_cast<Lopta*>(x)->u_koliziji = false;
                qDebug()<<"nisu iste boje";
                //static_cast<Lopta*>(x)->move_back();
                emit sudar(static_cast<Lopta*>(x));

                delete this;
                break;

            }


            korak=0;
            //delete this;
            //return;
            //connect(this, SIGNAL(sudar(QPointF)), game->putanja , SLOT((&dodaj_loptu(QPointF))));
        }

        //qDebug()<<x;
    }

    // Postavljamo poziciju na koju treba da ode lopta
    double theta = rotation();
    //int korak = 10;
    double dy = korak * qSin(qDegreesToRadians(theta));
    double dx = korak * qCos(qDegreesToRadians(theta));
    setPos(pos().x()+dx, pos().y()+dy);

    //da ne bi trosili memoriju, oslobadjamo se onih loptica koje izadju van scene
    //+rect.height je da bi brisali tek kad skroz izadje iz scene
    if(pos().y() > game->rect().height() - game->zabica->boundingRect().y()){
        scene()->removeItem(this);
        delete this;
    }
    else if(pos().x() > game->rect().width() - game->zabica->boundingRect().x()){
        scene() -> removeItem(this);
        delete this;
    }
    else if(pos().x() < -game->zabica->boundingRect().x()-2*size){
        scene() -> removeItem(this);
        delete this;
    }
    else if(pos().y() < -game->zabica->boundingRect().y()-2*size){
        scene() -> removeItem(this);
        delete this;
    }

}
void LoptaUUstima::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(x, y, size, size, boja);
}

QRectF LoptaUUstima::boundingRect() const
{
    return QRectF(x, y, size, size);
}

void LoptaUUstima :: setBoja(int indeks)
{
    QVector <QPixmap> niz_slika;
    niz_slika.resize(4);
    niz_slika[0]=QPixmap(":/images/roze.png");
    niz_slika[1]=QPixmap(":/images/plava.png");
    niz_slika[2]=QPixmap(":/images/zelena.png");
    niz_slika[3]=QPixmap(":/images/ljubicasta.png");
    boja= niz_slika[indeks%4];
    indexBoje=indeks;
}

LoptaUUstima::~LoptaUUstima()
{
    game->putanja->resetuj_kolizije_lopti();
}
