#include "aiplayer.h"

AIPlayer::AIPlayer(QObject *parent) : QObject(parent)
{
    amount = 1000;
    //amount = 20;
    hand = new Hand();
    emit siShowAmount(amount);
}

void AIPlayer::setAIBehavior(AIBehavior *ai)
{
    aiBehavior = ai;
}

void AIPlayer::AICall(int last_bet)
{
    if (last_bet >= amount)
    {
        amount -= last_bet;
        emit siBet(0);
    }
    else if (last_bet == 0)
    {
        amount -= aiBehavior->typ_bet;
        emit siBet(aiBehavior->typ_bet);
    }
    else
    {
        amount -= last_bet;
        last_bet = 0;
        emit siBet(last_bet);
    }
}

void AIPlayer::AIBet(int last_bet)
{
    amount -= (aiBehavior->typ_bet + last_bet);
    last_bet = aiBehavior->typ_bet;
    emit siBet(last_bet);
}

/*void AIPlayer::defineHand()
{
    if(((hand->cards[0]%13 == ACE || hand->cards[0]%13 == KING || hand->cards[0]%13 == QUEEN)&&(hand->cards[0]%13 == hand->cards[1]%13))||(hand->cards[0]%13 == ACE && hand->cards[1]%13 == KING))
    {
        hand_strength == 100;
    }
    else if((hand->cards[0]%13 == JACKET || hand->cards[0]%13 == TEN)&&(hand->cards[0]%13 == hand->cards[1]%13))
    {
        hand_strength = 99;
    }
}*/

void AIPlayer::slAction(int last_bet)
{
    int choice = aiBehavior->action(last_bet);
    if (choice)
    {
        AICall (last_bet);
    }
    else
    {
        emit siAIFold(1);
    }
    /*if (last_bet <= 50)
    {
        AICall(last_bet);
    }
    else
    {
        emit siAIFold(1);
    }*/
    emit siShowAmount(amount);
}

void AIPlayer::slSetHand(int card)
{
    if(hand->cards.size() == 2)
    {
        hand->cards.clear();
    }
    hand->cards.push_back(card);
    /*if(hand->cards.size() == 2)
    {
        defineHand();
    }*/
}

void AIPlayer::slShowAIHand()
{
    emit siShowHand(hand);
}

void AIPlayer::slGetBank(int bank)
{
    amount += bank;
    emit siShowAmount(amount);
    QString s = "AI_Player's Hand Won";
    emit siShowWinner(s);
}

void AIPlayer::slGetTieBank(int bank)
{
    amount += bank;
    emit siShowAmount(amount);
    QString s = "Tie";
    emit siShowWinner(s);
}
