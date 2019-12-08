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

    Zabica * zabica = new Zabica();
    CrnaRupa * crna_rupa = new CrnaRupa();
    scene->addItem(crna_rupa);
    //gornji levi ugao na (0, 0), pa sirina i visina
    zabica->setRect(0, 0, 100, 100);
    zabica->setPos(200, 250);
    zabica->setFlag(QGraphicsItem::ItemIsFocusable);
    zabica->setFocus();
   // zabica->rotiraj();
    scene->addItem(zabica);


//    Lopta * lopta = new Lopta();
//    lopta->setRect(0, 0, 50, 50);
//    lopta->setPos(300, 0);
//    scene->addItem(lopta);
    Putanja *putanja = new Putanja();
    scene->addItem(putanja);
    emit putanja->create();

    ///TODO: Treba nam metod koji ce na svakih n milisekundi da napravi novu Loptu
    /// ta lopta ce takodje ici istom putanjom jer nam je za sada putanja zadata u klasi Lopta
    ///TODO: Putanja bi trebala da se zada odavde, tj klasa Game bi trebala da ima putanje (mozda, ovo je samo ideja za sada)

//    Lopta * lopta2 = new Lopta();
//    lopta2->setRect(0, 0, 50, 50);
//    lopta2->setPos(400, 400);
//    scene->addItem(lopta2);

//    Putanja * putanja = new Putanja();
//    putanja->setLine(1,1,100,100);
//    putanja->setParent(parent);
//    scene->addItem(putanja);
    score = new Score();
    scene->addItem(score);
    zivot =new Zivot();
    zivot->setPos(score->x(), score->y()+20);
    scene->addItem(zivot);
    connect(this, SIGNAL(mousePressEvent(QMouseEvent*)), zabica, SLOT(klik(QMouseEvent*)));
    connect(this, SIGNAL(mouseMoveEvent(QMouseEvent*)), zabica, SLOT(rotiraj(QMouseEvent*)));



    //ovim gole kazemo da je rekt onaj element koji reaguje na keyboard i mouse evente, tj u fokusu je u tom smislu


    //treba nam view da bi vizualizovali scenu, view je widget pa je po defaultu nevidljiv, zato mora show
    //ova klasa je view; view javlja sceni da je nesto prisnuto ili tk neki event, i scena trazi koji u fokusu i javi njemu sta se desilo,
    //koji event, pa po definiciji odgovarajucih fja u toj klasi se vrse neke izmene

    show();


}


