#include "Score.h"
#include <QFont>
#include "Game.h"


extern Game* game;


//ovo znaci da je QGraphicsTextItem bazicna klasa za nasu klasu score, nad njom se gradi, ona i dodeli roditelja ako prosledimo
Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    score =0;
    //crtamo ga
    setPlainText(QString("Score: ")+QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times", 16));
}


void Score::increase()
{
    //score se uvecava za unapred zadatu vrednost
    score += scoreIncrease;
    //uvecavamo i pomocnu promenljivu za score
    newScore += scoreIncrease;
    //dajemo igracu novi zivot ako se skor dovoljno uvecao
    if(newScore == newLifeScore)
    {
        newScore=0;
        game->zivot->increase();
    }
    setPlainText(QString("Score: ")+QString::number(score));
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times", 16));


}

int Score::getScore()
{
    return score;
}
