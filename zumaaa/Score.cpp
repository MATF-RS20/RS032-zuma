#include "Score.h"
#include <QFont>

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
    score++;   //i ovo treba izmeniti da u zavisnosti od broj aloptica i ulancanih kolizija daje veci skor
    setPlainText(QString("Score: ")+QString::number(score));

}

int Score::getScore()
{
    return score;
}
