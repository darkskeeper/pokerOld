#include "table.h"

Table::Table(QObject *parent) : QObject(parent)
{

}

/*const Table Table::getTable()
{
    return table_cards;
}*/

void Table::slSetTable(int card)
{
    if(table_cards.size()==5)
    {
        table_cards.clear();
    }
    table_cards.push_back(card);
}

void Table::slShowCard(int value)
{
    emit siShowTableCard(value, table_cards[value]);
}
