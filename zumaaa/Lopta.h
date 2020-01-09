#ifndef LOPTA_H
#define LOPTA_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QObject>
#include <QList>
#include <QPointF>
#include <QPainter>
#include <QPixmap>
#include <QVector>
#include <QGraphicsObject>


class Lopta: public QGraphicsObject{
    Q_OBJECT
public:
    Lopta(int precnik, QList<QPointF> tacke, QGraphicsObject * parent=0);
    Lopta(const Lopta &l2);
    void rotateToPoint(QPointF p);
    void postaviTacke(QList<QPointF> ps);
    void kolizija_crna_rupa();
    ~Lopta() override = default;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    void setKorak(int k); //seter za korak kao bi mogle da se ubrzaju loptice
    bool ideUnatrag ,pocetniStop, doUdara; //indikatori koji odredjuju kretanje
    float ostaloVremena=0;
    float ostaloDuzine=0;
    void setIndex(int novi_indeks);
    void setReverse();
    void setReverse(float distance);
    bool poredi(const Lopta *other);
    QPointF krajnja;

    int indexBoje=0;
    bool u_koliziji = false;
    void move_back(int id);
    bool isDeleted = false;
    void setIndexBoje(int indeks);
    void stopTimer();
signals:
    void sudar(QPointF);
public slots:
    void move();
    void move_back(QPointF tacka);
private:
    double size;
    QList<QPointF> tacke;
    QTimer * timer;
    QPixmap boja;
    int index; //indeks tacke u listi ka kojoj trenutno idemo
    int index_u_nizu;
    double pocetna_dim;
    void generisi_boju();
    int korak=2;
    int id1=1;
    int id2=1;
    QVector <QPixmap> niz_slika{QPixmap(":/images/roze.png"), QPixmap(":/images/plava.png"), QPixmap(":/images/zelena.png"), QPixmap(":/images/ljubicasta.png")};


};


#endif // LOPTA_H
