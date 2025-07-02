#ifndef PATHDIALOG_H
#define PATHDIALOG_H

#include <QDialog>
#include "city.h"

namespace Ui {
class PathDialog;
}

class PathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PathDialog(const QVector<City*>& cities, QWidget *parent = nullptr);

    //explicit pathDialog(QWidget *parent = nullptr);
    ~PathDialog();
    QString getStartCity() const;
    QString getEndCity() const;

private:
    Ui::PathDialog *ui;
};

#endif // PATHDIALOG_H
