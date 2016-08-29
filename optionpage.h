#ifndef OPTIONPAGE_H
#define OPTIONPAGE_H

#include <QWidget>
#include <stdio.h>
#include <stdlib.h>
namespace Ui {
class optionPage;
}

class optionPage : public QWidget
{
    Q_OBJECT

public:
    explicit optionPage(QWidget *parent = 0);
    ~optionPage();
private slots:
    void on_timer_stateChanged(int arg1);
    void on_save_clicked();
    void on_cancel_clicked();
signals:
    void save_clicked();
    void cancel_clicked();
private:
    Ui::optionPage *ui;
    FILE *f;
    int  min,sec,timerActive=1;
};

#endif // OPTIONPAGE_H
