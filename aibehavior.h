#ifndef AIBEHAVIOR_H
#define AIBEHAVIOR_H


class AIBehavior
{
public:
    int typ_bet;
    AIBehavior();
    virtual int action(int);
};

#endif // AIBEHAVIOR_H
