#include "streetdialog.h"
#include "ui_streetdialog.h"

StreetDialog::StreetDialog(const QVector<City*>& cities,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StreetDialog)
{
    ui->setupUi(this);
    for(const City* city:cities){
        ui->comboBox_Start->addItem(city->getName());
        ui->comboBox_End->addItem(city->getName());
    }
}

StreetDialog::~StreetDialog()
{
    delete ui;
}

QString StreetDialog::getStartCity() const
{
    return ui->comboBox_Start->currentText();
}

QString StreetDialog::getEndCity() const
{
    return ui->comboBox_End->currentText();
}
