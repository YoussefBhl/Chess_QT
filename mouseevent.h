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
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    int x,y;
signals:
    void mousePressed();
    void cursorIn();
    void cursorOut();
public slots:
};

#endif // MOUSEEVENT_H
