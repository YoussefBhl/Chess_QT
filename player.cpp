#include "player.h"

player::player(QWidget *parent) : QMainWindow(parent)
{
    for(int i=0;i<8;i++)
        pawnProm[i] = -1;
}
bool player::playerTurn = true;
bool player::KingDanger =false;
bool player::canCapture =false;
bool player::gameOver =false;
void player::setPiecesName(std::initializer_list<string> argv)
{
    int j=0;
    for (auto i = argv.begin(); i != argv.end(); i++){
        piecesName[j] = *i;
        j++;
    }
}

void player::setPieces(std::initializer_list<QLabel *> argv)
{
    int j=0;
    for (auto i = argv.begin(); i != argv.end(); i++){
             pieces[j] = *i;
        j++;
    }
}

void player::setPiecesPosition(){
    for (int i=0;i<16; i++)
             piecesPosition[i] = pieces[i]->pos();
}

void player::setPiecesImage(std::initializer_list<QPixmap> argv)
{
    int j=0;
    auto i = argv.begin();
    while(j<8){
             pieces[j]->setPixmap(*i);
        i++;
        j++;
    }
    while(j<16){
        pieces[j]->setPixmap(*i);
        j++;
    }
}

bool player::rockLimits(int x, int y, int pieceX, int pieceY, int p, QPoint *T)
{
    int minX=1000,minY=1000,maxX=0,maxY=0;
    if(x == pieceX || y == pieceY){
        for(int i=0;i<16;i++){
            if(T[i].x() == x && i!=p){
                if(y>pieceY){
                    if(T[i].y() < minY && T[i].y() >pieceY)
                        minY = T[i].y();
                }
                else
                    if(T[i].y() > maxY && T[i].y() < pieceY)
                        maxY = T[i].y();
            }
            if(T[i].y() == y && i!=p){
                if(x>pieceX){
                    if(T[i].x() < minX && T[i].x() >pieceX)
                        minX = T[i].x();
                }
                else
                    if(T[i].x() > maxX && T[i].x() < pieceX)
                        maxX = T[i].x();
            }
        }
    }
    else
        return false;
    if(x<minX && y<minY && x>maxX && y>maxY)
        return true;
    else
        return false;
}

bool player::bishopLimits(int x, int y, int pieceX, int pieceY, int p, QPoint *T)
{
    int minX=1000,maxX=0,a,b;
    if(abs(pieceX - x) == abs(y - pieceY)){
        for(int i=0;i<16;i++){
            a = T[i].x() ; b = T[i].y();
            if(abs(a-pieceX) == abs(b -pieceY) && i!=p){
                 if(x>pieceX && y>pieceY){
                         if(a < minX && a>pieceX && pieceY<b)
                             minX = a;
                 }
                 else if(x>pieceX && y<pieceY ){
                         if(a < minX && a>pieceX && pieceY>b)
                             minX = a;
                 }
                 else if(x<pieceX && y<pieceY){
                         if(a > maxX && a<pieceX && pieceY>b)
                             maxX = a;
                 }
                 else if(x<pieceX && y>pieceY){
                         if(a > maxX && a<pieceX && pieceY<b)
                             maxX = a;
                 }
             }
        }
    }
           else
               return false;
           if(x<=minX && x>=maxX)
               return true;
           else
               return false;
}

bool player::queenLimits(int x, int y, int pieceX, int pieceY, int p, QPoint *T,int i)
{
    if(rockLimits(x,y,pieceX,pieceY,i,T) && rockLimits(x,y,pieceX,pieceY,p,piecesPosition)){
        return true;}
    if(bishopLimits(x,y,pieceX,pieceY,i,T) && bishopLimits(x,y,pieceX,pieceY,p,piecesPosition))
        return true;
    if(kingLimits(x,y,pieceX,pieceY))
        return true;
    return false;
}
bool player::kingLimits(int x, int y, int pieceX, int pieceY)
{
    if((pieceY ==y && (pieceX ==x+70 || pieceX == x-70))||(pieceY ==y+70 && (pieceX ==x+70 || pieceX == x-70 || pieceX == x))
                    ||(pieceY ==y-70 && (pieceX ==x+70 || pieceX == x-70 || pieceX == x)))
        return true;
    else
        return false;
}

bool player::knightLimits(int x, int y, int pieceX, int pieceY)
{
    if((pieceY == y -140 && (pieceX == x-70 || pieceX == x+70)) || (pieceY == y -70 && (pieceX == x-140 || pieceX == x+140))
            ||(pieceY == y +140 && (pieceX == x+70 || pieceX == x-70)) || (pieceY == y +70 && (pieceX == x-140 || pieceX == x+140)))
        return true;
    return false;
}

bool player::pawnLimits(int x, int y, int pieceX, int pieceY, int p,QPoint *enemy, int enemyPawn)
{
    if(x == pieceX){
        if(playerTurn){
            if(pieceY == 120){
                if(y == 190 || y == 260){
                    for(int i=0;i<8;i++){
                        if(piecesPosition[i].x() == pieceX && piecesPosition[i].y() == pieceY +70)
                            return false;
                    }
                    if(y == 260){
                        pawnEnPassant = p;
                        return true;
                    }
                    else if(y == 190)
                        return true;
                }
            }
            else if(pieceY == y-70)
                return true;
        }
        else{
            if(pieceY == 470){
                if(y == 400 || y == 330){
                    for(int i=0;i<8;i++){
                        if(piecesPosition[i].x() == pieceX && piecesPosition[i].y() == pieceY -70)
                            return false;
                    }
                    if(y == 330){
                        pawnEnPassant = p;
                        return true;
                    }
                    else if(y == 400)
                        return true;

                }
            }
            else if(pieceY == y+70)
                return true;
        }
    }
    else{
        if (enemyPawn != -1){
            if (x == pieceX+70 || x == pieceX-70){
                if(playerTurn){
                    if(y == pieceY+70){
                            if(enemy[enemyPawn].y() == pieceY){
                                if(enemy[enemyPawn].x() == pieceX+70 && x == pieceX +70){
                                    canCapturePawn = true;
                                    return true;
                                }
                                 else if(enemy[enemyPawn].x() == pieceX-70 && x == pieceX-70){
                                    canCapturePawn = true;
                                    return true;
                                }
                            }
                    }
                }
                else {
                    if(y == pieceY-70){
                            if(enemy[enemyPawn].y() == pieceY){
                                if(enemy[enemyPawn].x() == pieceX+70 && x == pieceX +70){
                                    canCapturePawn = true;
                                    return true;
                                }
                                 else if(enemy[enemyPawn].x() == pieceX-70 && x == pieceX-70){
                                    canCapturePawn = true;
                                    return true;
                                }
                            }
                    }
                }
            }
        }
    }
     return false;
}
bool player::pawnCapture(int x, int y, int pieceX, int pieceY)
{
    if(y == pieceY + 70){
        if(x == pieceX +70 || x == pieceX -70)
            return true;
    }
    return false;
}

bool player::kingReset(int x, int y,QPoint *T,int cpId)
{
    if(rockLimits(x,y,T[0].x(),T[0].y(),cpId,piecesPosition) && rockLimits(x,y,T[0].x(),T[0].y(),0,T))
        return true;
    if(rockLimits(x,y,T[7].x(),T[7].y(),cpId,piecesPosition) && rockLimits(x,y,T[7].x(),T[7].y(),0,T))
        return true;
    if(bishopLimits(x,y,T[2].x(),T[2].y(),cpId,piecesPosition) && bishopLimits(x,y,T[2].x(),T[2].y(),-1,T))
        return true;
    if(bishopLimits(x,y,T[5].x(),T[5].y(),cpId,piecesPosition) && bishopLimits(x,y,T[5].x(),T[5].y(),-1,T))
        return true;
    if(knightLimits(x,y,T[1].x(),T[1].y()))
        return true;
    if(knightLimits(x,y,T[6].x(),T[6].y()))
        return true;
    if(queenLimits(x,y,T[3].x(),T[3].y(),cpId,T,3))
        return true;
    for(int i=8;i<16;i++){
        if(pawnProm[i-8] == -1){
            if(pawnCapture(x,y,T[i].x(),T[i].y()))
                return true;
        }
        else if(pawnProm[i-8] == 0){
            if(rockLimits(x,y,T[i].x(),T[i].y(),cpId,piecesPosition) && rockLimits(x,y,T[i].x(),T[i].y(),i,T))
                return true;
        }
        else if(pawnProm[i-8] == 1){
            if(knightLimits(x,y,T[i].x(),T[i].y()))
                return true;
        }
        else if(pawnProm[i-8] == 2){
            if(bishopLimits(x,y,T[i].x(),T[i].y(),cpId,piecesPosition) && bishopLimits(x,y,T[i].x(),T[i].y(),i,T))
                return true;
        }
        else if(pawnProm[i-8] == 3){
            if(queenLimits(x,y,T[i].x(),T[i].y(),cpId,T,i))
                return true;
        }
    }
    return false;
}

bool player::enemyKingCanBeCaptured(int x, int y, QPoint *T,int cpId)
{
    if(rockLimits(x,y,piecesPosition[0].x(),piecesPosition[0].y(),0,piecesPosition) && rockLimits(x,y,piecesPosition[0].x(),piecesPosition[0].y(),-1,T) && cpId != 0)
        return true;
    if(rockLimits(x,y,piecesPosition[7].x(),piecesPosition[7].y(),7,piecesPosition) && rockLimits(x,y,piecesPosition[7].x(),piecesPosition[7].y(),-1,T) && cpId != 7)
        return true;
    if(bishopLimits(x,y,piecesPosition[2].x(),piecesPosition[2].y(),2,piecesPosition) && bishopLimits(x,y,piecesPosition[2].x(),piecesPosition[2].y(),4,T) && cpId != 2)
        return true;
    if(bishopLimits(x,y,piecesPosition[5].x(),piecesPosition[5].y(),5,piecesPosition) && bishopLimits(x,y,piecesPosition[5].x(),piecesPosition[5].y(),4,T) && cpId != 5)
        return true;
    if(knightLimits(x,y,piecesPosition[1].x(),piecesPosition[1].y()))
        return true;
    if(knightLimits(x,y,piecesPosition[6].x(),piecesPosition[6].y()))
        return true;
    if(queenLimits(x,y,piecesPosition[3].x(),piecesPosition[3].y(),3,T,-1) && cpId != 3)
        return true;
    for(int i=8;i<16;i++){
        if(pawnProm[i-8] == -1){
            if(pawnCapture(x,y,piecesPosition[i].x(),piecesPosition[i].y()))
                return true;
        }
        else if(pawnProm[i-8] == 0){
            if(rockLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y(),i,piecesPosition) && rockLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y(),cpId,T) && cpId != i)
                return true;
        }
        else if(pawnProm[i-8] == 1){
            if(knightLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y()))
                return true;
        }
        else if(pawnProm[i-8] == 2){
            if(bishopLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y(),i,piecesPosition) && bishopLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y(),cpId,T) && cpId != i)
                return true;
        }
        else if(pawnProm[i-8] == 3){
            if(queenLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y(),i,T,cpId) && cpId != i)
                return true;
        }
    }
    return false;
}

int player::KingWarning(QPoint *T)
{
    int x = T[4].x(),y = T[4].y();
    if(rockLimits(x,y,piecesPosition[0].x(),piecesPosition[0].y(),0,piecesPosition)
            && rockLimits(x,y,piecesPosition[0].x(),piecesPosition[0].y(),4,T))
        return 0;
    if(rockLimits(x,y,piecesPosition[7].x(),piecesPosition[7].y(),7,piecesPosition)
            && rockLimits(x,y,piecesPosition[7].x(),piecesPosition[7].y(),4,T))
        return 7;
    if(bishopLimits(x,y,piecesPosition[2].x(),piecesPosition[2].y(),2,piecesPosition)
            && bishopLimits(x,y,piecesPosition[2].x(),piecesPosition[2].y(),4,T))
        return 2;
    if(bishopLimits(x,y,piecesPosition[5].x(),piecesPosition[5].y(),5,T)
            && bishopLimits(x,y,piecesPosition[5].x(),piecesPosition[5].y(),4,T))
        return 5;
    if(knightLimits(x,y,piecesPosition[1].x(),piecesPosition[1].y()))
        return 1;
    if(knightLimits(x,y,piecesPosition[6].x(),piecesPosition[6].y()))
        return 6;
    if(queenLimits(x,y,piecesPosition[3].x(),piecesPosition[3].y(),3,T,4)){
        return 3;}
    for(int i=8;i<16;i++){
        if(pawnProm[i-8] == -1){
            if(pawnCapture(x,y,piecesPosition[i].x(),piecesPosition[i].y()))
                return i;
        }
        else if(pawnProm[i-8] == 0){
                if(rockLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y(),i,piecesPosition)
                        && rockLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y(),4,T))
                    return 0;
        }
        else if(pawnProm[i-8] == 1){
            if(knightLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y()))
            return 1;
        }
        else if(pawnProm[i-8] == 2){
            if(bishopLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y(),i,piecesPosition)
                && bishopLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y(),4,T))
            return 2;
        }
        else if(pawnProm[i-8] == 3){
            if(queenLimits(x,y,piecesPosition[i].x(),piecesPosition[i].y(),3,T,4))
                return 3;
        }

    }
    return -1;
}

bool player::gameOver_1(QPoint enemyKing, QPoint *enemy, int KingWarningPiece)
{
    bool cantMouve = false;
    int id = -1;
    int x = enemyKing.x(), y = enemyKing.y(),xEnemy = piecesPosition[KingWarningPiece].x(),yEnemy = piecesPosition[KingWarningPiece].y();
    if(kingReset(xEnemy,yEnemy,enemy,KingWarningPiece)) // if enemy piece can be captured then game is not over
        return false;
    if(kingLimits(xEnemy,yEnemy,x,y))
        id = KingWarningPiece;
    // testing the enemy's king mouvement possiblities
    if(y>50){
        for(int i = x-70;i<x+70;i+=70){
            if(i>=130 && i<=620){
                int j =0;
                cantMouve = false;
                while(j<16 && !cantMouve){
                    if(enemy[j].x() == i && enemy[j].y() == y-70 && j != 4)
                        cantMouve = true;
                    else
                        j++;
                }
                if(!cantMouve){
                    if(!enemyKingCanBeCaptured(i,y-70,enemy,id))
                        return false;
                }
            }
        }
        cantMouve = false;
    }
    if(x>130){
        int j =0;
        while(j<16 && ! cantMouve){
            if(enemy[j].x() == x-70 && enemy[j].y() == y && j != 4)
                cantMouve = true;
            else
                j++;
        }
        if(!cantMouve){
            if(!enemyKingCanBeCaptured(x-70,y,enemy,id))
                return false;
        }
    }
    cantMouve = false;
    if(x<620){
        int j=0;
        while(j<16 && !cantMouve){
            if(enemy[j].x() == x+70 && enemy[j].y() == y && j != 4)
                cantMouve = true;
            else
                j++;
        }
        if(!cantMouve){
            if(!enemyKingCanBeCaptured(x+70,y,enemy,id))
                return false;
        }
    }
    if(y<540){
        for(int i=x+70;i<x+70;i+=70){
            if(i>=130 && i<=620){
                cantMouve = false;
                int j=0;
                while(j<16 && !cantMouve){
                    if(enemy[j].x() == i && enemy[j].y() == y+70 && j != 4)
                        cantMouve = true;
                    else
                        j++;
                }
                if(!cantMouve){
                    if(!kingReset(i,y+70,enemy,id))
                        return false;
                }
            }
        }
    }
    return true;
}

bool player::gameOver_2(QPoint *enemy)
{
    int x = enemy[4].x(), y = enemy[4].y();
    for(int i=0;i<16;i++){
        if(i!=4){
            if(enemy[i] != QPoint(0,0) )
                return false;
        }
    }
    // testing the enemy's king mouvement possiblities
    if(y>50){
        for(int i = x-70;i<x+70;i+=70){
            if(i>=130 && i<=620){
                if(!enemyKingCanBeCaptured(i,y-70,enemy,-1))
                    return false;
                }
            }
        }
    if(x>130){
        if(!enemyKingCanBeCaptured(x-70,y,enemy,-1))
                return false;
        }
    if(x<620){
        if(!enemyKingCanBeCaptured(x+70,y,enemy,-1))
                return false;
        }
    if(y<540){
        for(int i=x+70;i<x+70;i+=70){
            if(i>=130 && i<=620){
                if(!kingReset(i,y+70,enemy,-1))
                    return false;
                }
            }
        }
    return true;
}

bool player::castling(QPoint *enemy, int cpId,int j)
{
    int x = piecesPosition[4].x(),y = piecesPosition[4].y();
    if(cpId == 0 || cpId == 7){
        int pieceX = piecesPosition[cpId].x(),pieceY = piecesPosition[cpId].y();
        if(!kingFirstMouve && kingNeverChecked){
            if(cpId == 0 && !rockFirstMouve0){
                if(rockLimits(x,y,pieceX,pieceY,4,piecesPosition) &&
                        rockLimits(x,y,pieceX,pieceY,-1,enemy)){
                    pieces[cpId]->setGeometry(x-70,y,70,70);
                    pieces[4]->setGeometry(x-140,y,70,70);
                    playerTurn = !playerTurn;
                    kingFirstMouve = true;
                    rockFirstMouve0 = true;
                }
            }
            else if(cpId == 7 && !rockFirstMouve7){
                if(rockLimits(x,y,pieceX,pieceY,4,piecesPosition) &&
                        rockLimits(x,y,pieceX,pieceY,-1,enemy)){
                    pieces[cpId]->setGeometry(x+70,y,70,70);
                    pieces[4]->setGeometry(x+140,y,70,70);
                    playerTurn = !playerTurn;
                    kingFirstMouve = true;
                    rockFirstMouve7 = true;
                }
            }
        }
    }
    else{
        int pieceX = piecesPosition[j].x(),pieceY = piecesPosition[j].y();
        if(!kingFirstMouve && kingNeverChecked){
            if(rockLimits(x,y,pieceX,pieceY,4,piecesPosition) && rockLimits(x,y,pieceX,pieceY,-1,enemy)){
                if(j == 0 && !rockFirstMouve0){
                    pieces[j]->setGeometry(x-70,y,70,70);
                    pieces[4]->setGeometry(x-140,y,70,70);
                    playerTurn = !playerTurn;
                    kingFirstMouve = true;
                    rockFirstMouve0 = true;
                }
                else if(j == 7 && !rockFirstMouve7){
                    pieces[j]->setGeometry(x+70,y,70,70);
                    pieces[4]->setGeometry(x+140,y,70,70);
                    playerTurn = !playerTurn;
                    kingFirstMouve = true;
                    rockFirstMouve7 = true;
                }
            }
        }
    }
}

void player::pawnPromotion()
{
    int j=8;
    bool test = false;
    while(j<16 && !test){
        if(piecesPosition[j].y() == 540){
            if(pawnProm[j-8] == -1)
                test = true;
            else
                break;
            }
            else
                j++;
        }
    if(test){
        pr = new promotion();
        pr->setSugg(playerTurn);
        pr->setModal(true);
        pr->show();
        pr->a = pawnProm+j-8;
        pr->l = pieces[j];
        this->setEnabled(false);

    }
}

void player::reset()
{

    pieceReset->setGeometry(xReset,yReset,70,70);
}

void player::capturePiece(int x, int y,QLabel *piece, int id,QPoint *T,int j,int cpId)
{
    int pieceX = piecesPosition[cpId].x() , pieceY = piecesPosition[cpId].y(),KingWarningPiece;
    bool kingInDanger = false;
    canCapture = false;
    QPoint capturedPiecePoint = T[j];
    T[j] = QPoint(0,0);
    xReset =piece->x();yReset=piece->y();
    pieceReset = piece;
        if(id == 0 || id == 7){
            if(rockLimits(x,y,pieceX,pieceY,id,piecesPosition) && rockLimits(x,y,pieceX,pieceY,j,T)){
                     playerTurn = !playerTurn;
                    piece->setGeometry(x,y,70,70);
                    canCapture = true;
                    piece->setGeometry(x,y,70,70);
                    if(cpId == 0)
                        rockFirstMouve0 = true;
                    else if(cpId == 7)
                        rockFirstMouve7 = true;
                 }
           }
        else if(id == 2 || id== 5){
                if(bishopLimits(x,y,pieceX,pieceY,-1,piecesPosition) && bishopLimits(x,y,pieceX,pieceY,-1,T)){
                    playerTurn = !playerTurn;
                    canCapture = true;
                piece->setGeometry(x,y,70,70);
         }
        }
        else if(id == 4){
            if(kingLimits(x,y,pieceX,pieceY)){
                playerTurn = !playerTurn;
                canCapture = true;
                piece->setGeometry(x,y,70,70);
                kingFirstMouve = true;
            }
        }
        else if(id == 3){
            if(queenLimits(x,y,pieceX,pieceY,3,T,j)){
                canCapture = true;
                playerTurn = !playerTurn;
               piece->setGeometry(x,y,70,70);
            }
        }
        else if(id == 1 || id == 6){
            if(knightLimits(x,y,pieceX,pieceY)){
                canCapture = true;
                playerTurn = !playerTurn;
               piece->setGeometry(x,y,70,70);
            }
        }
        else{
            int i = 8;
            while(i<16){
                 if(id == i){
                     if(pawnProm[i-8] == -1){
                         if(pawnCapture(x,y,pieceX,pieceY)){
                             canCapture = true;
                             playerTurn = !playerTurn;
                             piece->setGeometry(x,y,70,70);
                         }
                     }
                     break;
                 }
                 else
                     i++;
            }
        }

    playerTurn = !playerTurn;
    piecesPosition[cpId] = piece->pos();

    if(kingReset(piecesPosition[4].x(),piecesPosition[4].y(),T,4)){
        playerTurn = !playerTurn;
        kingInDanger = true;
        canCapture = false;
        QTimer::singleShot(500,this, SLOT(reset()));
        piecesPosition[cpId] = QPoint(xReset,yReset);
        }

    else{
        KingDanger = false;
    }
    KingWarningPiece = KingWarning(T);
    if(KingWarningPiece != -1){
        KingDanger = true;
        if(gameOver_1(T[4],T,KingWarningPiece))
            gameOver = true;
        kingNeverChecked = false;
    }
    else{
        if(gameOver_2(T))
            gameOver = true;
    }
     T[j] = capturedPiecePoint;
     pawnPromotion();

}

void player::mouvePiece(int x, int y, QLabel *piece, int id,QPoint *T,int cpId)
{

    int pieceX = piece->x() , pieceY = piece->y(),KingWarningPiece;
    bool kingInDanger = false;

    xReset =piece->x();yReset=piece->y();
    pieceReset = piece;
        if(id == 0 || id == 7){
            if(rockLimits(x,y,pieceX,pieceY,-1,piecesPosition)&& rockLimits(x,y,pieceX,pieceY,-1,T)){
                     playerTurn = !playerTurn;
                    piece->setGeometry(x,y,70,70);
                    if(cpId == 0)
                        rockFirstMouve0 = true;
                    else if(cpId == 7)
                        rockFirstMouve7 = true;
                 }
           }
        else if(id == 2 || id== 5){
                if(bishopLimits(x,y,pieceX,pieceY,-1,piecesPosition) && bishopLimits(x,y,pieceX,pieceY,-1,T)){
                    playerTurn = !playerTurn;
                   piece->setGeometry(x,y,70,70);

         }
        }
        else if(id == 3){
            if(queenLimits(x,y,pieceX,pieceY,3,T,-1)){
                playerTurn = !playerTurn;
               piece->setGeometry(x,y,70,70);
            }
        }
        else if(id == 4){
            if(kingLimits(x,y,pieceX,pieceY)){
                playerTurn = !playerTurn;
                piece->setGeometry(x,y,70,70);
                kingFirstMouve = true;
            }
        }
        else if(id == 1 || id == 6){
            if(knightLimits(x,y,pieceX,pieceY)){
                playerTurn = !playerTurn;
               piece->setGeometry(x,y,70,70);
            }
        }
    piecesPosition[cpId] = piece->pos();
    if(kingReset(pieces[4]->x(),pieces[4]->y(),T,4)){
        playerTurn = !playerTurn;
        kingInDanger = true;
        QTimer::singleShot(500,this, SLOT(reset()));
        piecesPosition[cpId] = QPoint(xReset,yReset);
        }
    else
        KingDanger =false;
    KingWarningPiece = KingWarning(T);
    if(KingWarningPiece != -1){
        KingDanger =true;
        if(gameOver_1(T[4],T,KingWarningPiece))
            gameOver = true;
    }
    else{
        if(gameOver_2(T))
            gameOver = true;
    }
    playerTurn = !playerTurn;
    pawnPromotion();


}

void player::mouvePawn(int x, int y, QLabel *piece, int pos, int cpId,QPoint *enemy, int enemyPawn)
{
    int pieceX = piece->x() , pieceY = piece->y(),KingWarningPiece;
    xReset =piece->x();yReset=piece->y();
    canCapture = false;
    pieceReset = piece;
    bool kingInDanger = false;
    if(pawnProm[cpId-8] == -1){
        if(pawnLimits(x,y,pieceX,pieceY,cpId,enemy,enemyPawn)){
            playerTurn = !playerTurn;
            piece->setGeometry(x,y,70,70);
            if(canCapturePawn)
                canCapture = true;
        }
    }
    piecesPosition[cpId] = piece->pos();
    if(kingReset(pieces[4]->x(),pieces[4]->y(),enemy,4)){
        playerTurn = !playerTurn;
        kingInDanger = true;
        QTimer::singleShot(500,this, SLOT(reset()));
        piecesPosition[cpId] = QPoint(xReset,yReset);
        }
    else
        KingDanger =false;
    KingWarningPiece = KingWarning(enemy);
    if(KingWarningPiece != -1){
        KingDanger =true;
        if(gameOver_1(enemy[4],enemy,KingWarningPiece))
            gameOver = true;
    }
    else{
        if(gameOver_2(enemy))
            gameOver = true;
    }
    playerTurn = !playerTurn;
    pawnPromotion();

}
