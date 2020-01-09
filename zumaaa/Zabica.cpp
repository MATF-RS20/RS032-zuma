#include "Zabica.h"

#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QEvent>
#include "LoptaUUstima.h"
#include <QWidget>
#include <QPoint>
#include <QtMath>
#include <QFont>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QTimer>
#include <QSignalMapper>
#include "Game.h"
#include <QtMultimedia/QMediaPlayer>


extern QGraphicsScene * scene;
extern Game * game;

Zabica::Zabica(int x, int y, int size, int precnik, QGraphicsObject* parent)
:x(x)
,y(y)
,size(size)
,precnik(precnik)
,centar(QPointF(x + size/2, y + size/2))
{
    Q_UNUSED(parent);

    setTransformOriginPoint(50, 50);

    promeni_boju();
}

void Zabica:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(x, y, size, size-15, boja);
}

QRectF Zabica::boundingRect() const
{
    return QRectF(x, y, size, size-15);
}

void Zabica::promeni_boju(){

    QVector <QPixmap> niz_slika;
    niz_slika.resize(4);
    niz_slika[0]=QPixmap(":/images/images/zabica_roze.png");
    niz_slika[1]=QPixmap(":/images/images/zabica_plava.png");
    niz_slika[2]=QPixmap(":/images/images/zabica_zelena.png");
    niz_slika[3]=QPixmap(":/images/images/zabica_ljubicasta.png");
    indexBoje = rand() % 4;
    boja= niz_slika[indexBoje];
    update(this->boundingRect());
}

void Zabica::rotiraj(QMouseEvent* event)
{
    QPointF center = this->boundingRect().center();
    QLineF ln(centar,event->pos());
    setTransformOriginPoint(center.x(), center.y());
    setRotation(-1 * ln.angle()-90); // dodao sam ovde 90 jer nam je slike zabice rotirana u suprotnom smeru
                                    // pa da bi zabica pratila kursor
}

void Zabica::klik(QMouseEvent * event)
{
    if(event->buttons() & Qt::RightButton){
        promeni_boju();
//        qDebug()<<"Promenio sam boju lopte";
    }
    // na levi klik se kreira lopta u ustima
    else if(event->buttons() & Qt::LeftButton){

        QPointF p =event->pos(); // pozicija klika
        auto x_ = centar.x() - precnik/2;
        auto y_ = centar.y() - precnik/2;
        // x_ i y_ su koordinate koje postavljaju loptu u centar zabice
        // oduzimam precnik/2 da ne bi postavio gornji levi ugao u centar zabice

        // dodat deo da se lopta crta iz usta u zavisnosti od rotacije
        double theta = rotation();
        y_ += precnik * qSin(qDegreesToRadians(theta+90));
        x_ += precnik * qCos(qDegreesToRadians(theta+90));

        loptaUsta= new LoptaUUstima(x_,y_, precnik, p);
        loptaUsta->setBoja(indexBoje);


        QTimer* timer = new QTimer(this);
        scene()->addItem(loptaUsta);
        QObject::connect(timer, SIGNAL(timeout()), loptaUsta, SLOT(move()));
        timer->start(50);

        // postavlja se zvuk pucanja
        QMediaPlayer *player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/sounds/sounds/ispaljena1.ogg"));
        player->setVolume(40);
        player->play();

        promeni_boju();

        //isipisujem tacku gde sam kliknuo
//        qInfo() << p;
    }
}

