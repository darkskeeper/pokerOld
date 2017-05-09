#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hide_table();
    /*table
    ui->T1_1->hide();
    ui->T1_2->hide();
    ui->T1_3->hide();
    ui->T1_4->hide();
    ui->T1_5->hide();*/
    is_table_ready = false;
    //player
    ui->LH1->hide();
    ui->H1_1->hide();
    ui->H1_2->hide();
    ui->betBut->hide();
    ui->BetAmountEdit->hide();
    ui->callBut->hide();
    ui->foldBut->hide();
    ui->TLcur_am->hide();
    ui->Lcur_am->hide();
    /*ai_player
    ui->LH2->hide();
    ui->H2_1->hide();
    ui->H2_2->hide();*/
    ui->TLcur_am_ai->hide();
    ui->Lcur_am_ai->hide();
    /*deal button
    ui->stgame->hide();*/
    //bank and bet
    ui->TLBank->hide();
    ui->LBank->hide();
    ui->TLBet->hide();
    ui->LBet->hide();

    room = new Room();

    //Showing Player's cards (called after deal(st_game button))
    connect(this->room, SIGNAL(siShowPlHand(Hand*)), SLOT(slShowPlHand(Hand*)));

    //Showing Bank and bet (called after every bet)
    connect(this->room, SIGNAL(siShowBankAndBet(int, int)), SLOT(slShowBankAndBet(int, int)));

    //Calling for AI Turn (after deal, turn, or when player raised
    connect(this, SIGNAL(siAITurn()), this->room, SIGNAL(siAITurn()));

    //Showing set of cards (after current bet = 0)
    connect(this->room, SIGNAL(siShowCard()), SLOT(slShowCard()));

    //Calling chosen card (after current bet = 0)
    connect(this, SIGNAL(siShowCard(int)), this->room, SIGNAL(siShowCard(int)));

    //Showing chosen card (after current bet = 0)
    connect(this->room, SIGNAL(siShowTableCard(int, int)), SLOT(slShowTableCard(int, int)));

    //Calling after player bet
    connect(this, SIGNAL(siPlBet(int, int)), this->room, SIGNAL(siPlBet(int, int)));

    //Showing after AIBet
    connect(this->room, SIGNAL(siShowAIAmount(int)), SLOT(slShowAIAmount(int)));

    //Showing after PlBet
    connect(this->room, SIGNAL(siShowPlAmount(int)), SLOT(slShowPlAmount(int)));

    //Showing after last bet in game
    connect(this, SIGNAL(siGetAIHand()), this->room, SIGNAL(siGetAIHand()));
    connect(this->room, SIGNAL(siShowAIHand(Hand*)), SLOT(slShowAIHand(Hand*)));

    //counting winner
    connect(this, SIGNAL(siWhoWin()), this->room, SLOT(slGetHands()));
    connect(this->room, SIGNAL(siShowWinner(QString)), SLOT(slShowWinner(QString)));

    //if player fold
    connect(this, SIGNAL(siFold(int)), this->room, SIGNAL(siFold(int)));

    //choosing difficulty
    connect(this, SIGNAL(siChooseDiff(int)), this->room, SLOT(slChooseDiff(int)));

    /*connect(room, SIGNAL(show(Hand*)), this, SLOT(show_players_hand(Hand*)));
    connect(room, SIGNAL(bet_to_bank(int)), this, SLOT(increaseBank(int)));
    connect(room, SIGNAL(ai_amount(int)), this, SLOT(show_ai_amount(int)));
    connect(this, SIGNAL(pl_bet(int &)), SLOT(show_pl_amount(int &)));
    connect(this, SIGNAL(sigAiAmount()), room, SIGNAL(sigAiAmount()));
    connect(this, SIGNAL(sigPlAmount()), room, SIGNAL(sigPlAmount()));
    connect(room, SIGNAL(sigPlAmount(int)), this, SLOT(slPlAmount(int)));*/
    setWindowTitle("Poker");
    setWindow();
    setMinimumSize(800, 600);
    //resize(1024, 768);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::parser(int card) //card to string
{
    QString str;
    if (card % 13 < 8)
    {
        str = QString::number((card % 13) + 2);
    }
    else
    {
        switch (card % 13)
        {
        case TEN:
            str = "T";
            break;
        case JACKET:
            str = "J";
            break;
        case QUEEN:
            str = "Q";
            break;
        case KING:
            str = "K";
            break;
        case ACE:
            str = "A";
            break;
        }
    }
    switch (card / 13)
    {
    case CLUBS:
        str += "♠";
        break;
    case SPADES:
        str += "♣";
        break;
    case DIAMONDS:
        str += "♦";
        break;
    case HEARTS:
        str += "♥";
        break;
    }
    return str;
}

void MainWindow::on_actionStart_Game_triggered()//after choosing start_game in menu we can see start_game button
{

    emit siFold(0);
    hide_table();

    DiffMenu *cd = new DiffMenu;
    if(cd->exec() == QDialog::Accepted)
    {
        ui->stgame->show();
        if(cd->radio1->isChecked())
        {
            emit siChooseDiff(0);
        }
        else
        {
            emit siChooseDiff(1);
        }
    }
    delete cd;

    is_table_ready = false;
    //player
    ui->LH1->hide();
    ui->H1_1->hide();
    ui->H1_2->hide();
    ui->betBut->hide();
    ui->BetAmountEdit->hide();
    ui->callBut->hide();
    ui->foldBut->hide();
    ui->TLcur_am->hide();
    ui->Lcur_am->hide();
    //ai_player
    ui->TLcur_am_ai->hide();
    ui->Lcur_am_ai->hide();
    //bank
    ui->TLBank->hide();
    ui->LBank->hide();
    ui->TLBet->hide();
    ui->LBet->hide();

    is_table_ready = false;
    ui->betBut->setDisabled(false);
    ui->callBut->setDisabled(false);
    ui->foldBut->setDisabled(false);

    //ui->stgame->show();
}

void MainWindow::on_actionStop_Game_triggered()//after choosing stop_game in menu, we hide all the table
{
    emit siFold(0);
    hide_table();

    is_table_ready = false;
    //player
    ui->LH1->hide();
    ui->H1_1->hide();
    ui->H1_2->hide();
    ui->betBut->hide();
    ui->BetAmountEdit->hide();
    ui->callBut->hide();
    ui->foldBut->hide();
    ui->TLcur_am->hide();
    ui->Lcur_am->hide();
    //ai_player
    ui->TLcur_am_ai->hide();
    ui->Lcur_am_ai->hide();
    //bank
    ui->TLBank->hide();
    ui->LBank->hide();
    ui->TLBet->hide();
    ui->LBet->hide();

    is_table_ready = false;
    ui->betBut->setDisabled(false);
    ui->callBut->setDisabled(false);
    ui->foldBut->setDisabled(false);
}

void MainWindow::on_stgame_clicked()//hiding table, setting it ready, starting game with AITurn
{
    set_table_ready();//showing buttons, bank and bet labels
    hide_table();//hiding table and ai_hand cards, hiding start_game button
    room->startGame();//deals and showing pl and ai amount
    if(ui->Lcur_am_ai->text().toInt() == 0)
    {
        setWindowTitle("Player won");
        close();
    }
    if(ui->Lcur_am->text().toInt() <= 0)
    {
        setWindowTitle("AI won");
        close();
    }
    fAITurn();
}

void MainWindow::slShowPlHand(Hand *hand)//showing players hand
{
    ui->LH1->show();
    ui->H1_1->show();
    ui->H1_2->show();
    //ui->H1_1->setText(parser(hand->cards[0]));
    //ui->H1_2->setText(parser(hand->cards[1]));
    //ui->pil1->setPixmap(":/images/" + QString::number(hand->cards[0]) + ".png");
    //ui->pil2->setPixmap(":/images/" + QString::number(hand->cards[1]) + ".png");
    ui->H1_1->setPixmap(":/images/" + QString::number(hand->cards[0]) + ".png");
    ui->H1_2->setPixmap(":/images/" + QString::number(hand->cards[1]) + ".png");
}

void MainWindow::slShowAIHand(Hand *hand)
{
    ui->LH2->show();
    ui->H2_1->show();
    ui->H2_2->show();
    //ui->H2_1->setText(parser(hand->cards[0]));
    //ui->H2_2->setText(parser(hand->cards[1]));
    //ui->ail1->setPixmap(":/images/" + QString::number(hand->cards[0]) + ".png");
    //ui->ail2->setPixmap(":/images/" + QString::number(hand->cards[1]) + ".png");
    ui->H2_1->setPixmap(":/images/" + QString::number(hand->cards[0]) + ".png");
    ui->H2_2->setPixmap(":/images/" + QString::number(hand->cards[1]) + ".png");
}

void MainWindow::slShowBankAndBet(int bank, int bet)//showing table bank and bet
{
    ui->LBank->setText(QString::number(bank));
    ui->LBet->setText(QString::number(bet));
}

//called after current_bet is 0
void MainWindow::slShowCard()//showing cards from table and some game management
{
    if (ui->T1_1->isHidden())//if first card is hidden, show first, second and third
    {
        emit siShowCard(0);//signal to get 0th card from table object
        emit siShowCard(1);
        emit siShowCard(2);
        ui->T1_1->show();//show lable, where we see our card
        ui->T1_2->show();
        ui->T1_3->show();
        fAITurn();
        /*ui->T1_1->setText(parser(room->table->table_cards[0]));*/
    }
    else if(ui->T1_4->isHidden())//if fourth card is hidden, show fourth
    {
        emit siShowCard(3);
        ui->T1_4->show();
        fAITurn();
    }
    else if(ui->T1_5->isHidden())//if fifth card is hidden, show fifth
    {
        emit siShowCard(4);
        ui->T1_5->show();
        fAITurn();
    }
    else
    {
        emit siGetAIHand();
        emit siWhoWin();
        if (true)
        {
            ui->stgame->show();
        }
        /*ui->stgame->show();
        ui->callBut->setDisabled(true);
        ui->betBut->setDisabled(true);
        ui->foldBut->setDisabled(true);*/
    }
}

//called after siShowCard going to Table and taking [value] card
void MainWindow::slShowTableCard(int value, int card)//showing cards from table (continue)
{
    switch(value)
    {
    case 0:
        //ui->T1_1->setText(parser(card));
        //ui->til1->setPixmap(":/images/" + QString::number(card) + ".png");
        ui->T1_1->setPixmap(":/images/" + QString::number(card) + ".png");
        break;
    case 1:
        //ui->T1_2->setText(parser(card));
        //ui->til2->setPixmap(":/images/" + QString::number(card) + ".png");
        ui->T1_2->setPixmap(":/images/" + QString::number(card) + ".png");
        break;
    case 2:
        //ui->T1_3->setText(parser(card));
        //ui->til3->setPixmap(":/images/" + QString::number(card) + ".png");
        ui->T1_3->setPixmap(":/images/" + QString::number(card) + ".png");
        break;
    case 3:
        //ui->T1_4->setText(parser(card));
        //ui->til4->setPixmap(":/images/" + QString::number(card) + ".png");
        ui->T1_4->setPixmap(":/images/" + QString::number(card) + ".png");
        break;
    case 4:
        //ui->T1_5->setText(parser(card));
        //ui->til5->setPixmap(":/images/" + QString::number(card) + ".png");
        ui->T1_5->setPixmap(":/images/" + QString::number(card) + ".png");
        break;
    }
}

//should be called after bet, at the beginning
void MainWindow::slShowPlAmount(int amount)
{
    ui->Lcur_am->setText(QString::number(amount));
}

//should be called after bet, at the beginning
void MainWindow::slShowAIAmount(int amount)
{
    ui->Lcur_am_ai->setText(QString::number(amount));
}

void MainWindow::slShowWinner(QString s)
{
    ui->TLResult->show();
    ui->LResult->show();
    ui->LResult->setText(s);
    ui->stgame->show();
    ui->callBut->setDisabled(true);
    ui->betBut->setDisabled(true);
    ui->foldBut->setDisabled(true);
}

//should be called after ending current deal
void MainWindow::hide_table()//hiding table and ai_hand cards, hiding start_game button
{
    ui->LH2->hide();
    ui->H2_1->hide();
    ui->H2_2->hide();
    ui->T1_1->hide();
    ui->T1_2->hide();
    ui->T1_3->hide();
    ui->T1_4->hide();
    ui->T1_5->hide();
    ui->stgame->hide();
    ui->TLResult->hide();
    ui->LResult->hide();
}

//should be called after we start deal
void MainWindow::set_table_ready()//showing buttons, bank and bet labels
{
    if(!is_table_ready)//if we come in 1st time, we show table
    {
        ui->TLBank->show();
        ui->LBank->show();
        ui->TLBet->show();
        ui->LBet->show();
        ui->betBut->show();
        ui->BetAmountEdit->show();
        ui->callBut->show();
        ui->foldBut->show();
        ui->TLcur_am->show();
        ui->Lcur_am->show();
        ui->TLcur_am_ai->show();
        ui->Lcur_am_ai->show();
        is_table_ready = true;
    }
    else//if it was, after we finished game, disabling buttons, that we disable after the game
    {
        ui->betBut->setDisabled(false);
        ui->callBut->setDisabled(false);
        ui->foldBut->setDisabled(false);
    }
    /*ui->Lcur_am->setText(QString::number(room->player->amount));
    //ui->Lcur_am_ai->setText(QString::number(room->ai_player->amount));
    //emit sigPlAmount();
    //emit sigAiAmount();
    //room->dealer->last_bet = room->ai_player->bet();
    //ui->LBank->setText(QString::number(room->dealer->bank));*/
}

//should be called after deal, each turn and if player raises
void MainWindow::fAITurn()
{
    //int temp = ui->LBet->text().toInt();
    emit siAITurn();//starting game with AITurn
}

void MainWindow::setWindow()
{
    ui->stgame->setGeometry(50, 250, 100, 50);
    ui->layoutWidget_3->setGeometry(175, 185, 450, 180);//table
    ui->layoutWidget->setGeometry(550, 125, 200, 50);//result
    ui->bankAndBetWidget->setGeometry(300, 120, 200, 60);//bank and bet
    ui->layoutWidget_5->setGeometry(265, 460, 270, 90);//plhand
    ui->layoutWidget_2->setGeometry(265, 0, 270, 90);//aihand
    ui->layoutWidget_4->setGeometry(650, 490, 150, 50);//plamount
    ui->layoutWidget_6->setGeometry(650, 0, 150, 50);//aiamount
    ui->buttonsWidget->setGeometry(550, 400, 200, 100);//buttons and edit
    //ui->layoutWidget->
    //ui->AIAmountLayout->resize(12, 12);
}

/*void MainWindow::show_ai_amount(int amount)
{
    ui->Lcur_am_ai->setText(QString::number(amount));
}


void MainWindow::increaseBank(int amount)
{
    room->dealer->bank += amount;
    ui->LBank->setText(QString::number(room->dealer->bank));
}

void MainWindow::on_callBut_clicked()
{
    emit pl_bet(room->dealer->last_bet);
    if (ui->T1_1->isHidden())
    {
        ui->T1_1->show();
        ui->T1_2->show();
        ui->T1_3->show();
        ui->T1_1->setText(parser(room->table->table_cards[0]));
        ui->T1_2->setText(parser(room->table->table_cards[1]));
        ui->T1_3->setText(parser(room->table->table_cards[2]));
    }
    else if(ui->T1_4->isHidden())
    {
        ui->T1_4->show();
        ui->T1_4->setText(parser(room->table->table_cards[3]));
    }
    else if(ui->T1_5->isHidden())
    {
        ui->T1_5->show();
        ui->T1_5->setText(parser(room->table->table_cards[4]));
    }
    else
    {
        ui->stgame->show();
        ui->LH2->show();
        ui->H2_1->show();
        ui->H2_2->show();
        ui->H2_1->setText(parser(room->ai_player->hand->cards[0]));
        ui->H2_2->setText(parser(room->ai_player->hand->cards[1]));
        room->player->amount+=room->dealer->giveBank();
        ui->callBut->setDisabled(true);
        ui->betBut->setDisabled(true);
        ui->foldBut->setDisabled(true);
        room->dealer->bank = 0;
    }
}


void MainWindow::on_betBut_clicked()
{
    room->player->amount-=room->dealer->last_bet;
    room->dealer->bank += room->dealer->last_bet;
    int last_bet = ui->BetAmountEdit->text().toInt();
    room->dealer->last_bet = last_bet;
    room->player->amount -= room->dealer->last_bet;
    ui->Lcur_am->setText(QString::number(room->player->amount));
    room->dealer->bank += room->dealer->last_bet;
    room->dealer->bank += room->ai_player->call(last_bet);
    ui->Lcur_am->setText(QString::number(room->ai_player->amount));
}

void MainWindow::show_pl_amount(int &cur_bet)
{
    room->player->amount-=cur_bet;
    increaseBank(cur_bet);
}

void MainWindow::slPlAmount(int value)
{
    ui->Lcur_am->setText(QString::number(value));
}

void MainWindow::slAiAmount(int value)
{
    ui->Lcur_am_ai->setText(QString::number(value));
}



*/

//pl turn
void MainWindow::on_callBut_clicked()
{
    int temp = ui->LBet->text().toInt();
    emit siPlBet(temp, 0);
    /*if(ui->T1_5->isHidden())
    {
        emit siAITurn();
    }*/
}

void MainWindow::on_betBut_clicked()
{
    int temp = ui->LBet->text().toInt();
    int bet = ui->BetAmountEdit->text().toInt();
    if (bet < 0 || bet > ui->Lcur_am->text().toInt())
    {
        Warning * dialog = new Warning;
        if(dialog->exec() == QDialog::Accepted)
        {
            ui->BetAmountEdit->clear();
        }
        delete dialog;
    }
    else
    {
        emit siPlBet(temp, bet);
        if(bet)
        {
            emit siAITurn();
        }
    }
}

void MainWindow::on_foldBut_clicked()
{
    emit siFold(0);
}
