#include "noob.h"

Noob::Noob() : AIBehavior()
{
    typ_bet=20;
}

int Noob::action(int last_bet)
{
    if (last_bet <= 20)
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
