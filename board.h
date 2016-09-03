#ifndef BOARD_H
#define BOARD_H
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <iostream>
using namespace   std;
class board
{
public:
    board();
    void paintEvent(QPainter& painter);
    void suggestion(QPainter& painter,string,string *names ,QPoint *,QPoint *,bool,int *pawnProm,int enemyPawn,bool casting);
    void rokSugg(QPainter &painter,QPoint *,QPoint *,int,bool casting);
    bool rockLimits(int x, int y, int pieceX, int pieceY, int p, QPoint *T);
    void kingSugg(QPainter &painter,QPoint *,QPoint *enemy,int,bool casting);
    void knightSugg(QPainter &painter,QPoint * T,int pos);
    void bishopSugg(QPainter &painter,QPoint *,QPoint *,int);
    void pawnSugg(QPainter &painter,QPoint *,QPoint *,int,bool,int);
};

#endif // BOARD_H
