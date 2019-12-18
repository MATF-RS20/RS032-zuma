#include "LoptaUUstima.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Game.h"
#include <QEvent>
#include <QMouseEvent>
#include <QtMath>
#include <QDebug>
//#include "Game.h"
#include "Putanja.h"

extern Game * game ; //jer u game imamo nas skor i hocemo da mu pristupimo i menjamo



LoptaUUstima::LoptaUUstima(int x, int y,  int precnik, QPointF p)
: QGraphicsObject()
,size(precnik)
{
    //setRect(x, y, precnik, precnik);
    //setTransformOriginPoint(this->rect().center());
    //QLineF ln(this->rect().center(), p);

   // QPointF center = QPointF(this->pos().x()+precnik/2, this->pos().y()-precnik/2);  ////


    setTransformOriginPoint(boundingRect().center());
    QLineF ln(boundingRect().center(), p);
    setRotation(-1*ln.angle());
    connect(this, SIGNAL(sudar(QPointF)), game->putanja , SLOT(dodaj_loptu(QPointF)));
}

void LoptaUUstima::move()
{

    int korak=10;
    QList<QGraphicsItem *> colliding_items= collidingItems();
    int n = colliding_items.size();
   // qDebug() <<n;

    foreach(auto &x ,colliding_items){
        if(typeid(*x)==typeid(Lopta)){
            emit sudar(x->pos());
            //connect(this, SIGNAL(sudar(QPointF)), game->putanja , SLOT((&dodaj_loptu(QPointF))));
            korak=0;
            //delete this;
            //return;
            //connect(this, SIGNAL(sudar(QPointF)), game->putanja , SLOT((&dodaj_loptu(QPointF))));
        }

        //qDebug()<<x;
    }
    //nisam jos definisala ni loptu ni boju pa cemo ovo da zakomentarisemo
    //i ovde brise samo ako se udari isti, a treba ceo uzastopni niz njih, tako da i to treba modifikovati

    /*for(int i=0; i<n; i++){
        if(typeid(*(colliding_items[i]))==typeid(Lopta) & (boja==Lopta->boja())){

            //i ovde hocemo da povecamo score
            game->score->increase();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }
    }*/


    // Postavljamo poziciju na koju treba da ode lopta
    double theta = rotation();
    //int korak = 10;
    double dy = korak * qSin(qDegreesToRadians(theta));
    double dx = korak * qCos(qDegreesToRadians(theta));
    setPos(x()+dx, y()+dy);
    //da ne bi trosili memoriju, oslobadjamo se onih loptica koje izadju van scene
    //+rect.height je da bi brisali tek kad skroz izadje iz scene
    ///TODO uradi za sve strane scene
        ///
        ///
        /// FATAL ERROR:
    //    if(pos().y()+rect().height()<0){
    //        scene()->removeItem(this);
    //        delete this;
    //    }
    //    if(pos().x()+rect().width()<0){
    //        scene() -> removeItem(this);
    //        delete this;
    //    }
    //    if(pos().x()<0){
    //        scene() -> removeItem(this);
    //        delete this;
    //    }
    //    if(pos().y()<0){
    //        scene() -> removeItem(this);
    //        delete this;
    //    }

        if(pos().y()>game->rect().height()-250-25){
            scene()->removeItem(this);
            delete this;
        }
        else if(pos().x()>game->rect().width()-200-25){
            scene() -> removeItem(this);
            delete this;
        }
        else if(pos().x()<-200-75){
            scene() -> removeItem(this);
            delete this;
        }
        else if(pos().y()<-250-75){
            scene() -> removeItem(this);
            delete this;
        }




}
// Implementacija setera
void LoptaUUstima::postaviAB(double a_, double b_) {
    a = a_;
    b = b_;
}

void LoptaUUstima::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //QPixmap pixmap("/home/tetejesandra/Desktop/Fax/zuma/RS032-zuma/zumaaa/images/roze.png");
    painter->drawPixmap(250, 300, size, size, boja);
}

QRectF LoptaUUstima::boundingRect() const
{
    return QRectF(250, 300, size, size);
}

void LoptaUUstima::promeni_boju(){

        QVector <QPixmap> niz_slika;
        niz_slika.resize(4);
        niz_slika[0]=QPixmap("/home/tetejesandra/Desktop/Fax/zuma/RS032-zuma/zumaaa/images/roze.png");
        niz_slika[1]=QPixmap("/home/tetejesandra/Desktop/Fax/zuma/RS032-zuma/zumaaa/images/plava.png");
        niz_slika[2]=QPixmap("/home/tetejesandra/Desktop/Fax/zuma/RS032-zuma/zumaaa/images/zelena.png");
        niz_slika[3]=QPixmap("/home/tetejesandra/Desktop/Fax/zuma/RS032-zuma/zumaaa/images/ljubicasta.png");
        int indeks = rand() % 4;
        boja= niz_slika[indeks];

}




