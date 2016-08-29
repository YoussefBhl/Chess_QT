#ifndef PROMOTION_H
#define PROMOTION_H

#include <QDialog>
#include <iostream>
#include <QLabel>
using namespace std;
namespace Ui {
class promotion;
}

class promotion : public QDialog
{
    Q_OBJECT

public:
    explicit promotion(QWidget *parent = 0);
    ~promotion();
    void setSugg(bool playerTurn);
    string senderObj;
    QPixmap rock,knight,queen,bishop;
    QLabel * l;
    int *a;
private:
    Ui::promotion *ui;
public slots:
    void mousePressed();
};

#endif // PROMOTION_H
