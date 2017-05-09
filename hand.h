#ifndef HAND_H
#define HAND_H
#include <QVector>
const int SUITS = 4;
const int ONE_SUIT = 13;
const int N_CARDS_HAND = 2;
const int N_CARDS = 52;
const int N_CARDS_TABLE = 5;

enum RANK { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACKET, QUEEN, KING, ACE };
enum COMBINATIONS { HIGH_CARD, PAIR, TWO_PAIRS, THREE_OF_A_KIND, STRAIGHT, FLASH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLASH, ROYAL_FLASH };
enum SUIT { CLUBS, SPADES, DIAMONDS, HEARTS };
const QString c[10] = { "HIGH_CARD", "PAIR", "TWO_PAIRS", "THREE_OF_A_KIND", "STRAIGHT", "FLASH", "FULL_HOUSE", "FOUR_OF_A_KIND", "STRAIGHT_FLASH", "ROYAL_FLASH" };

class Hand
{
public:
    QVector <int> cards;
    Hand();
};

#endif // HAND_H
