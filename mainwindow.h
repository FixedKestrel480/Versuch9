#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "map.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
/**
 * @class MainWindow
 * @brief Main GUI window of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_addStadt_clicked(); //clicked button and add new city

    void on_actionExit_triggered();//Exit application

    void on_actionClear_Scene_triggered(); //clear graphics scene

    void on_actionAbout_triggered(); //show message when input add Stadt

    void on_pushButton_testDrawCity_clicked();

    void on_Buttonmap_clicked();//draw all cities and streets from the map

    void on_draw_city_clicked();//add two cities and connect with street

    void on_Testknop_toggled(bool checked);

    void on_pushButton_city_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene; //The graphics scene shown in the view
    Map* p_map; //Pointer to the current map object
};
#endif // MAINWINDOW_H
