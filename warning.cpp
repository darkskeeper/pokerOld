#include "warning.h"

Warning::Warning(QWidget *pwgt /*=0*/) : QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    QLabel * lbl = new QLabel("Wrong input");
    lbl->show();
    QPushButton* ok = new QPushButton("&ok");
    connect(ok, SIGNAL(clicked()), SLOT(accept()));
    QGridLayout * layout = new QGridLayout;
    layout->addWidget(lbl, 0, 0);
    layout->addWidget(ok, 1, 0);
    setLayout(layout);
    setWindowTitle("Warning");
    //addWidget(lbl);
}
