#ifndef TABLE_H
#define TABLE_H

#include <QObject>
#include <QVector>

class Table : public QObject
{
    Q_OBJECT

public:
    explicit Table(QObject *parent = 0);
    QVector <int> getTable(){return table_cards;}
private:
    QVector <int> table_cards;
    //const Table getTable();

signals:
    void siShowTableCard(int, int);
public slots:
    void slSetTable(int);
    void slShowCard(int);
};

#endif // TABLE_H
