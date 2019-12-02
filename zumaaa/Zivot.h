#ifndef ZIVOT_H
#define ZIVOT_H

#include <QGraphicsItem>

class Zivot: public QGraphicsTextItem{
public:
    Zivot(QGraphicsItem * parent=0);
    //ovo znaci po defaultu nema roditelja, ali mozemo da ga prosledimo ako zelimo
    void increase();
    void decrease();
    int getZivot();
private:
    int zivot;
};

#endif // ZIVOT_H
