#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
    amount = 1000;
    hand = new Hand();
}

void Player::slSetHand(int card)
{
    if(hand->cards.size() == 2)
    {
        hand->cards.clear();
        //emit showHand(hand);
    }
    hand->cards.push_back(card);
    if(hand->cards.size() == 2)
    {
        emit siShowHand(hand);
        emit siShowAmount(amount);
    }
}

void Player::slPlBet(int last_bet, int pl_bet)
{
    this->amount -= (last_bet + pl_bet);
    last_bet = pl_bet;
    emit siPlBet(last_bet);
    emit siShowAmount(amount);
}

void Player::slGetBank(int bank)
{
    amount += bank;
    emit siShowAmount(amount);
    QString s = "Player's Hand Won";
    emit siShowWinner(s);
}

void Player::slGetTieBank(int bank)
{
    amount += bank;
    emit siShowAmount(amount);
    QString s = "Tie";
    emit siShowWinner(s);
}
