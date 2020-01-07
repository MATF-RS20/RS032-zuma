#include "Putanja.h"
#include <QGraphicsScene>
#include <QDebug>
#include <algorithm>
#include <QFile>
#include "Game.h"

extern QGraphicsScene *scene;
extern Game* game;

Putanja::Putanja(int precnik, int brojLopti, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , maxSize(brojLopti)
    , precnik(precnik)
{
    //zadajemo listu tacaka
//    tacke << QPointF(800+precnik, 60) << QPointF(80, 60) << QPointF(55, 75) << QPointF(40, 90) << QPointF(55, 120) << QPointF(80, 130) << QPointF(700, 130) << QPointF(705, 500) << QPointF(690, 550) << QPointF(70, 550) << QPointF(45, 535) << QPointF(45, 205) << QPointF(55, 190) << QPointF(620, 190) << QPointF(625, 200) << QPointF(630, 490) << QPointF(125, 490) << QPointF(125, 260);
    // citamo tacke iz datoteke
    QFile inputFile(":/images/images/level1.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QStringList koordinate = in.readLine().split(" ");

          tacke << QPointF(koordinate[0].toInt(), koordinate[1].toInt());
       }
       inputFile.close();
    }
    else {
        qDebug() << "Bad input file error!";
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(create()));

    timer->start(800);
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
    if(count >= maxSize) {
        timer->stop();
        return;
    }
    // pravimo novu loptu i dodajemo je u listu i na scenu
    Lopta *lopta = new Lopta(precnik, tacke);
    if(ind_udareno)
        lopta->move_back(1);
    lopte.append(lopta);
    scene()->addItem(lopta);
    //connect(lopta, SIGNAL(sudar(QPointF)), this, SLOT(susedne(QPointF)));
    count++;

}

void Putanja::dodaj_loptu(Lopta * l)
{
    //qDebug()<<tacka;
    int indeks=lopte.indexOf(l);

    ind_udareno=true;

        //qDebug()<<(x)->pos();
        //emit pomeri_se(tacka);
        Lopta *lopta = new Lopta(precnik, tacke);
       // int x_razlika =lopte[indeks]->x()-lopte[indeks]->krajnja.x();
       // int y_razlika =lopte[indeks]->y()-lopte[indeks]->krajnja.y();
        lopta->setPos(lopte[indeks]->pos());
        //qDebug()<<"test tacka"<<QPointF(100, 200)/2;
        lopta->setIndexBoje(game->zabica->loptaUsta->indexBoje);
        qDebug()<<"pozicija nove"<<lopta->pos();
        lopta->krajnja=l->krajnja;

        lopte.insert(indeks, lopta);
        scene()->addItem(lopta);

    for(int j=0; j<lopte.size(); j++){
         // QPointF poz = lopte[j]->pos();
         if(j<=indeks){
             lopte[j]->move_back(-1);
             //lopte[j]->timer->stop();
         }else{

         }


    }

    ind_udareno=false;


    timer = new QTimer(this);


}
//ubrzavanje loptica kada treba da ulete u rupu
void Putanja:: ubrzaj(int k)
{
    foreach(auto lopta, lopte)
    {
        lopta->setKorak(k);
    }
}

void Putanja:: zaustaviLopte()
{
    foreach(auto lopta, lopte)
        lopta->setKorak(0);
}


int Putanja:: getIndeksLopte(Lopta* lopta)
{
    return lopte.indexOf(lopta);
}

Lopta* Putanja::susedne(Lopta *lopta)
{
    int n=lopte.size();
    int indeks = lopte.indexOf(lopta);
    qDebug()<<indeks;
    int i=indeks;
    Lopta* poslednja;

    while(i>=0 && (lopte[indeks]->indexBoje==lopte[i]->indexBoje || lopte[i]->isDeleted)){
        if(lopte[i]->isDeleted)
            i--;
        else {
            indeksi.append(i);
            i--;
        }
    }
    i=indeks+1;
    while(i<n && (lopte[indeks]->indexBoje==lopte[i]->indexBoje || lopte[i]->isDeleted)){
        if(lopte[i]->isDeleted)
            i++;
        else {
            indeksi.append(i);
            i++;
        }
    }
    qDebug()<<indeksi;
    int indeks_prve=(*std::min_element(indeksi.begin(), indeksi.end()));
    int indeks_posle_poslednje=(*std::max_element(indeksi.begin(), indeksi.end()));
    //vracamo se ka onoj koja je najdalja u nizu, tj onoj koja ima najveci indeks

    poslednja=lopte[indeks_posle_poslednje];
    int broj_obrisanih=indeksi.size();
    qDebug()<<indeks_posle_poslednje;
    if(broj_obrisanih<2) {
        indeksi.clear();
        lopta->u_koliziji = false;
        return lopta;
    }

   /* auto pocetak = lopte.mid(0, indeks_prve);
    auto kraj = lopte.mid(indeks_posle_poslednje);
    qDebug()<<pocetak;
    qDebug()<<kraj;
    lopte.erase(lopte.begin(), lopte.end());
    lopte.reserve(pocetak.size()+kraj.size());
    lopte.insert(lopte.end(), pocetak.begin(), pocetak.end());
    lopte.insert(lopte.end(), kraj.begin(), kraj.end());*/


     foreach(auto &j, indeksi) {
        if(!lopte[j]->isDeleted)
            unisti_loptu(lopte[j]);
     }

     indeksi.clear();

     for(int j=0; j<lopte.size(); j++){
        if(j<indeks_prve && !lopte[j]->isDeleted){
            //lopte[j]->indeks_u_nizu=j-broj_obrisanih;
            lopte[j]->move_back(poslednja->pos());
        }
     }


 /*   foreach(auto &j, indeksi){
        if(j+broj_obrisanih>=n){
            delete lopte[j];
        }
        lopte.move(j, j+broj_obrisanih);
    }
    for(int j =n-indeks_prve; j<=n; j++)
        delete lopte[j];*/

    //lopte.delete(lopte.end()-broj_obrisanih, lopte.end());

    //  qDebug()<<lopte;
   //  for(int j=indeks_prve; j<lopte.size(); j++){
     //   lopte.replace(j, lopte[j+broj_obrisanih]);
     //}
    // vector<Lopta*>::const_iterator first = lopte.begin()+indeks_posle_poslednje;
    // vector<Lopta*>::const_iterator last = lopte.end();
    //lopte.reserve(n-broj_obrisanih);

    return poslednja;

}

void Putanja::resetuj_kolizije_lopti()
{
    for(auto &l: lopte)
        static_cast<Lopta*>(l)->u_koliziji = false;
}

void Putanja:: unisti_loptu(Lopta* lopta )
{
    lopta->isDeleted = true;
    delete lopta;
    game->score->increase();
}
