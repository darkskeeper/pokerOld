#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "room.h"
#include "warning.h"
#include "diffmenu.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionStart_Game_triggered();
    void on_actionStop_Game_triggered();
    void on_stgame_clicked();

    void on_callBut_clicked();

    void on_betBut_clicked();

    void on_foldBut_clicked();

public slots:
    void slShowPlHand(Hand*);
    void slShowAIHand(Hand*);
    void slShowBankAndBet(int bank, int bet);
    void slShowCard();
    void slShowTableCard(int value, int card);
    void slShowPlAmount(int);
    void slShowAIAmount(int);
    void slShowWinner(QString);
signals:
    void siAITurn();
    void siShowCard(int );
    void siPlBet(int, int );
    void siGetAIHand();
    void siWhoWin();
    void siFold(int);
    void siChooseDiff(int);
private:
    Ui::MainWindow *ui;
    QString parser(int);
    Room *room;
    void hide_table();
    bool is_table_ready;
    void set_table_ready();
    void fAITurn();
    void setWindow();
};

#endif // MAINWINDOW_H
