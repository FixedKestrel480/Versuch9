#ifndef CITYDIALOG_H
#define CITYDIALOG_H

#include <QDialog>

namespace Ui {
class CityDialog;
}

class CityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CityDialog(QWidget *parent = nullptr);
    ~CityDialog();
    QString getCityName() const;
    int getX() const;
    int getY() const;

private:
    Ui::CityDialog *ui;
};

#endif // CITYDIALOG_H
