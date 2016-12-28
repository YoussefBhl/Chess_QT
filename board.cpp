#include "board.h"

board::board()
{
}
void board::paintEvent(QPainter& painter)
{
    QPen pen(QColor(240,230,140));
    pen.setWidth(14);
    painter.setPen(pen);
    QBrush brushBlack(Qt::black);
    QBrush brushWhite(Qt::white);
    int a=200,b=50;
    QPoint pt(a,b);
    for(int j=0;j<8;j++)
    {
        for(int i=0;i<4;i++)
        {
            QRect rectBlack(a,b,70,70);
            QRect rectWhie(a-70,b,70,70);
            painter.fillRect(rectWhie,brushWhite);
            painter.fillRect(rectBlack,brushBlack);
            a+=140;
        }
        if(j%2==0)
        {
            brushBlack.setColor(Qt::white);
            brushWhite.setColor(Qt::black);
        }
        else
        {
            brushBlack.setColor(Qt::black);
            brushWhite.setColor(Qt::white);
        }
        a=200;
        b+=70;
    }
    painter.drawRect(QRect(123,43,574,574));
}
bool board::rockLimits(int x, int y, int pieceX, int pieceY, int p, QPoint *T)
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
void board::rokSugg(QPainter &painter,QPoint *T,QPoint *enemy, int pos,bool castling)
{
    int minX=690,minY=610,maxX=60,maxY=-20;
    int pieceX = T[pos].x(),pieceY = T[pos].y();
    for(int i=0;i<16;i++){
        int x = T[i].x(),y = T[i].y();
        int xE = enemy[i].x(),yE = enemy[i].y();
            if(pieceX == x){
                if(y>pieceY){
                    if(y < minY)
                        minY = y;
                }
                else if(y<pieceY){
                    if(y > maxY)
                        maxY = y;
                }
            }
            else if(pieceY == y){
                if(x>pieceX){
                    if(x < minX)
                        minX = x;
                }
                else{
                    if(x > maxX)
                        maxX = x;
                }
            }
            if(pieceX == xE){
                if(yE>pieceY){
                    if(yE < minY){
                        minY= yE;
                        minY += 70;
                    }
                }
                else{
                    if(yE > maxY){
                        maxY = yE;
                        maxY -= 70;
                    }
                }
            }
            else if(pieceY == yE){
                if(xE>pieceX){
                    if(xE < minX){
                        minX = xE;
                        minX += 70;
                    }
                }
                else{
                    if(xE > maxX){
                        maxX = xE;
                        maxX -= 70;
                    }
                }
            }
        }
    QBrush brush(Qt::red,Qt::Dense4Pattern);
    if(castling){
        if(rockLimits(T[4].x(),T[4].y(),pieceX,pieceY,-1,enemy) && rockLimits(T[4].x(),T[4].y(),pieceX,pieceY,4,T)){
           painter.fillRect(QRect(T[4].x(),T[4].y(),70,70),brush);
        }
    }
    for(int i=pieceY;i<minY;i+=70)
        painter.fillRect(QRect(pieceX,i, 70, 70), brush);
    for(int i=pieceY;i>maxY;i-=70)
        painter.fillRect(QRect(pieceX,i, 70, 70), brush);
    for(int i=pieceX;i<minX;i+=70)
        painter.fillRect(QRect(i,pieceY, 70, 70), brush);
    for(int i=pieceX;i>maxX;i-=70)
        painter.fillRect(QRect(i,pieceY, 70, 70), brush);

}

void board::kingSugg(QPainter &painter, QPoint *T,QPoint *enemy,int pos,bool castling)
{
    int pieceX = T[pos].x(),pieceY = T[pos].y();
    QBrush brush(Qt::red, Qt::Dense4Pattern);
    int x,y;
    bool test[9];
    for(int i=0;i<9;i++)
        test[i]=true;
        if(pieceX -70<130){
            test[0]=false;
            test[3]=false;
            test[6]=false;
        }
        if(pieceX+70 >620){
            test[2]=false;
            test[5]=false;
            test[8]=false;
        }
        if(pieceY -70<50){
            test[0]=false;
            test[1]=false;
            test[2]=false;
        }
        if(pieceY +70>540){
            test[6]=false;
            test[7]=false;
            test[8]=false;
        }
    for(int i=0;i<16;i++){
        x= T[i].x();y = T[i].y();
        if(pieceY == y +70){
            if(pieceX == x+70)
                test[0]=false;
            else if(pieceX == x)
                test[1]=false;
            else if(pieceX == x-70)
                test[2]=false;
        }
        else if(pieceY == y){
            if(pieceX == x+70)
                test[3]=false;
            else if(pieceX  == x-70)
                test[5]=false;
        }
        else if(pieceY == y-70){
            if(pieceX == x+70)
                test[6]=false;
            else if(pieceX == x)
                test[7]=false;
            else if(pieceX  == x-70)
                test[8]=false;
        }

    }
   x = pieceX-70;y = pieceY-70;
    for(int i=0;i<9;i++){
        if(i%3 == 0&&i!=0){
            x = pieceX-70;
            y+=70;
        }

        if(test[i] == true){
            painter.fillRect(QRect(x,y,70,70), brush);
        }
        x+=70;
    }
    if(castling){
        if(rockLimits(pieceX,pieceY,T[0].x(),T[0].y(),-1,enemy) && rockLimits(pieceX,pieceY,T[0].x(),T[0].y(),4,T)){
           painter.fillRect(QRect(T[0].x(),T[0].y(),70,70), brush);
        }
        if(rockLimits(pieceX,pieceY,T[7].x(),T[7].y(),4,enemy) && rockLimits(pieceX,pieceY,T[0].x(),T[0].y(),4,T)){
           painter.fillRect(QRect(T[7].x(),T[7].y(),70,70), brush);
        }
    }
}

void board::knightSugg(QPainter &painter, QPoint *T, int pos)
{
    int pieceX = T[pos].x(),pieceY = T[pos].y();
    QBrush brush(Qt::red, Qt::Dense4Pattern);
    painter.fillRect(QRect(pieceX,pieceY,70,70), brush);
    int x,y;
    bool test[8];
    for(int i=0;i<8;i++)
        test[i] = true;
    if(pieceX - 70 < 130){
        test[0] = false;
        test[2] = false;
        test[4] = false;
        test[6] = false;
    }
    else if(pieceX - 140 < 130){
        test[4] = false;
        test[2] = false;
    }
    if(pieceX + 70 > 620){
        test[1] = false;
        test[3] = false;
        test[5] = false;
        test[7] = false;
    }
    else if(pieceX + 140 > 620){
        test[3] = false;
        test[5] = false;
    }

    if(pieceY - 70 < 50){
        test[0] = false;
        test[1] = false;
        test[2] = false;
        test[3] = false;
    }
    else if(pieceY - 140 < 50){
        test[0] = false;
        test[1] = false;
    }
    if(pieceY + 70 > 540){
        test[4] = false;
        test[5] = false;
        test[6] = false;
        test[7] = false;
    }
    else if(pieceY + 140 > 540){
        test[6] = false;
        test[7] = false;
    }

    for(int i=0;i<16;i++){
        x=T[i].x();y=T[i].y();
        if(pieceY -140 == y){
            if(pieceX - 70 == x)
                test[0] = false;
            else if(pieceX +70 == x)
                test[1] = false;

        }
        else if(pieceY -70 == y){
            if(pieceX -140 == x)
                test[2] = false;
            else if(pieceX + 140 == x)
                test[3] = false;
        }
        else if(pieceY +70 == y){
            if(pieceX - 140 == x)
                test[4] = false;
            else if(pieceX +140 == x)
                test[5] = false;

        }
        else if(pieceY +140 == y){
            if(pieceX -70 == x)
                test[6] = false;
            else if(pieceX + 70 == x)
                test[7] = false;
        }
    }
    x = pieceX-70; y = pieceY - 140;
    for(int i=0;i<8;i++){
        if(i==2 || i == 4){
            y += 70;
            x = pieceX -140;
            if(i==4)
                y+=70;
        }
        if(i == 6){
            y += 70;
            x = pieceX -70;
        }
        if(test[i]){
            painter.fillRect(QRect (x,y,70,70), brush);
        }
        x+=140;
        if(i == 2 || i == 4)
            x+=140;


    }
}

void board::bishopSugg(QPainter &painter, QPoint *T, QPoint *enemy, int pos)
{
    int pieceX = T[pos].x(),pieceY = T[pos].y();
    int xE,yE,x,y,minX1=690,minY1=610,maxX1=60,maxY1=-20,minX2=690,minY2=-20,maxX2=60,maxY2=610;
        for(int i=0;i<16;i++){
            x = T[i].x() ; y = T[i].y();
            xE = enemy[i].x();yE = enemy[i].y();
            if(abs(x-pieceX) == abs(y -pieceY)){
                 if(x>pieceX && y>pieceY){
                         if(x < minX1){
                             minX1 = x;
                             minY1 = y;
                         }
                 }
                 else if(x>pieceX && y<pieceY ){
                         if(x < minX2){
                             minX2 = x;
                             minY2 = y;
                         }
                 }
                 else if(x<pieceX && y<pieceY){
                         if(x > maxX1){
                             maxX1 = x;
                             maxY1 = y;
                         }
                 }
                 else if(x<pieceX && y>pieceY){
                         if(x > maxX2){
                             maxX2 = x;
                             maxY2 = y;
                         }
                 }
             }

            if(abs(xE-pieceX) == abs(yE -pieceY)){
                if(xE>pieceX && yE>pieceY){
                        if(x < minX1){
                            minX1 = xE;
                            minY1 = yE;
                            minX1 += 70;
                            minY1 += 70;
                        }
                }
                else if(xE>pieceX && yE<pieceY ){
                        if(x < minX2){
                            minX2 = xE;
                            minY2 = yE;
                            minX2+=70;
                            minY2 -= 70;
                        }
                }
                else if(xE<pieceX && yE<pieceY){
                        if(x > maxX1){
                            maxX1 = xE;
                            maxY1 = yE;
                            maxX1 -=70;
                            maxY1 -= 70;
                        }
                }
                else if(xE<pieceX && yE>pieceY){
                        if(x > maxX2){
                            maxX2 = xE;
                            maxY2 = yE;
                            maxX2 -=70;
                            maxY2 +=70;
                        }
                }
            }
            }
    QBrush brush(Qt::red,Qt::Dense4Pattern);
    for(int i=pieceX,j=pieceY;i<minX1&&j<minY1;i+=70,j+=70)
        painter.fillRect(QRect(i,j,70, 70), brush);
    for(int i=pieceX,j=pieceY;i<minX2&&j>minY2;i+=70,j-=70)
        painter.fillRect(QRect(i,j, 70, 70), brush);
    for(int i=pieceX,j=pieceY;i>maxX1&&j>maxY1;i-=70,j-=70)
        painter.fillRect(QRect(i,j, 70, 70), brush);
    for(int i=pieceX,j=pieceY;i>maxX2&&j<maxY2;i-=70,j+=70)
        painter.fillRect(QRect(i,j, 70, 70), brush);

}

void board::pawnSugg(QPainter &painter, QPoint *T, QPoint *enemy, int pos,bool test,int enemyPawn)
{
    int pieceX = T[pos].x(),pieceY = T[pos].y(),x,y,xE,yE;
    bool draw[2] ;
    bool capture[2];
    for(int i=0;i<2;i++){
        draw[i]=true;
        capture[i]=false;
    }
    QBrush brush(Qt::red,Qt::Dense4Pattern);
    painter.fillRect(QRect(pieceX,pieceY,70, 70),brush);
    for(int i=0;i<16;i++){
        x = T[i].x();y = T[i].y();
        xE = enemy[i].x();yE = enemy[i].y();
            if(test){
                if(x == pieceX ){ //pawn first mouve
                    if(pieceY == 120){
                        if(y == 260)
                            draw[1] = false;
                        else if(y == 190){
                            draw[0] = false;
                            draw[1] = false;
                        }
                    }
                    else if(pieceY == y-70){
                        draw[1] = false;
                        draw[0] = false;
                    }
                    else
                        draw[1] = false;
                }
                if(yE-70 == pieceY && xE == pieceX)//pawn can capture a piece
                        draw[0] = false;
                else if(yE -70 == pieceY){
                    if(pieceX +70 == xE)
                        capture[0]=true;
                else if(pieceX -70 == xE)
                        capture[1] = true;
                }
            }
            else {
                if(x == pieceX ){
                    if(pieceY == 470){
                        if(y == 330)
                            draw[1] = false;
                        else if(y == 400){
                            draw[1] = false;
                            draw[0] = false;
                        }
                    }
                    else if(pieceY == y+70){
                        draw[1] = false;
                        draw[0] = false;
                    }
                    else
                        draw[1] = false;
            }
            if(yE+70 == pieceY && xE == pieceX)
                draw[0] = false;
            else if(yE+70 == pieceY){
                if(pieceX+70 == xE)
                   capture[0]=true;
             else if(pieceX-70 == xE)
                   capture[1] = true;
                }
            }

        }
        if(test){
            if(enemyPawn != -1){//en pasant
                if(enemy[enemyPawn].y() == pieceY){
                    if(enemy[enemyPawn].x() == pieceX+70)
                        capture[0]=true;
                    else if(enemy[enemyPawn].x() == pieceX-70)
                        capture[1]=true;
                }
            }
            if(draw[1]){
                painter.fillRect(QRect(pieceX,pieceY+70,70, 70), brush);
                painter.fillRect(QRect(pieceX,pieceY+140,70, 70), brush);
            }
            else if(draw[0])
                painter.fillRect(QRect(pieceX,pieceY+70,70, 70), brush);
            if(capture[0])
                painter.fillRect(QRect(pieceX+70,pieceY+70,70, 70), brush);
            if(capture[1])
                painter.fillRect(QRect(pieceX-70,pieceY+70,70, 70), brush);

    }
    else {
            if(enemyPawn != -1){
                if(enemy[enemyPawn].y() == pieceY){
                    if(enemy[enemyPawn].x() == pieceX+70)
                        capture[0]=true;
                    else if(enemy[enemyPawn].x() == pieceX-70)
                        capture[1]=true;
                }
            }
            if(draw[1]){
                painter.fillRect(QRect(pieceX,pieceY-70,70, 70), brush);
                painter.fillRect(QRect(pieceX,pieceY-140,70, 70), brush);
            }
            else if(draw[0])
                painter.fillRect(QRect(pieceX,pieceY-70,70, 70), brush);
            if(capture[0])
                painter.fillRect(QRect(pieceX+70,pieceY-70,70, 70), brush);
            if(capture[1])
                painter.fillRect(QRect(pieceX-70,pieceY-70,70, 70), brush);
    }

}
void board::suggestion(QPainter &painter,string sender,string *names,QPoint *T,QPoint *enemy,bool test,int *pawnProm,int enemyPawn,bool castling)
{
    int i=0,j;
    while(i<16){
        if(sender == names[i])
            break;
        i++;
   }
   j=i;
   //testing if pawn was promoted
    if(i<16 && i>7){
        if(pawnProm[i-8] != -1)
            i = pawnProm[i-8];
    }
    if(i == 0 || i == 7)
        rokSugg(painter,T,enemy,j,castling);
    else if(i == 4)
        kingSugg(painter,T,enemy,j,castling);
    else if(i == 1 || i == 6)
        knightSugg(painter,T,j);
    else if(i == 2 || i == 5)
        bishopSugg(painter,T,enemy,j);
    else if( i == 3){
        kingSugg(painter,T,enemy,j,false);
        rokSugg(painter,T,enemy,j,false);
        bishopSugg(painter,T,enemy,j);
    }
    else if (i>7 && i<16)
        pawnSugg(painter,T,enemy,j,test,enemyPawn);

}
