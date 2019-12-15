#include "LoptaUUstima.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Game.h"
#include <QEvent>
#include <QMouseEvent>
#include <QtMath>
#include <QDebug>

extern Game * game; //jer u game imamo nas skor i hocemo da mu pristupimo i menjamo

LoptaUUstima::LoptaUUstima(int x, int y,  int precnik, QPointF p){
    setRect(x, y, precnik, precnik);
    setTransformOriginPoint(this->rect().center());
    QLineF ln(this->rect().center(), p);
    setRotation(-1*ln.angle());
}

void LoptaUUstima::move()
{
    //pre nego sto se pomerimo hocemo da proverimo da li smo se sudarili sa putanjom i lopticama
    //collidingItems metod nam vraca listu svih objakata sa kojim se ovaj koji zove sudara, a zove ova nasa loptauustims
    QList<QGraphicsItem *> colliding_items= collidingItems();
    int n = colliding_items.size();
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
    int korak = 10;
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


}
// Implementacija setera
void LoptaUUstima::postaviAB(double a_, double b_) {
    a = a_;
    b = b_;
}


