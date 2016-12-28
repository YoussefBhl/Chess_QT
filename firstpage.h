#ifndef FIRSTPAGE_H
#define FIRSTPAGE_H

#include <QWidget>
#include "mainwindow.h"
#include "optionpage.h"
#include "mouseevent.h"
namespace Ui {
class firstPage;
}

class firstPage : public QWidget
{
    Q_OBJECT

public:
    explicit firstPage(QWidget *parent = 0);
    ~firstPage();
    bool quit = false;
private slots:
    void save_clicked();
    void openingWindow();
    void cancel_clicked();
    void cursorIn();
    void cursorOut();
    void mousePressed();
    void backButtom(); // play window
private:
    Ui::firstPage *ui;
    MainWindow *playWindow;
    optionPage *option;
};

#endif // FIRSTPAGE_H
