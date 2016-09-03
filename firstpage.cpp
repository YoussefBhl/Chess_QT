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

}

firstPage::~firstPage()
{
    delete ui;
}

void firstPage::on_play_clicked()
{
    QRect geo;
    playWindow = new MainWindow;
    //mod playwindow postion
    geo = this->geometry();
    geo.setWidth(800);
    geo.setHeight(650);
    playWindow->setGeometry(geo);
    playWindow->show();
    connect(playWindow,SIGNAL(openingWindow()),this,SLOT(openingWindow()));
    this->hide();
}

void firstPage::on_conf_clicked()
{
    option = new optionPage;
    connect(option,SIGNAL(save_clicked()),this,SLOT(save_clicked()));
    connect(option,SIGNAL(cancel_clicked()),this,SLOT(cancel_clicked()));
    option->show();
    this->hide();

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


void firstPage::on_quit_clicked()
{
    this->close();
}
