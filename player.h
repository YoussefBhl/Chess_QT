#ifndef PLAYER_H
#define PLAYER_H
#include "promotion.h"
#include <QMainWindow>
#include <QSignalMapper>
#include <QCursor>
#include <QDialog>
#include <QtGui>
#include <QTimer>
#include <string>
#include <QLabel>
#include <QPoint>
#include <QCursor>
#include <board.h>
#include <iostream>
#include <initializer_list>
#include <QPainter>
#include <QPen>
#include <QRect>
#include <QTimer>
using namespace std;
class player : public QMainWindow
{
    Q_OBJECT
public:
    explicit player(QWidget *parent = 0);
    void setPiecesName(std::initializer_list<string> argv); //set name of pieces used to know which piece clicked
    void setPieces(std::initializer_list<QLabel *> argv);   //set pieces into table
    void setPiecesPosition(); //set pieces' posotion
    void setPiecesImage(std::initializer_list<QPixmap> argv);   // set pieces pictures
    void capturePiece(int x, int y,QLabel *piece,int pos,QPoint *,int,int);
    void mouvePiece(int x, int y,QLabel *piece,int pos,QPoint *T,int cpId);
    void mouvePawn(int x, int y,QLabel *piece,int pos,int cpId,QPoint *enemy,int enemyPawn);
    bool rokLimits(int x, int y,int pieceX, int pieceY,int p, QPoint *T);
    bool bishopLimits(int x, int y, int pieceX, int pieceY,int p, QPoint *T);
    bool kingLimits(int,int,int,int);
    bool horseLimits(int,int,int,int);
    bool pawnLimits(int x, int y, int pieceX, int pieceY,int p,QPoint *enemy, int enemyPawn);
    bool pawnCapture(int x, int y, int pieceX, int pieceY);
    bool kingReset(int pieceX, int pieceY, QPoint *T);
    bool KingWarning(QPoint* T);
    string piecesName[16];
    QLabel *pieces[16];
    QPoint  piecesPosition[16];
    int pawnProm[8];
    static bool playerTurn ;
    static bool KingDanger ;
    static bool canCapture ;
    bool canCapturePawn = false;
    QLabel *pieceReset;
    int pawnEnPassant = -1;
    int xReset,yReset,pawnCaptured = -1;
private:
     promotion *pr;
     void pawnPromotion();
signals:

public slots:
    void reset();
};

#endif // PLAYER_H
