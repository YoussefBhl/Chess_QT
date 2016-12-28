#include "mouseevent.h"
#include <iostream>
using namespace std;
mouseEvent::mouseEvent(QWidget *parent) : QLabel(parent)
{

}

void mouseEvent::mousePressEvent(QMouseEvent *)
{
    emit mousePressed();
}

void mouseEvent::enterEvent(QEvent *)
{
    emit cursorIn();
}

void mouseEvent::leaveEvent(QEvent *)
{
    emit cursorOut();
}
