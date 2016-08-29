#include "mouseevent.h"
#include <iostream>
using namespace std;
mouseEvent::mouseEvent(QWidget *parent) : QLabel(parent)
{

}

void mouseEvent::mousePressEvent(QMouseEvent *e)
{

    emit mousePressed();
}
