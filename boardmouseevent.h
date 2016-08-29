#ifndef BOARDMOUSEEVENT_H
#define BOARDMOUSEEVENT_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>

class boardMouseEvent : public QLabel
{
    Q_OBJECT
public:
    explicit boardMouseEvent(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);
    int x,y,pX,pY;
signals:
        void mousePressedBoard();
//        void piecePressed();

public slots:
};

#endif // BOARDMOUSEEVENT_H
