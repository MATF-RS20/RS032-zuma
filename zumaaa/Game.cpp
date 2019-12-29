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

    QGraphicsScene * scene = new QGraphicsScene();
    scene->setBackgroundBrush(QBrush(QPixmap(":/images/level1").scaledToHeight(600)));

    scene->setSceneRect(0, 0, 800, 600);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800, 600);

    // Postavljanje putanje
    // Putanja(precnik, brojLopti) precnik se odnosi na lopte koje putanja kreira
    putanja = new Putanja(this->precnik, 10);
    scene->addItem(putanja);

    zabica = new Zabica(350, 300, 120, this->precnik);
    zabica->setFlag(QGraphicsItem::ItemIsFocusable);
    zabica->setFocus();
    scene->addItem(zabica);

    // CrnaRupa(x, y, visina, sirina)
    crna_rupa = new CrnaRupa(110, 250, 70, 70);
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
   // connect(, SIGNAL(sudar), putanja, SLOT(dodaj_loptu()))

    show();


}


