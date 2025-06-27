#include "mainwindow.h"
#include "city.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "street.h"
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Create the scene
    scene = new QGraphicsScene(this);

    // Connect ti QGraphicsView from UI
    ui->graphicsView->setScene(scene);
    p_map = new Map();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_addStadt_clicked()
{
    // Reads line Edit text
    QString eingabe = ui->lineEdit_stadtname->text();
    //show text
    qDebug() << QString("Der Benutzer hat eingegeben: %1").arg(eingabe);

    //try to convert it to number and sum 4
    bool istZahl;
    int zahl = eingabe.toInt(&istZahl); //would be true if conversion erfolg
    QMessageBox::information(this, "Eingabe", QString("Du hast eingegeben: %1").arg(eingabe));
    int x = QRandomGenerator::global()->bounded(500); //random x location where the city will appear
    int y = QRandomGenerator::global()->bounded(500); // random y coordinate where the city will appear
    //int size = 30;

    //scene->addRect(x, y, size, size);

    City* neueStadt = new City(eingabe, x, y); //creates new object City
    p_map->addCity(neueStadt);       //Stores city to pointer/list p_map
    //neueStadt->draw(*scene);
 /**
    if(istZahl){
        int ergebnis = zahl + 4;
        qDebug() << QString("Die Zahl plus 4 ist: %1").arg(ergebnis);
    } else {
        qDebug() << "Die Eingabe ist keine Zahl.";
    }**/



}


void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::on_actionClear_Scene_triggered()
{
    scene->clear();//erase all elements of the map
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "Über diese App", "Streetplanner");

}


void MainWindow::on_pushButton_testDrawCity_clicked()
{
    //test the function draw with two cities
    City stadt1("Berlin", 100, 100);
    City stadt2("München", 200, 200);
 //draw the two cities
    stadt1.draw(*scene); // reference not pointer
    stadt2.draw(*scene);
}



void MainWindow::on_Buttonmap_clicked()
{
     p_map->draw(*scene);
}


void MainWindow::on_draw_city_clicked()
{
    City* stadt1 = new City("A", 100, 100); //City A
    City* stadt2 = new City("B", 300, 300); //City B

//add the cities to the map
    p_map->addCity(stadt1);
    p_map->addCity(stadt2);

    Street* strasse = new Street(stadt1, stadt2);
    p_map->addStreet(strasse); // will be added when the two cities are there

   // scene->clear();
    p_map->draw(*scene);
}

