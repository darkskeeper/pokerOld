#ifndef WARNING_H
#define WARNING_H
#include <QDialog>
#include <QtWidgets>


class Warning : public QDialog
{
    Q_OBJECT
public:
    Warning(QWidget *pwgt = 0);
};

#endif // WARNING_H
