#include "mainwindow.h"

#include <QApplication>
#include "Game.h"
#include <QtMultimedia/QMediaPlayer>

Game * game;

//roditeljstvo za brisanje umesto provere susednih??????

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();
    //MainWindow w;
    //w.show();

    QMediaPlayer *player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile("/sounds/sounds/Zuma.mp3"));
        player->setVolume(50);
        player->play();

    return a.exec();
}
