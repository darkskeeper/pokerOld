#include "modern.h"

Modern::Modern() : AIBehavior()
{
    typ_bet=40;
}

int Modern::action(int last_bet)
{
    if (last_bet <= 100)
    {
        //AICall(last_bet);
        return 1;
    }
    else
    {
        //emit siAIFold(1);
        return 0;
    }
}
