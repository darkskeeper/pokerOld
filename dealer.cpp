#include "dealer.h"

Dealer::Dealer(QObject *parent) : QObject(parent)
{
    bank = 0;
    last_bet = 0;
}

void Dealer::shuffle()
{
    this->deck.clear();
    for (int i = 0; i < 52; i++)
    {
        deck.push_back(i);
    }
    int random, temp;
    for (int i = 0; i < 52; i++)
    {
        random = rand() % 52;
        temp = deck[i];
        deck[i] = deck[random];
        deck[random] = temp;
    }
}

void Dealer::dealCards()
{
    bank = 0;
    int temp;
    QVector <int> ::iterator it;
    for(int i = 0; i < 5; i++)
    {
        if ( i < 2 )
        {
            //deal ai
            it = deck.begin();
            temp = rand() % deck.size();
            it += temp;
            temp = *it;
            deck.erase(it);
            emit siDealAI(temp);

            //deal player
            it = deck.begin();
            temp = rand() % deck.size();
            it += temp;
            temp = *it;
            deck.erase(it);
            emit siDealPl(temp);
        }

        //deal table
        it = deck.begin();
        temp = rand() % deck.size();
        it += temp;
        temp = *it;
        deck.erase(it);
        emit siDealTable(temp);
    }
}

void Dealer::showBank()
{
    emit siShowBankAndBet(bank, last_bet);
}

QVector <int> Dealer::det_comb(QVector<int> cards)
{
    //QVector <int> comb;
    sort(cards);
    QVector <int> def_cards(N_CARDS, 0);
    QVector <int> combs(5, 0);
    QVector <int> current_comb;
    QVector <int> comb_cards;
    current_comb.push_back(0);
    for (int i = 0; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
    {
        def_cards[cards[i]] = 1;
    }
    for (int i = 0; i < ONE_SUIT; i++)
    {
        combs[def_cards[i + (CLUBS * ONE_SUIT)] + def_cards[i + (SPADES * ONE_SUIT)] + def_cards[i + (DIAMONDS * ONE_SUIT)] + def_cards[i + (HEARTS * ONE_SUIT)]]++;
    }
    if (combs[4] == 1)
    {
        current_comb[0] = FOUR_OF_A_KIND;
    }
    else if ((combs[3] == 1 && combs[2] >= 1) || combs[3] > 1 )
    {
        current_comb[0] = FULL_HOUSE;
        setFH(cards, comb_cards);
        current_comb += comb_cards;
    }
    else if (combs[1] + combs[2] + combs[3] >= 5)
    {
        if (straight_check(cards, comb_cards))
        {
            if (straight_flash_check(cards, comb_cards))
            {
                if ( comb_cards[0] == ACE )
                {
                    current_comb[0] = ROYAL_FLASH;
                }
                else
                {
                    current_comb[0] = STRAIGHT_FLASH;
                }
                current_comb += comb_cards;
            }
            else
            {
                current_comb[0] = STRAIGHT;
                current_comb += comb_cards;
            }
        }
        else if (flash_check(cards))
        {
            current_comb[0] = FLASH;
            setFl(cards, comb_cards);
            current_comb += comb_cards;
        }
        else if (combs[3] == 1)
        {
            current_comb[0] = THREE_OF_A_KIND;
            setTOAK(cards, comb_cards);
            current_comb += comb_cards;
        }
        else if (combs[2] >= 2)
        {
            current_comb[0] = TWO_PAIRS;
            setTP(cards, comb_cards);
            current_comb += comb_cards;
        }
        else if (combs[2] == 1)
        {
            current_comb[0] = PAIR;
            setOP(cards, comb_cards);
            current_comb += comb_cards;
        }
        else
        {
            current_comb[0] = HIGH_CARD;
            setHC(cards, comb_cards);
            current_comb += comb_cards;
        }
    }
    else if (combs[3] == 1)
    {
        current_comb[0] = THREE_OF_A_KIND;
        setTOAK(cards, comb_cards);
        current_comb += comb_cards;
    }
    else if (combs[2] >= 2)
    {
        current_comb[0] = TWO_PAIRS;
        setTP(cards, comb_cards);
        current_comb += comb_cards;
    }
    return current_comb;
}

void Dealer::sort(QVector<int> &cards)
{
    int temp;
    for (int i = 0; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
    {
        for (int k = i + 1; k < N_CARDS_HAND + N_CARDS_TABLE; k++)
        {
            if ((cards[i] % 13) < (cards[k] % 13))
            {
                temp = cards[i];
                cards[i] = cards[k];
                cards[k] = temp;
            }
        }
    }
}

bool Dealer::straight_check(QVector<int> cards, QVector<int> &current_comb)
{
    QVector <int> ranks;
    QVector <int>::iterator it;
    ranks.push_back(cards[0] % 13);
    for (int i = 1; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
    {
        bool check = true;
        for (it = ranks.begin(); it != ranks.end(); it++)
        {
            if (*it == (cards[i] % 13))
            {
                check = false;
            }
        }
        if (check)
        {
            ranks.push_back(cards[i] % 13);
        }
    }
    for (int i = 0; (i + 4) < ranks.size(); i++)
    {
        if (ranks[i] - 4 == ranks[i + 4])
        {
            current_comb.push_back(ranks[i]);
            return true;
        }
    }
    int rs = ranks.size() - 1;
    if (ranks[rs] == TWO && ranks[rs - 1] == THREE && ranks[rs - 2] == FOUR && ranks[rs - 3] == FIVE && ranks[0] == ACE)
    {
        current_comb.push_back(-1);
        return true;
    }
    return false;
}

bool Dealer::flash_check(QVector<int> cards)
{
    QVector <int> suits(4, 0);
    for (int i = 0; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
    {
        suits[(cards[i] / 13)]++;
    }
    for (int i = 0; i < SUITS; i++)
    {
        if (suits[i] >= 5)
        {
            return true;
        }
    }
    return false;
}

bool Dealer::straight_flash_check(QVector<int> cards, QVector<int> &current_comb)
{
    QVector <int> suits(4, 0);
    if (current_comb[0] == -1)
    {
        int i = 0;
        while (cards[i] % 13 == ACE)
        {
            suits[cards[i] / 13]++;
            i++;
        }
        while (cards[i] % 13 != FIVE)
        {
            i++;
        }
        for (; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
        {
            suits[cards[i] / 13]++;
        }
    }
    else
    {
        int i = 0;
        while (current_comb[0] != cards[i] % 13)
        {
            i++;
        }
        while (i != N_CARDS_HAND + N_CARDS_TABLE && cards[i] % 13 >= current_comb[0] - 4)
        {
            suits[cards[i] / 13]++;
            i++;
        }
    }
    for (int i = 0; i < SUITS; i++)
    {
        if (suits[i] == 5)
        {
            return true;
        }
    }
    return false;
}

void Dealer::setHC(const QVector<int> &ccards, QVector<int> &current_comb)
{
    QVector <int> ::const_iterator it;
    int i = 0;
    for (it = ccards.begin(); i < 5; it++, i++)
    {
        current_comb.push_back(*it);
    }
}

void Dealer::setOP(QVector<int> ccards, QVector<int> &current_comb)
{
    QVector <int>::iterator it, it_current;
    it = ccards.begin();
    while (current_comb.empty())
    {
        for (it_current = it + 1; it_current != ccards.end(); it_current++)
        {
            if ((*it % 13) == (*it_current % 13))
            {
                current_comb.push_back(*it % 13);
                break;
            }
        }
        if (current_comb.empty())
        {
            it++;
        }
    }
    ccards.erase(it_current);
    ccards.erase(it);
    int i = 0;
    for (it = ccards.begin(); i < 3; it++, i++)
    {
        current_comb.push_back(*it);
    }
}

void Dealer::setTP(QVector<int> ccards, QVector<int> &current_comb)
{
    QVector <int>::iterator it, it_current;
    it = ccards.begin();
    it_current = it + 1;
    while (current_comb.size() != 2)
    {
        if (it_current == ccards.begin())
        {
            it = ccards.begin();
        }
        for (it_current = it + 1; it_current != ccards.end(); it_current++)
        {
            if ((*it % 13) == (*it_current % 13))
            {
                current_comb.push_back(*it % 13);
                ccards.erase(it_current);
                ccards.erase(it);
                it = it_current = ccards.begin();
                break;
            }
        }
        if (current_comb.size() != 2)
        {
            it++;
        }
    }
    current_comb.push_back(ccards[0] % 13);
}

void Dealer::setTOAK(QVector<int> ccards, QVector<int> &current_comb)
{
    QVector <int>::iterator it, it_current;
    it = ccards.begin();
    while (current_comb.empty())
    {
        for (it_current = it + 1; it_current != ccards.end(); it_current++)
        {
            if (*it % 13 == *it_current % 13)
            {
                if (current_comb.empty())
                {
                    current_comb.push_back(*it % 13);
                }
                ccards.erase(it_current);
                it_current = it;
            }
        }
        if (current_comb.empty())
        {
            it++;
        }
    }
    ccards.erase(it);
    int i = 0;
    for (it = ccards.begin(); i < 2; it++, i++)
    {
        current_comb.push_back(*it);
    }
}

void Dealer::setFl(QVector<int> ccards, QVector<int> &current_comb)
{
    int suit;
    QVector <int> suits(4, 0);
    for (int i = 0; i < N_CARDS_HAND + N_CARDS_TABLE; i++)
    {
        suits[(ccards[i] / 13)]++;
    }
    for (int i = 0; i < SUITS; i++)
    {
        if (suits[i] >= 5)
        {
            suit = i;
            break;
        }
    }
    QVector <int>::iterator it;
    int i = 0;
    for (it = ccards.begin(); i < 5; it++)
    {
        if ((*it / 13) == suit)
        {
            current_comb.push_back(*it);
            i++;
        }
    }
}

void Dealer::setFH(QVector<int> ccards, QVector<int> &current_comb)
{
    QVector <int>::iterator it, it_current, it_next;
    it = ccards.begin();
    int max = -1;
    while (it != ccards.end())
    {
        for (it_current = it + 1; it_current != ccards.end(); it_current++)
        {
            if (*it % 13 == *it_current % 13)
            {
                for (it_next = it_current + 1; it_next != ccards.end(); it_next++)
                {
                    if (*it_next % 13 == *it_current % 13)
                    {
                        if (*it % 13 > max)
                        {
                            max = *it % 13;
                        }
                        break;
                    }
                }
                break;
            }
        }
        it++;
    }
    current_comb.push_back(max);
    for (it = ccards.begin(); it < ccards.end(); it++)
    {
        if (*it % 13 == max)
        {
            ccards.erase(it);
            it = ccards.begin();
        }
    }
    it = ccards.begin();
    while (current_comb.size() != 2)
    {
        for (it_current = it + 1; it_current != ccards.end(); it_current++)
        {
            if ((*it % 13) == (*it_current % 13))
            {
                current_comb.push_back(*it % 13);
                break;
            }
        }
        it++;
    }
}




void Dealer::slShowBet()
{
    emit siShowBet(last_bet);
}

void Dealer::slSetBet(int amount)
{
    bank += last_bet;
    last_bet = amount;
    if (last_bet == 0)
    {
        //this->showBank();
        emit siShowCard();
    }
    else
    {
        bank += last_bet;
        this->showBank();
    }
    //this->showBank();
}

void Dealer::slWhoWin(QVector<int> pl_hand, QVector<int> ai_hand, QVector<int> table)
{
    QVector <int> pl = pl_hand + table;
    QVector <int> ai = ai_hand + table;
    //double pl_comb = det_comb(pl);
    //double ai_comb = det_comb(ai);
    pl = det_comb(pl);
    ai = det_comb(ai);
    int i = 0;
    int pls = pl.size();
    while (i < pls)
    {
        if(pl[i]%13 < ai[i]%13)
        {
            emit siGiveAIBank(bank);
            i = 100;
            break;
        }
        else if (pl[i]%13 > ai[i]%13)
        {
            emit siGivePlBank(bank);
            i = 100;
            break;
        }
        i++;
    }
    if (i != 100)
    {
        emit siTie(bank/2);
    }
    //bank = 0;
    //emit siShowBankAndBet(bank, last_bet);
    showBank();
    bank = 0;
}
    /*if(pl[0])
    {
        //pl won
        emit siGivePlBank(this->bank);
    }
    else if(ai[0])
    {
        //ai won
        emit siGiveAIBank(bank);
    }
    else if(!table.isEmpty())
    {
        emit siGivePlBank(this->bank);
        //draw
    }
    //bank = 0;
}*/

void Dealer::slFold(int key)
{
    if(key == 0)
    {
        siGiveAIBank(bank);
    }
    else
    {
        siGivePlBank(bank);
    }
    last_bet = 0;
    emit siShowBankAndBet(bank, last_bet);
    bank = 0;
}
