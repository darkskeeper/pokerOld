#include "diffmenu.h"
#include "ui_diffmenu.h"

DiffMenu::DiffMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiffMenu)
{
    ui->setupUi(this);
    QGridLayout *grid = new QGridLayout;
    QGroupBox *groupBox = new QGroupBox(tr("Choose Difficulty"));
    radio1 = new QRadioButton(tr("&Ez"));
    radio1->setChecked(true);
    radio2 = new QRadioButton(tr("&Med"));
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio1);
    vbox->addWidget(radio2);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    grid->addWidget(groupBox, 0, 0);
    grid->addWidget(ui->buttonBox, 1, 0);
    setLayout(grid);
    setWindowTitle("Choose AI difficulty");
}

DiffMenu::~DiffMenu()
{
    delete ui;
}
