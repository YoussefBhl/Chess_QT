#include "boardmouseevent.h"
#include <iostream>
#include <QString>
#include "mainwindow.h"
using namespace std;
boardMouseEvent::boardMouseEvent(QWidget *parent) : QLabel(parent)
{

}
void boardMouseEvent::mousePressEvent(QMouseEvent *e)
{
    //changing x & y to right on the cube
    int a=0;int b=0;
    while(a<e->x()||b<e->y()){
        if(a<e->x()){
           a+=70;
        }
        if(b<e->y()){
           b+=70;
        }
    }
        this->x=a+60;
    this->y=b-20;
    emit mousePressedBoard();
}
