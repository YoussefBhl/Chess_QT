#ifndef FIRSTPAGE_H
#define FIRSTPAGE_H

#include <QWidget>
#include "mainwindow.h"
#include "optionpage.h"
namespace Ui {
class firstPage;
}

class firstPage : public QWidget
{
    Q_OBJECT

public:
    explicit firstPage(QWidget *parent = 0);
    ~firstPage();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void save_clicked();
    void cancel_clicked();
private:
    Ui::firstPage *ui;
    MainWindow *playWindow;
    optionPage *option;
};

#endif // FIRSTPAGE_H
