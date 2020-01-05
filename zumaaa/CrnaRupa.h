#ifndef CRNARUPA_H
#define CRNARUPA_H

#include <QGraphicsRectItem>
#include <QObject>

class CrnaRupa: public QGraphicsObject {
    Q_OBJECT
public:
    CrnaRupa(int x, int y, int size);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    int x;
    int y;
    int size;
};

#endif // CRNARUPA_H
