#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>


class mouseEvent : public QLabel
{
    Q_OBJECT
public:
    explicit mouseEvent(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *ev);
    int x,y;
signals:
    void mousePressed();

public slots:
};

#endif // MOUSEEVENT_H
