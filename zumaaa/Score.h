#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{
public:
    Score(QGraphicsItem * parent=0);
    //ovo znaci po defaultu nema roditelja, ali mozemo da ga prosledimo ako zelimo
    void increase();
    int getScore();
private:
    int score=0; //ukupan score korisnika
    int scoreIncrease =50; //za koliko uvecavamo scorekada ga uvecavamo
    int newScore=0; //pomocni score za uvecavanje broja zivota
    int newLifeScore=100; //koliki treba da bude score da bi korisnik dobio novi zivot
};

#endif // SCORE_H
