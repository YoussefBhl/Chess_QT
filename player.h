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
    void capturePiece(int x, int y,QLabel *piece,int pos,QPoint *,int,int,int*);
    void mouvePiece(int x, int y,QLabel *piece,int pos,QPoint *T,int cpId,int*);
    void mouvePawn(int x, int y,QLabel *piece,int cpId,QPoint *enemy,int enemyPawn,int*);
    bool rockLimits(int x, int y,int pieceX, int pieceY,int p, QPoint *T);
    bool bishopLimits(int x, int y, int pieceX, int pieceY,int p, QPoint *T);
    bool queenLimits(int x, int y, int pieceX, int pieceY,int p, QPoint *T,int i);
    bool kingLimits(int,int,int,int);
    bool knightLimits(int,int,int,int);
    bool pawnLimits(int x, int y, int pieceX, int pieceY,int p,QPoint *enemy, int enemyPawn);
    bool pawnCapture(int x, int y, int pieceX, int pieceY);
    bool pawnCaptureKing(int x, int y, int pieceX, int pieceY);
    bool kingReset(int pieceX, int pieceY,QPoint *T,int,int *);
    bool enemyKingCanBeCaptured(int pieceX, int pieceY,QPoint *T,int);
    int KingWarning(QPoint* T);
    bool intersection(int,QPoint*,int *);
    bool rockIntersection(int pieceX,int pieceY,int enemykingX,int enemykingY,QPoint*,int *enemyPawnProm);
    bool bishopIntersection(int pieceX,int pieceY,int enemykingX,int enemykingY,QPoint*,int *enemyPawnProm);
    bool gameOver_1(QPoint enemyKing,QPoint *enemy,int,int *); //if king's Trapped
    bool gameOver_2(QPoint *enemy,int *); // all pieces're captured except king & can't mouve it
    void pawnPromotion();
    string piecesName[16];
    QLabel *pieces[16];
    QPoint  piecesPosition[16];
    int pawnProm[8];
    static bool playerTurn ;
    static bool KingDanger ;
    static bool canCapture ;
    static bool gameOver ;
    bool canCapturePawn = false;
    QLabel *pieceReset;
    int pawnEnPassant = -1;
    int xReset,yReset,pawnCaptured = -1;
    //castling
    bool kingFirstMouve = false;
    bool rockFirstMouve0 = false;
    bool rockFirstMouve7 = false;
    bool kingNeverChecked = true;
    void castling(QPoint *enemy,int id,int k);
private:
     promotion *pr;
     bool pieceCanCaptured(int pieceX, int pieceY,QPoint *T,int,int *);

signals:

public slots:
    void reset();
};

#endif // PLAYER_H
