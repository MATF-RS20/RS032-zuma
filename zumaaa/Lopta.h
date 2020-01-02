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

class Lopta: public QGraphicsObject{
    Q_OBJECT
public:
    Lopta(QGraphicsItem * parent=0);
    Lopta(int precnik, QList<QPointF> tacke, QGraphicsItem * parent=0);
    void rotateToPoint(QPointF p);
    void postaviTacke(QList<QPointF> ps);
    void kolizija_crna_rupa();
    ~Lopta() override = default;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

public slots:
    void move();
    void move_back(QPointF tacka);
private:
    QList<QPointF> tacke;
    QTimer * timer;
    QPointF krajnja;
    QPixmap boja;
    int index; //indeks tacke u listi ka kojoj trenutno idemo
    int index_u_nizu;
    double size;
    char smer='v';
    char orij;
    void generisi_boju();
    int korak=2;
    int id1=1;
    int id2=1;

};


#endif // LOPTA_H
