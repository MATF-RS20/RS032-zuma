#ifndef LOPTA_H
#define LOPTA_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QObject>
#include <QList>  //omogucen lista<<element za ubacanje
#include <QPointF>
#include <QPainter>
#include <QPixmap>
#include <QVector>
#include <QGraphicsObject>

//struktura za reverse????

class Lopta: public QGraphicsObject{
    Q_OBJECT
public:
    Lopta(QGraphicsItem * parent=0);
    Lopta(int precnik, QList<QPointF> tacke, QGraphicsItem * parent=0);
    Lopta(const Lopta &l2);
    void rotateToPoint(QPointF p);
    void postaviTacke(QList<QPointF> ps);
    void kolizija_crna_rupa();
    ~Lopta() override = default;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    //seter za korak kao bi mogle da se ubrzaju loptice
    void setKorak(int k);
    bool ideUnatrag,pocetniStop,doUdara; //indikatori koji odredjuju kretanje
    float ostaloVremena=0;
    float ostaloDuzine=0;
    void setIndex(int novi_indeks);
    void setReverse();
    void setReverse(float distance);
    bool poredi(const Lopta *other);
    QPointF krajnja;

signals:
    void sudar(QPointF);
public slots:
    void move();
    void move_back(QPointF tacka);
private:
    QList<QPointF> tacke;
    QTimer * timer;
    QPixmap boja;
    int index; //indeks tacke u listi ka kojoj trenutno idemo
    int index_u_nizu;
    double size;
    double pocetna_dim;
    char smer='v';
    char orij;
    void generisi_boju();
    int korak=2;
    int id1=1;
    int id2=1;
public:
    //indeks preko kog se porde boje, mozda neki geter i seter bi bilo bolje da se koristi
    int indexBoje=0;
    bool u_koliziji = false;
<<<<<<< HEAD
    void move_back(int id);
=======
    bool isDeleted = false;
>>>>>>> d39dbb6df60dbc80261c32ce3bf48cbf2b8565e7


};


#endif // LOPTA_H
