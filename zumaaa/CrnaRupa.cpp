#include "CrnaRupa.h"
#include <QGraphicsScene>
#include "Game.h"
#include <QDebug>
#include "Putanja.h"
#include <QList>
#include <QTimer>

//ovo sam stavila ovde da kad udje lopta u crnu rupu, mozemo da pristupimo zivot varijabli i smanjimo je
//ali to tek treba kasnije definisati, nemamo jos putanju i blizinu itd
//to bi trebalo doduse mozda u Putanja klasi kad bude postojala u move... njema veze, ne smeta zasad
//uglavnom pozvali bi game->health->decrease()
//i uklonili sve
extern Game * game;

CrnaRupa::CrnaRupa(int x, int y, int size)
    : x(x), y(y), size(size)
{
//    setRect(x,y,weight,height);
//    setRect(0, 0, 70, 70);
    //    setPos(200,290);
}

void CrnaRupa::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    QPixmap boja = QPixmap(":/images/crna_rupa");

    painter->drawPixmap(x, y, size, size, boja);
}

QRectF CrnaRupa::boundingRect() const
{
    return QRectF(x, y, size, size);
}

