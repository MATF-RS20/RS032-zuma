#include "CrnaRupa.h"
#include <QGraphicsScene>
#include "Game.h"

//ovo sam stavila ovde da kad udje lopta u crnu rupu, mozemo da pristupimo zivot varijabli i smanjimo je
//ali to tek treba kasnije definisati, nemamo jos putanju i blizinu itd
//to bi trebalo doduse mozda u Putanja klasi kad bude postojala u move... njema veze, ne smeta zasad
//uglavnom pozvali bi game->health->decrease()
//i uklonili sve
extern Game * game;

CrnaRupa::CrnaRupa()
{
    setRect(0, 0, 50, 50);
    setPos(0,0);
}
