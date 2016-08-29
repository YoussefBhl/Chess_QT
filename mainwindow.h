#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include "player.h"
#include "mouseevent.h"
#include "boardmouseevent.h"
#include "piecemouvement.h"
#include "lcdnumber.h"
#include "promotion.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
private:
    player p1,p2;
    string senderObj;
    bool capture = false;
    bool segg = false;
    int cpId = 0,id ;
    Ui::MainWindow *ui;
    FILE *f;
    int min,sec,timerActive = 1;

private slots:
    void mousePressedBoard();
    void mousePressed();
    void endWarning();
    void playersInfo();
    void playerTurnDisplay();
};

#endif // MAINWINDOW_H
