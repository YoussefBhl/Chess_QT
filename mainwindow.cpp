#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->playerTurn->hide();
    ui->gameOverStatue->hide();
    //player 1 set path of pieces ' png
    QPixmap player1rock(":/images/images/player1Rock.png");
    QPixmap player1Knight(":/images/images/player1Knight.png");
    QPixmap player1Bishop(":/images/images/player1Bishop.png");
    QPixmap player1Queen(":/images/images/player1Queen.png");
    QPixmap player1King(":/images/images/player1King.png");
    QPixmap player1Pawn(":/images/images/player1Pawn.png");

    //player 2 set path of pieces ' image png
    QPixmap player2rock(":/images/images/player2Rock.png");
    QPixmap player2Knight(":/images/images/player2Knight.png");
    QPixmap player2Bishop(":/images/images/player2Bishop.png");
    QPixmap player2Queen(":/images/images/player2Queen.png");
    QPixmap player2King(":/images/images/player2King.png");
    QPixmap player2Pawn(":/images/images/player2Pawn.png");
    p1 = new player;
    p2 = new player;
    //player 1 & 2 set attribute
    p1->setPieces({ui->player1Rock1,ui->player1Knight1,ui->player1Bishop1,ui->player1Queen,ui->player1King,ui->player1Bishop2,ui->player1Knight2,ui->player1Rock2
             ,ui->player1Pawn1,ui->player1Pawn2,ui->player1Pawn3,ui->player1Pawn4,ui->player1Pawn5,ui->player1Pawn6,ui->player1Pawn7,ui->player1Pawn8});
    p1->setPiecesName({"player1Rock1","player1Knight1","player1Bishop1","player1Queen","player1King","player1Bishop2","player1Knight2","player1rock2"
                 ,"player1Pawn1","player1Pawn2","player1Pawn3","player1Pawn4","player1Pawn5","player1Pawn6","player1Pawn7","player1Pawn8"});
    p1->setPiecesImage({player1rock,player1Knight,player1Bishop,player1Queen,player1King,player1Bishop,player1Knight,player1rock,player1Pawn});
    p1->setPiecesPosition();


    p2->setPieces({ui->player2Rock1,ui->player2Knight1,ui->player2Bishop1,ui->player2Queen,ui->player2King,ui->player2Bishop2,ui->player2Knight2,ui->player2Rock2
             ,ui->player2Pawn1,ui->player2Pawn2,ui->player2Pawn3,ui->player2Pawn4,ui->player2Pawn5,ui->player2Pawn6,ui->player2Pawn7,ui->player2Pawn8});

    p2->setPiecesName({"player2Rock1","player2Knight1","player2Bishop1","player2Queen","player2King","player2Bishop2","player2Knight2","player2Rock2"
                 ,"player2Pawn1","player2Pawn2","player2Pawn3","player2Pawn4","player2Pawn5","player2Pawn6","player2Pawn7","player2Pawn8"});
    p2->setPiecesImage({player2rock,player2Knight,player2Bishop,player2Queen,player2King,player2Bishop,player2Knight,player2rock,player2Pawn});
    p2->setPiecesPosition();


    //connect plots and signals
    connect(ui->label,SIGNAL(mousePressedBoard()),this,SLOT(mousePressedBoard()));
    for(int i=0;i<16;i++){
        connect(p1->pieces[i],SIGNAL(mousePressed()),this,SLOT(mousePressed()));
        connect(p2->pieces[i],SIGNAL(mousePressed()),this,SLOT(mousePressed()));
    }
    //read timer minutes & seconds from config file
    f = fopen("conf.txt","r");
    fscanf(f,"%d %d %d",&timerActive,&min,&sec);
    //count down
    if(timerActive){
        ui->timerNotif->setText("Timer :");
        ui->lcdNumber->startCountDown(min,sec);
        ui->lcdNumber->timer->stop();
    }
    //players info
    QTimer::singleShot(1000,this, SLOT(playersInfo()));

}
MainWindow::~MainWindow()
{
    p1->playerTurn = true;
    p1->KingDanger =false;
    p1->canCapture =false;
    p1->gameOver =false;
    delete p1;
    delete p2;
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *e)
{

  QPainter painter(this);

    board b;
    b.paintEvent(painter);
    if(segg){
        if(p1->playerTurn)
            b.suggestion(painter,senderObj,p1->piecesName,p1->piecesPosition,p2->piecesPosition,p1->playerTurn,p1->pawnProm,p2->pawnEnPassant,castling);
        else
            b.suggestion(painter,senderObj,p2->piecesName,p2->piecesPosition,p1->piecesPosition,p1->playerTurn,p2->pawnProm,p1->pawnEnPassant,castling);
    }
    if(timerActive){
        if(ui->lcdNumber->timeValue->toString() == QString("00:00:00")){  //if timeout then change palyer turn
            p1->playerTurn = !p1->playerTurn;
            ui->lcdNumber->timer->stop();
            QTimer::singleShot(1000,this, SLOT(playerTurnDisplay()));
        }
    }

}

void MainWindow::piecePressed(string senderObj, player *p,player *enemyP)
{
    int j=0;
    while(!capture && cpId<16){
        if(senderObj == p->piecesName[cpId]){
            id = cpId;
            capture = true;
        }
        else
            cpId++;
    }
    //castling sugg
    if(cpId == 4 || cpId == 0 || cpId == 7){
        if(p->kingNeverChecked && !p->kingFirstMouve){
            if(cpId == 0 && !p->rockFirstMouve0)
                castling = true;
            else if(cpId == 7 && !p->rockFirstMouve7)
                castling = true;
            else if(cpId == 4){
                if(!p->rockFirstMouve0 || !p->rockFirstMouve7)
                   castling = true;
            }
        }
    }
    //testing pawn if it was pormoted or not
    if(cpId<16 && cpId>7){
        if(p->pawnProm[cpId-8] != -1)
            id = p->pawnProm[cpId-8];
    }

    if(capture){
        while(j<16){
            if(senderObj == enemyP->piecesName[j]){
                p->capturePiece(enemyP->piecesPosition[j].x(),enemyP->piecesPosition[j].y(),p->pieces[cpId],id,enemyP->piecesPosition,j,cpId);
                capture = false;
                cpId = 0;
                if(p->canCapture){
                    delete enemyP->pieces[j];
                    enemyP->piecesPosition[j] = QPoint(0,0);
                    p->canCapture = false;
                    if(p->playerTurn)
                        ui->playerTurn->setText("Player 1");
                    else
                        ui->playerTurn->setText("Player 2");
                    ui->playerTurn->show();
                    //count Down
                    if(timerActive){
                        ui->lcdNumber->timer->stop();
                    }
                    QTimer::singleShot(1000,this, SLOT(playerTurnDisplay()));
                }
                break;
            }
            else
                j++;
        }
        //castling
        if(j==16){
            if(cpId == 0 || cpId == 7){
                if(senderObj == p->piecesName[4]){
                        p->castling(enemyP->piecesPosition,cpId,4);
                }
            }
            if(cpId == 4){
                if(senderObj == p->piecesName[0])
                    p->castling(enemyP->piecesPosition,cpId,0);
                else if(senderObj == p->piecesName[7])
                    p->castling(enemyP->piecesPosition,cpId,7);
            }
        }
    }
}

void MainWindow::playerTurnDisplay()
{
    ui->playerTurn->hide();
    if(timerActive)
        ui->lcdNumber->startCountDown(min,sec);
}

void MainWindow::backTopeningWindow()
{
    emit openingWindow();
}

void MainWindow::mousePressedBoard()
{
    int i=0,j;
    bool restartCount = false;
    //first player move
        if(p1->playerTurn){
            p1->pawnEnPassant = -1;
            while(i<16){
                if(p1->piecesName[i] == senderObj){
                    j = i;
                    break;
                }
                else
                    i++;
            }
            if(i<16 && i>7){
                if(p1->pawnProm[i-8] != -1){
                    j = p1->pawnProm[i-8];
                    p1->mouvePiece(ui->label->x,ui->label->y,p1->pieces[i],j,p2->piecesPosition,i);
                }
                else{
                    p1->mouvePawn(ui->label->x,ui->label->y,p1->pieces[i],j,i,p2->piecesPosition,p2->pawnEnPassant);
                    //en passant
                    if(p1->canCapture){
                        delete p2->pieces[p2->pawnEnPassant];
                        p2->piecesPosition[p2->pawnEnPassant] = QPoint(0,0);
                    }
                    restartCount = true;
                }
            }
            else{
             p1->mouvePiece(ui->label->x,ui->label->y,p1->pieces[i],j,p2->piecesPosition,i);
             restartCount = true;
            }
    }
        else{
            p2->pawnEnPassant = -1;
            while(i<16){
                if(p2->piecesName[i] == senderObj){
                    j = i;
                    break;
                }
                else
                    i++;
            }
            if(i<16 && i>7){
                if(p1->pawnProm[i-8] != -1){
                    j = p2->pawnProm[i-8];
                    p2->mouvePiece(ui->label->x,ui->label->y,p2->pieces[i],j,p1->piecesPosition,i);
                }
                else{
                    p2->mouvePawn(ui->label->x,ui->label->y,p2->pieces[i],j,i,p1->piecesPosition,p1->pawnEnPassant);
                    restartCount = true;
                    //EN PASSENT
                    if(p2->canCapture){
                        delete p1->pieces[p1->pawnEnPassant];
                        p1->piecesPosition[p1->pawnEnPassant] = QPoint(0,0);
                    }
                    restartCount = true;
                }
            }
            else{
                p2->mouvePiece(ui->label->x,ui->label->y,p2->pieces[i],j,p1->piecesPosition,i);
                restartCount = true;
            }
       }
        if(p1->playerTurn)
            ui->playerTurn->setText("Player 1");
        else
            ui->playerTurn->setText("Player 2");
    if(restartCount){
        //count down
        if(timerActive)
            ui->lcdNumber->timer->stop();
        ui->playerTurn->show();
        QTimer::singleShot(1000,this, SLOT(playerTurnDisplay()));
    }
    cpId = 0;
    id = 0;
    segg  = !segg;
    capture = false;
    if(p1->KingDanger){
        ui->message->setText("Check King !");
    }
    else{
        ui->message->setText("");

    }
    if(p1->gameOver){
        ui->gameOverStatue->show();
        QString s = "GAME OVER";
        if(p1->playerTurn)
            s += "\n\n\n PLAYER 1 Win";
        else
            s += "\n\n\n PLAYER 2 Win";
        ui->gameOverStatue->setText(s);
        QTimer::singleShot(1000,this, SLOT(backTopeningWindow()));
    }
    this->update();

}
void MainWindow::mousePressed()
{
    senderObj = sender()->objectName().toLocal8Bit().constData();
    //player 1 turn
    if(p1->playerTurn){
        piecePressed(senderObj,p1,p2);
    }
    else{
        piecePressed(senderObj,p2,p1);
    }
    if(p1->KingDanger)
        ui->message->setText("Check King !");
    else
        ui->message->setText("");
    segg = !segg;
    if(p1->gameOver){
        ui->gameOverStatue->show();
        QString s = "GAME OVER";
        if(p1->playerTurn)
            s += "\n\n\n PLAYER 1 Win";
        else
            s += "\n\n\n PLAYER 2 Win";
        ui->gameOverStatue->setText(s);

        QTimer::singleShot(1000,this, SLOT(backTopeningWindow()));
    }
    this->update();
}

void MainWindow::endWarning()
{
    ui->message->setText("");
}

void MainWindow::playersInfo()
{
    delete ui->player1Info;
    delete ui->player2Info;
    ui->playerTurn->show();
    QTimer::singleShot(1000,this, SLOT(playerTurnDisplay()));
}


