#include "mainwindow.h"
#include "board.h"
#include "firstpage.h"
#include "lcdnumber.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    firstPage p1;
    p1.show();
    return a.exec();
}
