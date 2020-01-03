#include "Putanja.h"
#include <QGraphicsScene>
#include <QDebug>
#include <algorithm>
extern QGraphicsScene *scene;

Putanja::Putanja(int precnik, int brojLopti, QGraphicsItem *parent)
    : QGraphicsObject(parent)
    , maxSize(brojLopti)
    , precnik(precnik)
{
    //zadajemo listu tacaka
    tacke << QPointF(800+precnik, 60) << QPointF(80, 60) << QPointF(55, 75) << QPointF(40, 90) << QPointF(55, 120) << QPointF(80, 130) << QPointF(700, 130) << QPointF(705, 500) << QPointF(690, 550) << QPointF(70, 550) << QPointF(45, 535) << QPointF(45, 205) << QPointF(55, 190) << QPointF(620, 190) << QPointF(625, 200) << QPointF(630, 490) << QPointF(125, 490) << QPointF(125, 260);

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
    if(lopte.size() >= maxSize) {
        timer->stop();
        return;
    }
    // pravimo novu loptu i dodajemo je u listu i na scenu
    Lopta *lopta = new Lopta(precnik, tacke);
    lopte.append(lopta);
    scene()->addItem(lopta);
    connect(this, SIGNAL(pomeri_se(QPointF)), lopta, SLOT(move_back(QPointF)));
}

void Putanja::dodaj_loptu(QPointF tacka)
{
    //qDebug()<<tacka;
    foreach (auto x, lopte) {
        //qDebug()<<(x)->pos();
        emit pomeri_se(tacka);
    }
    timer = new QTimer(this);


}
//ubrzavanje loptica kada treba da ulete u rupu
void Putanja:: ubrzaj(int k)
{
    foreach(auto lopta, lopte)
    {
        lopta->setKrak(k);
    }
}

void Putanja:: zaustaviLopte()
{
    foreach(auto lopta, lopte)
        lopta->setKrak(0);
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

    while(i>=0 && lopte[indeks]->indexBoje==lopte[i]->indexBoje){
        indeksi.append(i);
        i--;
    }
    i=indeks+1;
    while(i<n && lopte[indeks]->indexBoje==lopte[i]->indexBoje){
        indeksi.append(i);
        i++;
    }
    qDebug()<<indeksi;
    int indeks_prve=(*std::min_element(indeksi.begin(), indeksi.end()));
    int indeks_posle_poslednje=(*std::max_element(indeksi.begin(), indeksi.end()))+1;
    //vracamo se ka onoj koja je najdalja u nizu, tj onoj koja ima najveci indeks
    poslednja=lopte[indeks_posle_poslednje];
    int broj_obrisanih=indeksi.size();
    qDebug()<<indeks_posle_poslednje;

    if(broj_obrisanih<2)
        return lopta;

   /* auto pocetak = lopte.mid(0, indeks_prve);
    auto kraj = lopte.mid(indeks_posle_poslednje);
    qDebug()<<pocetak;
    qDebug()<<kraj;
    lopte.erase(lopte.begin(), lopte.end());
    lopte.reserve(pocetak.size()+kraj.size());
    lopte.insert(lopte.end(), pocetak.begin(), pocetak.end());
    lopte.insert(lopte.end(), kraj.begin(), kraj.end());*/


     foreach(auto &j, indeksi)
        delete lopte[j];

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
