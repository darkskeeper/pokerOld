#include "mainwindow.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    MainWindow w;
    //QObject::connect(&w.room.ai_player, SIGNAL(bet_to_bank(int)), &w, SLOT(increaseBank(int&)));//bank changes
    //QObject::connect(&w.room.player, SIGNAL(&(w.room.player.show(Hand &))), &w, SLOT((&w.show_players_hand(Hand &))));//show player hand, when it's 2 cards
    w.show();
    //AIPlayer *ai = new ModernAI();
    //
    return a.exec();
}
