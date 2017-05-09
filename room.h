#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include "player.h"
//#include "aiplayer.h"
#include "dealer.h"
#include "table.h"
#include "modernai.h"
#include "noobai.h"

class Room : public QObject
{
    Q_OBJECT
public:
    explicit Room(QObject *parent = 0);
    void startGame();
private:
    Table *table;
    Player *player;
    AIPlayer *ai_player;
    Dealer *dealer;

signals:
    void siDealPl(int);
    void siDealAI(int);
    void siDealTable(int);
    void siShowPlHand(Hand *);
    void siGetAIHand();
    void siShowAIHand(Hand *);
    void siShowBankAndBet(int, int);
    void siAITurn();
    void siShowBet(int);
    void siAISetBet(int);
    void siPlSetBet(int);
    void siShowCard();
    void siShowCard(int);
    void siShowTableCard(int, int);
    void siPlBet(int, int);
    void siShowPlAmount(int);
    void siShowAIAmount(int);
    //void siWhoWin(Hand *, Hand *, Table *);
    void siWhoWin(QVector <int> pl_hand, QVector <int> ai_hand, QVector <int> table);
    void siGivePlBank(int);
    void siGiveAIBank(int);
    void siShowWinner(QString);
    void siFold(int);
    void siTie(int);
public slots:
    void slGetHands();
    void slChooseDiff(int);
};

#endif // ROOM_H
