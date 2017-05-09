#include "room.h"

Room::Room(QObject *parent) : QObject(parent)
{
    dealer = new Dealer();
    player = new Player();
    //ai_player = new NoobAI();
    ai_player = new ModernAI();
    //ai_player = new AIPlayer();
    table = new Table();
    //taking card from dealer
    connect(this->dealer, SIGNAL(siDealPl(int)), SIGNAL(siDealPl(int)));
    connect(this->dealer, SIGNAL(siDealAI(int)), SIGNAL(siDealAI(int)));
    connect(this->dealer, SIGNAL(siDealTable(int)), SIGNAL(siDealTable(int)));
    //and deal it to player, ai and table
    connect(this, SIGNAL(siDealPl(int)), this->player, SLOT(slSetHand(int)));
    connect(this, SIGNAL(siDealAI(int)), this->ai_player, SLOT(slSetHand(int)));
    connect(this, SIGNAL(siDealTable(int)), this->table, SLOT(slSetTable(int)));

    //showing hand to player, when he got 2 cards
    connect(this->player, SIGNAL(siShowHand(Hand*)), SIGNAL(siShowPlHand(Hand*)));

    //dealer showing bank and bet (after any bet)
    connect(this->dealer, SIGNAL(siShowBankAndBet(int, int)), SIGNAL(siShowBankAndBet(int, int)));

    //AIturn funs
    connect(this, SIGNAL(siAITurn()), this->dealer, SLOT(slShowBet()));
    connect(this->dealer, SIGNAL(siShowBet(int)), SIGNAL(siShowBet(int)));
    connect(this, SIGNAL(siShowBet(int)),this->ai_player, SLOT(slAction(int)));
    connect(this->ai_player, SIGNAL(siBet(int)), SIGNAL(siAISetBet(int)));
    connect(this, SIGNAL(siAISetBet(int)), this->dealer, SLOT(slSetBet(int)));

    //Showing table cards
    connect(this->dealer, SIGNAL(siShowCard()), SIGNAL(siShowCard()));
    connect(this, SIGNAL(siShowCard(int)), this->table, SLOT(slShowCard(int)));
    connect(this->table, SIGNAL(siShowTableCard(int, int)), SIGNAL(siShowTableCard(int, int)));

    //Player turn funs
    connect(this, SIGNAL(siPlBet(int, int)), this->player, SLOT(slPlBet(int, int)));
    connect(this->player, SIGNAL(siPlBet(int)), SIGNAL(siPlSetBet(int)));
    connect(this, SIGNAL(siPlSetBet(int)), this->dealer, SLOT(slSetBet(int)));

    //Player and AIPlayer bets (amount changes)
    connect(this->player, SIGNAL(siShowAmount(int)), SIGNAL(siShowPlAmount(int)));
    connect(this->ai_player, SIGNAL(siShowAmount(int)), SIGNAL(siShowAIAmount(int)));

    //AIPlayer hand
    connect(this, SIGNAL(siGetAIHand()), this->ai_player, SLOT(slShowAIHand()));
    connect(this->ai_player, SIGNAL(siShowHand(Hand*)), SIGNAL(siShowAIHand(Hand*)));

    //who win
    connect(this, SIGNAL(siWhoWin(QVector<int>, QVector<int>, QVector<int>)), this->dealer, SLOT(slWhoWin(QVector<int>, QVector<int>, QVector<int>)));
    connect(this->dealer, SIGNAL(siGivePlBank(int)), SIGNAL(siGivePlBank(int)));
    connect(this->dealer, SIGNAL(siGiveAIBank(int)), SIGNAL(siGiveAIBank(int)));
    connect(this, SIGNAL(siGivePlBank(int)), this->player, SLOT(slGetBank(int)));
    connect(this, SIGNAL(siGiveAIBank(int)), this->ai_player, SLOT(slGetBank(int)));
    connect(this->ai_player, SIGNAL(siShowWinner(QString)), SIGNAL(siShowWinner(QString)));
    connect(this->player, SIGNAL(siShowWinner(QString)), SIGNAL(siShowWinner(QString)));

    //pl or ai fold
    connect(this, SIGNAL(siFold(int)), this->dealer, SLOT(slFold(int)));
    connect(this->ai_player, SIGNAL(siAIFold(int)), SIGNAL(siFold(int)));

    //Tie
    connect(this->dealer, SIGNAL(siTie(int)), SIGNAL(siTie(int)));
    connect(this, SIGNAL(siTie(int)), this->player, SLOT(slGetTieBank(int)));
    connect(this, SIGNAL(siTie(int)), this->ai_player, SLOT(slGetTieBank(int)));
}

void Room::startGame()
{
    dealer->shuffle();
    dealer->dealCards();
    dealer->showBank();
    /*int amount;
    amount = player->showAmount();
    emit siShowPlAmount(amount);
    amount = ai_player->showAmount();
    emit siShowAIAmount(amount);*/
}

void Room::slGetHands()
{
    //Hand *ai = ai_player->getHand();
    //Hand *pl = player->getHand();
    QVector <int> pl_hand = player->getHand();
    QVector <int> ai_hand = ai_player->getHand();
    QVector <int> tb = table->getTable();
    emit siWhoWin(pl_hand, ai_hand, tb);
}

void Room::slChooseDiff(int diff)
{
    if(diff)
    {
        ai_player->setAIBehavior(new Modern());
    }
    else
    {
        ai_player->setAIBehavior(new Noob());
    }
}
