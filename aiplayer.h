#ifndef AIPLAYER_H
#define AIPLAYER_H
#include "hand.h"
#include "aibehavior.h"
#include "modern.h"
#include "noob.h"


#include <QObject>

class AIPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AIPlayer(QObject *parent = 0);
    const int & showAmount(){return amount;}
    //Hand* getHand(){return hand;}
    QVector <int> getHand(){return hand->cards;}
    AIBehavior *aiBehavior;
    void setAIBehavior(AIBehavior* ai);

private:
    int hand_strength;
    int amount;
    Hand *hand;
    void AICall(int);
    void AIBet(int);
    //void defineHand();

signals:
    void siShowHand(Hand *);
    void siBet(int);
    void siShowAmount(int);
    void siShowWinner(QString);
    void siAIFold(int);

public slots:
    void slAction(int last_bet);
    void slSetHand(int);
    void slShowAIHand();
    void slGetBank(int);
    void slGetTieBank(int);
};

#endif // AIPLAYER_H
