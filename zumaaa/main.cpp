#include "mainwindow.h"

#include <QApplication>
#include "Game.h"

Game * game;

//roditeljstvo za brisanje umesto provere susednih??????

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();
    game->show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
