#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QTimer>
#include "player.h"
namespace Ui {
class playWindow;
}

class playWindow : public QWidget
{
    Q_OBJECT

public:
    explicit playWindow(QWidget *parent = 0);
    ~playWindow();
    void paintEvent(QPaintEvent *e);
//private:
    player p1,p2;
    string senderObj;
    bool timerActive = true;
    bool capture = false;
    bool segg = false;
    int cpId = 0,counter=0;
    QTimer *timer1;
    Ui::playWindow *ui;
    FILE *f;
    int min,sec;
private slots:
    void mousePressedBoard();
    void mousePressed();
    void warningMes();
    void endWarning();
};

#endif // PLAYWINDOW_H
