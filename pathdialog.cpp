#include "pathdialog.h"
#include "ui_pathdialog.h"

/**
PathDialog::PathDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pathDialog)
{
    ui->setupUi(this);
}**/
PathDialog::PathDialog(const QVector<City*>& cities, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PathDialog)
{
    ui->setupUi(this);

    for (City* c : cities) {
        ui->comboBox_start->addItem(c->getName());
        ui->comboBox_end->addItem(c->getName());
    }
}


QString PathDialog::getStartCity() const
{
    return ui->comboBox_start->currentText();
}

QString PathDialog::getEndCity() const
{
    return ui->comboBox_end->currentText();
}

PathDialog::~PathDialog()
{
    delete ui;
}
