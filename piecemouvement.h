#ifndef PIECEMOUVEMENT_H
#define PIECEMOUVEMENT_H

#include <QMainWindow>
#include "mainwindow.h"
class pieceMouvement : public QMainWindow
{
    Q_OBJECT
public:
    explicit pieceMouvement(QWidget *parent = 0);
    void movePiece(QLabel &peice,int x,int y);
signals:

public slots:
};

#endif // PIECEMOUVEMENT_H
