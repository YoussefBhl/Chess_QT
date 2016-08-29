#include "playWindow.h"
#include "ui_playWindow.h"
#include "mouseevent.h"
#include "boardmouseevent.h"
#include "piecemouvement.h"
#include "lcdnumber.h"
using namespace std;
playWindow::playWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playWindow)
{
    ui->setupUi(this);

    //player 1 set path of pieces ' image
    QPixmap player1Rok(":/images/images/player1Rok.png");
    QPixmap player1Horse(":/images/images/player1Horse.png");
    QPixmap player1Bishop(":/images/images/player1Bishop.png");
    QPixmap player1Queen(":/images/images/player1Queen.png");
    QPixmap player1King(":/images/images/player1King.png");
    QPixmap player1Pawn(":/images/images/player1Pawn.png");

    //player 2 set path of pieces ' image
    QPixmap player2Rok(":/images/images/player2Rok.png");
    QPixmap player2Horse(":/images/images/player2Horse.png");
    QPixmap player2Bishop(":/images/images/player2Bishop.png");
    QPixmap player2Queen(":/images/images/player2Queen.png");
    QPixmap player2King(":/images/images/player2King.png");
    QPixmap player2Pawn(":/images/images/player2Pawn.png");

    //player 1 & 2 set attribute
    p1.setPieces({ui->player1Rok1,ui->player1Horse1,ui->player1Bishop1,ui->player1Queen,ui->player1King,ui->player1Bishop2,ui->player1Horse2,ui->player1Rok2
             ,ui->player1Pawn1,ui->player1Pawn2,ui->player1Pawn3,ui->player1Pawn4,ui->player1Pawn5,ui->player1Pawn6,ui->player1Pawn7,ui->player1Pawn8});
    p1.setPiecesName({"player1Rok1","player1Horse1","player1Bishop1","player1Queen","player1King","player1Bishop2","player1Horse2","player1Rok2"
                 ,"player1Pawn1","player1Pawn2","player1Pawn3","player1Pawn4","player1Pawn5","player1Pawn6","player1Pawn7","player1Pawn8"});
    p1.setPiecesImage({player1Rok,player1Horse,player1Bishop,player1Queen,player1King,player1Bishop,player1Horse,player1Rok,player1Pawn});
    p1.setPiecesPosition();


    p2.setPieces({ui->player2Rok1,ui->player2Horse1,ui->player2Bishop1,ui->player2Queen,ui->player2King,ui->player2Bishop2,ui->player2Horse2,ui->player2Rok2
             ,ui->player2Pawn1,ui->player2Pawn2,ui->player2Pawn3,ui->player2Pawn4,ui->player2Pawn5,ui->player2Pawn6,ui->player2Pawn7,ui->player2Pawn8});

    p2.setPiecesName({"player2Rok1","player2Horse1","player2Bishop1","player2Queen","player2King","player2Bishop2","player2Horse2","player2Rok2"
                 ,"player2Pawn1","player2Pawn2","player2Pawn3","player2Pawn4","player2Pawn5","player2Pawn6","player2Pawn7","player2Pawn8"});
    p2.setPiecesImage({player2Rok,player2Horse,player2Bishop,player2Queen,player2King,player2Bishop,player2Horse,player2Rok,player2Pawn});
    p2.setPiecesPosition();


    //connect plots and signals
    connect(ui->label,SIGNAL(mousePressedBoard()),this,SLOT(mousePressedBoard()));
    for(int i=0;i<16;i++){
        connect(p1.pieces[i],SIGNAL(mousePressed()),this,SLOT(mousePressed()));
        connect(p2.pieces[i],SIGNAL(mousePressed()),this,SLOT(mousePressed()));
    }
    //read timer minutes & seconds from config file
    f = fopen("conf.txt","r");
    fscanf(f,"%d %d %d",&timerActive,&min,&sec);
    if(timerActive){
        //count down intialzaion
        ui->lcdNumber->startCountDown(min,sec);
        if(ui->lcdNumber->timeValue->isNull())  //if timeout then change palyer turn
            p1.playerTurn = !p1.playerTurn;
    }
    else{
        delete ui->lcdNumber;
    }

}
playWindow::~playWindow()
{
    delete ui;
}
void playWindow::paintEvent(QPaintEvent *e)
{

  QPainter painter(this);

    board b;
    b.paintEvent(painter);
    if(segg){
    b.suggestion(painter,senderObj,p1.piecesName,p1.piecesPosition,p2.piecesPosition,p1.playerTurn);
    b.suggestion(painter,senderObj,p2.piecesName,p2.piecesPosition,p1.piecesPosition,p1.playerTurn);

    }
}
void playWindow::mousePressedBoard()
{
    //first player move
    for(int i=0;i<16;i++){
//        if(p1.playerTurn){
        if(p1.piecesName[i] == senderObj){
             p1.mouvePiece(ui->label->x,ui->label->y,p1.pieces[i],i,p2.piecesPosition);
        }
//    }
//        else{
            if(p2.piecesName[i] == senderObj){
                 p2.mouvePiece(ui->label->x,ui->label->y,p2.pieces[i],i,p1.piecesPosition);
            }
        }
    cpId = 0;
    segg  = !segg;
    capture = false;
    timer1 = new QTimer();
    if(p1.KingDanger){
    connect(timer1,SIGNAL(timeout()),this,SLOT(warningMes()));
//    timer->singleShot(2000, this, SLOT(warningMes()));
        timer1->start(800);
    }
    this->update();
}
void playWindow::mousePressed()
{
    senderObj = sender()->objectName().toLocal8Bit().constData();
    if(p1.playerTurn){
        while(!capture && cpId<16){
            if(senderObj == p1.piecesName[cpId]){
                capture = true;

            }
            else
                cpId++;
        }
        if(capture){
            for(int j=0;j<16;j++){
                if(senderObj == p2.piecesName[j]){
                    p1.capturePiece(p2.piecesPosition[j].x(),p2.piecesPosition[j].y(),p1.pieces[cpId],cpId,p2.piecesPosition,j);
                    capture = false;
                    cpId = 0;
                    delete p2.pieces[j];
                    p2.piecesPosition[j] = QPoint(0,0);
                    timer1->stop();
                }
            }
        }


    }
    segg = !segg;
    this->update();
}

void playWindow::warningMes()
{
    if(counter%2)
            ui->message->setText("KING IN DANGER!");
        else
            ui->message->setText("");
        counter++;
    QTimer::singleShot(5000,this, SLOT(endWarning()));

}

void playWindow::endWarning()
{
    ui->message->setText("");
    timer1->stop();
}


