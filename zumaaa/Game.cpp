#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "CrnaRupa.h"
#include <QtMath>
#include <QPainter>
#include "Lopta.h"
#include "Putanja.h"

Game::Game(QWidget *parent)
{
    Q_UNUSED(parent);
    //ova klasa je nas view
    QGraphicsScene * scene = new QGraphicsScene();
    //podesavamo da je view fiksne velicine u da je ta velicina ista za scenu i za view, i da je scena tamo gde je view
    //scena moze ogromna da bude, nama bi bila sigurno jer se ona siri kako se povecavaju koordinate SVIH objekata
    //nama lete ove lopte, pa bi se pravio skrol bar pored. Mi vidimo samo deo takve scene, to je razlika izmedju view i scene
    //ovim podesavamo da kad nesto ode van, mi gaignorisemo, nestaje, jer nije deo scene (pazi, jos se cuva u memoriji,
    //treba to osloboditi u LoptaUUstima klasi!!)
    //pozijija pravougaonika se gleda u odnosu na view,
    scene->setSceneRect(0, 0, 800, 600);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);

    // Postavljanje zabice
    // Zabica(x, y, visina, sirina)
    Zabica * zabica = new Zabica(200, 250, 100, 100);
//    zabica->setRect(0, 0, 100, 100);
//    zabica->setPos(200, 250);
    zabica->setFlag(QGraphicsItem::ItemIsFocusable);
    zabica->setFocus();
    scene->addItem(zabica);

    // postavljamo precnik lopte, ovo bi trebalo da bude i kod lopte iz putanje i kod lopte iz usta
    int precnik = 50;

    // Postavljanje putanje
    // Putanja(precnik, brojLopti) precnik se odnosi na lopte koje putanja kreira
    Putanja *putanja = new Putanja(precnik, 10);
    scene->addItem(putanja);

    // Postavljanje Crne Rupe
    // CrnaRupa(x, y, visina, sirina)
    CrnaRupa * crna_rupa = new CrnaRupa(200, 290, 70, 70);
    scene->addItem(crna_rupa);

    // Postavljanje Score
    score = new Score();
    scene->addItem(score);

    // Postavljanje Zivot
    zivot =new Zivot();
    zivot->setPos(score->x(), score->y()+20);
    scene->addItem(zivot);

    //// FUN FACT: ako iskljucimo da se ne prikazuje zivot i score ne radi rotacija!!!

    connect(this, SIGNAL(mousePressEvent(QMouseEvent*)), zabica, SLOT(klik(QMouseEvent*)));
    connect(this, SIGNAL(mouseMoveEvent(QMouseEvent*)), zabica, SLOT(rotiraj(QMouseEvent*)));



    //ovim gole kazemo da je rekt onaj element koji reaguje na keyboard i mouse evente, tj u fokusu je u tom smislu


    //treba nam view da bi vizualizovali scenu, view je widget pa je po defaultu nevidljiv, zato mora show
    //ova klasa je view; view javlja sceni da je nesto prisnuto ili tk neki event, i scena trazi koji u fokusu i javi njemu sta se desilo,
    //koji event, pa po definiciji odgovarajucih fja u toj klasi se vrse neke izmene

    show();


}


