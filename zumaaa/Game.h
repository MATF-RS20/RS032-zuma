#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Zabica.h"
#include "Score.h"
#include "Zivot.h"
#include "Putanja.h"
#include "Lopta.h"
#include "CrnaRupa.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game(QWidget * parent=0);
    QGraphicsScene * scene;
    Zabica * zabica;
    Score * score;
    Zivot * zivot;
    Putanja * putanja;
    Lopta * lopta;
    CrnaRupa * crna_rupa;


signals:
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent * event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // GAME_H
