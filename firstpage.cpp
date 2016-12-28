#include "firstpage.h"
#include "ui_firstpage.h"

firstPage::firstPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::firstPage)
{
    ui->setupUi(this);
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(":/images/images/chessBoard.jpg")))));
    setPalette(*palette);
    connect(ui->play,SIGNAL(mousePressed()),this,SLOT(mousePressed()));
    connect(ui->conf,SIGNAL(mousePressed()),this,SLOT(mousePressed()));
    connect(ui->quit,SIGNAL(mousePressed()),this,SLOT(mousePressed()));

    connect(ui->play,SIGNAL(cursorIn()),this,SLOT(cursorIn()));
    connect(ui->play,SIGNAL(cursorOut()),this,SLOT(cursorOut()));
    connect(ui->conf,SIGNAL(cursorIn()),this,SLOT(cursorIn()));
    connect(ui->conf,SIGNAL(cursorOut()),this,SLOT(cursorOut()));
    connect(ui->quit,SIGNAL(cursorIn()),this,SLOT(cursorIn()));
    connect(ui->quit,SIGNAL(cursorOut()),this,SLOT(cursorOut()));

    this->setFixedSize(900,600);
}

firstPage::~firstPage()
{
    delete ui;
}
void firstPage::save_clicked()
{
    option->hide();
    delete option;
    this->show();
}

void firstPage::openingWindow()
{
    delete playWindow;
    this->show();
}
void firstPage::cancel_clicked()
{
    option->hide();
    delete option;
    this->show();
}
void firstPage::cursorIn()
{
    string senderObj =  sender()->objectName().toLocal8Bit().constData();//QString to string
    if(senderObj == "play")
        ui->play->setStyleSheet("color:white");
    else if(senderObj == "conf")
        ui->conf->setStyleSheet("color:white");
    else if(senderObj == "quit")
        ui->quit->setStyleSheet("color:white");

}

void firstPage::cursorOut()
{
    string senderObj =  sender()->objectName().toLocal8Bit().constData();;
    if(senderObj == "play")
        ui->play->setStyleSheet("color:#ffbf00");
    else if(senderObj == "conf")
        ui->conf->setStyleSheet("color:#ffbf00");
    else if(senderObj == "quit")
        ui->quit->setStyleSheet("color:#ffbf00");
}

void firstPage::mousePressed()
{
    string senderObj =  sender()->objectName().toLocal8Bit().constData();
    if(senderObj == "play"){
        QRect geo;
        playWindow = new MainWindow;
        //mod playwindow postion
        geo = this->geometry();
        geo.setWidth(800);
        geo.setHeight(650);
        playWindow->setGeometry(geo);
        playWindow->setFixedSize(800,650);
        playWindow->show();
        connect(playWindow,SIGNAL(openingWindow()),this,SLOT(openingWindow()));
        connect(playWindow,SIGNAL(backButtom()),this,SLOT(backButtom()));
        this->hide();
    }
    else if(senderObj == "conf"){
        option = new optionPage;
        connect(option,SIGNAL(save_clicked()),this,SLOT(save_clicked()));
        connect(option,SIGNAL(cancel_clicked()),this,SLOT(cancel_clicked()));
        option->setFixedSize(900,600);
        option->show();
        this->hide();
    }
    else if(senderObj == "quit")
        this->close();
}

void firstPage::backButtom()
{
    delete playWindow;
    this->show();
}
