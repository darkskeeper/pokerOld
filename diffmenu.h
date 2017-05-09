#ifndef DIFFMENU_H
#define DIFFMENU_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class DiffMenu;
}

class DiffMenu : public QDialog
{
    Q_OBJECT

public:
    QRadioButton *radio1;
    QRadioButton *radio2;
    explicit DiffMenu(QWidget *parent = 0);
    ~DiffMenu();

private:
    Ui::DiffMenu *ui;
};

#endif // DIFFMENU_H
