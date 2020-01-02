#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QPalette>
#include <QPainter>
#include <QApplication>
#include <QList>
#include <QDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setBackgroundImage(":square.jpg");
    //this->setStyleSheet("QWidget{background-image: url(:/images/images/square.jpg);}");
    //setStyleSheet("background-image: url(:/images/images/square.jpg);");

    show();
}

MainWindow::~MainWindow(){
    delete ui;
}

/*
void MainWindow::setBackgroundImage(QString imagePath)
{
    QPixmap bkgnd(imagePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

*/
