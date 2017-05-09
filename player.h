#ifndef PLAYER_H
#define PLAYER_H
#include "hand.h"

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    const int & showAmount(){return amount;}
    //Hand* getHand(){return hand;}
    QVector <int> getHand(){return hand->cards;}
private:
    Hand *hand;
    int amount;

signals:
    void siShowHand(Hand *);
    void siPlBet(int);
    void siShowAmount(int);
    void siShowWinner(QString);

public slots:
    void slSetHand(int);
    void slPlBet(int, int);
    void slGetBank(int);
    void slGetTieBank(int);
};

#endif // PLAYER_H
