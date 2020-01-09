#include "Putanja.h"
#include <QGraphicsScene>
#include <QDebug>
#include <algorithm>
#include <QFile>
#include "Game.h"
#include <QtMultimedia/QMediaPlayer>

extern QGraphicsScene *scene;
extern Game* game;

Putanja::Putanja(int precnik, int brojLopti, QGraphicsObject *parent)
    : QGraphicsObject(parent)
    , maxSize(brojLopti)
    , precnik(precnik)
{
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

void Putanja::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
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
    int indeks=lopte.indexOf(l);

    ind_udareno=true;

    Lopta *lopta = new Lopta(precnik, tacke);

    lopta->setPos(lopte[indeks]->pos());

    lopta->setIndexBoje(game->zabica->loptaUsta->indexBoje);
//        qDebug()<<"pozicija nove"<<lopta->pos();
    lopta->krajnja=l->krajnja;

    lopte.insert(indeks, lopta);
    scene()->addItem(lopta);

    // postavljanje zvuka udara
    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/sounds/sounds/ubacena.ogg"));
    player->setVolume(40);
    player->play();


    for(int j=0; j<lopte.size(); j++){
         if(j<=indeks){
             lopte[j]->move_back(-1);
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
    int indeks_posle_poslednje=(*std::max_element(indeksi.begin(), indeksi.end()))+1;
    //vracamo se ka onoj koja je najdalja u nizu, tj onoj koja ima najveci indeks

    if(indeks_posle_poslednje < lopte.size())
        poslednja=lopte[indeks_posle_poslednje];
    else
        poslednja=lopte[indeks_prve-1]; // indkes pre prve

    int broj_obrisanih=indeksi.size();

    qDebug()<<indeks_posle_poslednje;
    if(broj_obrisanih<2) {
        indeksi.clear();
        lopta->u_koliziji = false;
//        game->putanja->resetuj_kolizije_lopti();
        return lopta;
    }

     foreach(auto &j, indeksi) {
        if(!lopte[j]->isDeleted)
            unisti_loptu(lopte[j]);
     }

     // postavljanje zvuka pogotka
     QMediaPlayer *player = new QMediaPlayer;
     player->setMedia(QUrl("qrc:/sounds/sounds/pogodjene.ogg"));
     player->setVolume(40);
     player->play();

     indeksi.clear();

    if(indeks_posle_poslednje < lopte.size())  // ne vracaj ako iza nema nista
        for(int j=0; j<lopte.size(); j++){
            if(j<indeks_prve /*&& !lopte[j]->isDeleted*/){
                lopte[j]->move_back(poslednja->pos());
            }
        }





//    game->putanja->resetuj_kolizije_lopti();

    return poslednja;
}

void Putanja::resetuj_kolizije_lopti()
{
    for(auto &l: lopte)
        if(!static_cast<Lopta*>(l)->isDeleted)
            static_cast<Lopta*>(l)->u_koliziji = false;
}

void Putanja:: unisti_loptu(Lopta* lopta )
{
    lopta->isDeleted = true;
    lopta->stopTimer();
    delete lopta;
    game->score->increase();
}

bool Putanja:: prazneLopte()
{
    for(int i =0; i<lopte.size(); i++)
        if(!lopte[i]->isDeleted)
            return false;
    return true;
}
