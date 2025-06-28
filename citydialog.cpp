#include "citydialog.h"
#include "ui_citydialog.h"

CityDialog::CityDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CityDialog)
{
    ui->setupUi(this);
}

CityDialog::~CityDialog()
{
    delete ui;
}

QString CityDialog::getCityName() const {
    return ui->lineEditStadt->text();
}

int CityDialog::getX() const {
    return ui->spinBoxX->value();
}

int CityDialog::getY() const {
    return ui->spinBoxY->value();
}
