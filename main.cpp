#include "mainwindow.h"
#include "board.h"
#include "firstpage.h"
#include "lcdnumber.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    firstPage p1;
//    p1.setStyleSheet("QWidget {background-image: url(:/images/images/player1Bishop.png)}");

    p1.show();

    return a.exec();
}
