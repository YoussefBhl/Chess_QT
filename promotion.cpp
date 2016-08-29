#include "promotion.h"
#include "ui_promotion.h"

promotion::promotion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::promotion)
{
    ui->setupUi(this);
}

promotion::~promotion()
{
    delete ui;
}

void promotion::setSugg(bool playerTurn)
{
    if(playerTurn){
        rock = QPixmap(":/images/images/player1Rok.png");
        knight = QPixmap(":/images/images/player1Horse.png");
        bishop = QPixmap(":/images/images/player1Bishop.png");
        queen = QPixmap(":/images/images/player1Queen.png");
    }
    else{
        rock = QPixmap(":/images/images/player2Rok.png");
        knight = QPixmap(":/images/images/player2Horse.png");
        bishop = QPixmap(":/images/images/player2Bishop.png");
        queen = QPixmap(":/images/images/player2Queen.png");
    }

    ui->rock->setPixmap(rock);
    ui->knight->setPixmap(knight);
    ui->bishop->setPixmap(bishop);
    ui->queen->setPixmap(queen);
    connect(ui->rock,SIGNAL(mousePressed()),this,SLOT(mousePressed()));
    connect(ui->knight,SIGNAL(mousePressed()),this,SLOT(mousePressed()));
    connect(ui->bishop,SIGNAL(mousePressed()),this,SLOT(mousePressed()));
    connect(ui->queen,SIGNAL(mousePressed()),this,SLOT(mousePressed()));
}

void promotion::mousePressed()
{
    senderObj = sender()->objectName().toLocal8Bit().constData();
    if(senderObj == "rock"){
            *a = 0;
            l->setPixmap(rock);
            this->close();
    }
    if(senderObj == "knight"){
            *a = 1;
            l->setPixmap(knight);
            this->close();
    }
    if(senderObj == "bishop"){
            *a = 2;
            l->setPixmap(bishop);
            this->close();
    }
    if(senderObj == "queen"){
            *a = 3;
            l->setPixmap(queen);
            this->close();
    }
}
