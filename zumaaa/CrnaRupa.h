#ifndef CRNARUPA_H
#define CRNARUPA_H

#include <QGraphicsRectItem>
#include <QObject>

class CrnaRupa: public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    CrnaRupa(int x, int y, int height, int weight);
};

#endif // CRNARUPA_H
