#ifndef DEALER_H
#define DEALER_H

#include <QObject>
#include <QVector>
#include <table.h>
#include <hand.h>

class Dealer : public QObject
{
    Q_OBJECT

public:
    explicit Dealer(QObject *parent = 0);
    void shuffle();
    void dealCards();
    void showBank();

private:
    int bank, last_bet;
    QVector <int> deck;
    QVector <int> det_comb(QVector <int> cards);
    void sort(QVector <int>& cards);
    bool straight_check(QVector<int> cards, QVector <int> &current_comb);
    bool flash_check(QVector<int> cards);
    bool straight_flash_check(QVector<int> cards, QVector <int> &current_comb);
    void setHC(const QVector <int> &ccards, QVector <int> &current_comb);
    void setOP(QVector <int> ccards, QVector <int> &current_comb);
    void setTP(QVector <int> ccards, QVector <int> &current_comb);
    void setTOAK(QVector <int> ccards, QVector <int> &current_comb);
    void setFl(QVector <int> ccards, QVector <int> &current_comb);
    void setFH(QVector <int> ccards, QVector <int> &current_comb);

signals:
    void siDealTable(int);
    void siDealAI(int);
    void siDealPl(int);
    void siShowBankAndBet(int bank, int bet);
    void siShowBet(int);
    void siShowCard();
    void siGivePlBank(int);
    void siGiveAIBank(int);
    void siTie(int);
public slots:
    void slShowBet();
    void slSetBet(int);
    //void slWhoWin(Hand*, Hand*, Table*);
    void slWhoWin(QVector <int> pl_hand, QVector <int> ai_hand, QVector <int> table);
    void slFold(int);
};

#endif // DEALER_H
