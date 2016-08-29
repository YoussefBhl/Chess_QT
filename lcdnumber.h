#ifndef LCDNUMBER_H
#define LCDNUMBER_H

#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <iostream>
using namespace std;
class LCDNumber: public QLCDNumber
{
  Q_OBJECT

  public:
  QTimer* timer;
  QTime*  timeValue;
  public:
  LCDNumber(QWidget *parentWidget){
      this->setParent(parentWidget);
  };
  void startCountDown(int min,int sec){
      timer = new QTimer();
      timeValue = new QTime(0,min,sec);
      this->display(timeValue->toString());
      QObject::connect(timer,SIGNAL(timeout()),this,SLOT(setDisplay()));
      timer->start(1000);
//      timeValue->start();
  };
    ~ LCDNumber(){};

   public slots:
    void setDisplay()
    {
      this->timeValue->setHMS(0,this->timeValue->addSecs(-1).minute(),this->timeValue->addSecs(-1).second());
      this->display(this->timeValue->toString());       
    };
};
#endif
