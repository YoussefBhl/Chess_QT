#include "optionpage.h"
#include "ui_optionpage.h"
#include <iostream>
using namespace std;
optionPage::optionPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optionPage)
{
    ui->setupUi(this);
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,*(new QBrush(*(new QPixmap(":/images/images/chessBoard.jpg")))));
    setPalette(*palette);
    //read min & sec of timer from file
    f = fopen("conf.txt","r");
    fscanf(f,"%d %d %d",&timerActive,&min,&sec);
    ui->minValue->setValue(min);
    ui->secValue->setValue(sec);
    ui->timer->setChecked(timerActive);
    fclose(f);
}

optionPage::~optionPage()
{
    delete ui;
    delete f;
}
void optionPage::on_timer_stateChanged(int arg1)
{
    //show min & sec if timer enabled else hide em
    if(!arg1){
        ui->min->close();
        ui->sec->close();
        ui->minValue->close();
        ui->secValue->close();
    }
    else{
        ui->min->show();
        ui->sec->show();
        ui->minValue->show();
        ui->secValue->show();
    }
    timerActive = arg1;
}
void optionPage::on_save_clicked()
{
    //save new valuess
    f = fopen("conf.txt","w+");
    fprintf(f,"%d%c%d%c%d",timerActive,'\n',ui->minValue->value(),'\n',ui->secValue->value());
    fclose(f);
    emit save_clicked();
}
void optionPage::on_cancel_clicked(){
    emit cancel_clicked();
}
