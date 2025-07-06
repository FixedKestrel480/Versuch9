#ifndef STREETDIALOG_H
#define STREETDIALOG_H

#include <QDialog>
#include <QVector>
#include "city.h"

namespace Ui {
class StreetDialog;
}

class StreetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StreetDialog(const QVector<City*>& cities, QWidget *parent = nullptr);
    ~StreetDialog();
    QString getStartCity() const;
    QString getEndCity() const;

private:
    Ui::StreetDialog *ui;
};

#endif // STREETDIALOG_H
