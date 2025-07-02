#include "mainwindow.h"
#include "city.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "street.h"
#include <QDebug>
#include "citydialog.h"
#include "mapionrw.h"
#include "mapio.h"
#include "abstractmap.h"
#include "dijkstra.h"
#include "pathdialog.h"


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
    p_mapIo = new MapIoNrw(); //cambiar aqui el constructor
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


void MainWindow::on_Testknop_toggled(bool checked)
{
    if(checked){
        ui->pushButton_testDrawCity->show();
        ui->pushButton_addStadt->show();
        ui->Buttonmap->show();
        ui->draw_city->show();

    } else {
        ui->pushButton_testDrawCity->hide();
        ui->pushButton_addStadt->hide();
        ui->Buttonmap->hide();
        ui->draw_city->hide();
    }
}


void MainWindow::on_pushButton_city_clicked()
{
    CityDialog dialog(this);
    int result = dialog.exec();

    qDebug() << "Dialog:" << result;

    if (result == QDialog::Accepted) {
        // Uswe clicked Ok
        QString name = dialog.getCityName();
        int x = dialog.getX();
        int y = dialog.getY();

        qDebug() << "Stadt erzeugen:" << name << "in" << x << "," << y;

        City* neueStadt = new City(name, x, y);
        p_map->addCity(neueStadt);
        neueStadt->draw(*scene);
    } else {
        qDebug() << "Dialog canceled.";
    }

}


void MainWindow::on_pushButton_fill_map_clicked()
{
    p_mapIo->fillMap(*p_map); //fill map instance using p_mapIo
    scene->clear();// clear scene
    p_map->draw(*scene); // draw everything that contains p_map
}


void MainWindow::on_pushButton_testAbstract_clicked()
{
    testAbstractMap();
}

/*
 * In dieser Datei finden Sie einige Beispiele für Funktions-Tests,
 * die im Versuch "GUI-Programmierung mit Qt" benötigt werden.
 */

/**
// Einlesen der Benutzereingaben und Ausgabe auf der Konsole
testSimpleUi()
    QString pattern = "The user's input: %1";
QString s = pattern.arg(ui->lineEdit->text());
qDebug() << s;


// In der GUI zeichnen
testSimpleDrawing()
    scene.addRect(50, 20, 50, 100);


// Eine Stadt anlegen und zeichnen
testDrawCities()
    City c1("city c1", 20,50);
c1.draw(scene);

// Hinzufügen von Städten zu einer Karte und Zeichnen der Städte über die Karte
testDrawMapWithCities()
    City c1("city c1", 20,50);
map.addCity(&c1);
map.draw(scene);

testDrawStreets()
    testDrawMapWithStreets()
    testRejectStreet()

    // Einen Dialog anzeigen
    testShowDialog()
    DialogAddCity dialog;
int result = dialog.exec();
qDebug() << QString("Dialog result: %1").arg(result);**/

// Diese Funktion testet, ob die Klasse Map das Interface "AbstractMap" korrekt implementiert.
void MainWindow::testAbstractMap()
{
    Map testMap;
    City *a = new City("a", 0, 0);
    City *b = new City("b", 0, 100);
    City *c = new City("c", 100, 300);
    Street *s = new Street(a, b);
    Street *s2 = new Street(b, c);


    qDebug() << "MapTest: Start Test of the Map";
    {
        qDebug() << "MapTest: adding wrong street";
        bool t1 = testMap.addStreet(s);
        if (t1) {
            qDebug() << "-Error: Street should not bee added, if cities have not been added.";
        }
    }

    {
        qDebug() << "MapTest: adding correct street";
        testMap.addCity(a);
        testMap.addCity(b);
        bool t1 = testMap.addStreet(s);
        if (!t1) {
            qDebug() << "-Error: It should be possible to add this street.";
        }
    }

    {
        qDebug() << "MapTest: findCity";
        City* city = testMap.findCity("a");
        if (city != a)
            qDebug() << "-Error: City a could not be found.";

        city = testMap.findCity("b");
        if (city != b)
            qDebug() << "-Error: City b could not be found.";

        city = testMap.findCity("c");
        if (city != nullptr)
            qDebug() << "-Error: If city could not be found 0 should be returned.";
    }

    testMap.addCity(c);
    testMap.addStreet(s2);

    {
        qDebug() << "MapTest: getOppositeCity";
        const City *city = testMap.getOppositeCity(s, a);
        if (city != b)
            qDebug() << "-Error: Opposite city should be b.";

        city = testMap.getOppositeCity(s, c);
        if (city != nullptr)
            qDebug() << "-Error: Opposite city for a city which is not linked by given street should be 0.";
    }

    {
        qDebug() << "MapTest: streetLength";
        double l = testMap.getLength(s2);
        double expectedLength = 223.6;
        // compare doubles with 5% tolerance
        if (l < expectedLength * 0.95 || l > expectedLength *1.05)
            qDebug() << "-Error: Street Length is not equal to the expected.";

    }

    {
        qDebug() << "MapTest: getStreetList";
        QVector<Street*> streetList1 = testMap.getStreetList(a);
        QVector<Street*> streetList2 = testMap.getStreetList(b);
        if (streetList1.size() != 1) {
            qDebug() << "-Error: One street should be found for city a.";
        }
        else if (*streetList1.begin() != s) {
            qDebug() << "-Error: The wrong street has been found for city a.";
        }

        if (streetList2.size() != 2)
            qDebug() << "-Error: Two streets should be found for city b.";
    }

    qDebug() << "MapTest: End Test of the Map.";
}



void MainWindow::on_pushButton_TestDijikstra_clicked()
{
    // Zwei Teststädte (z.B. "A" und "C") suchen
    const City* startCity = p_map->findCity("A");
    const City* endCity = p_map->findCity("C");

    if (!startCity || !endCity) {
        qDebug() << "Eine oder beide Städte wurden nicht gefunden!";
        return;
    }

    QString startName = startCity->getName();
    QString endName   = endCity  ->getName();
    QVector<Street*> weg = Dijkstra::search(*p_map, startName, endName);

    qDebug() << "Gefundener Weg:";
    for (const Street* s : weg) {
        qDebug() << "Von" << s->getStartCity()->getName() << "nach" << s->getEndCity()->getName();
    }

    // Szene leeren und alles normal zeichnen
    scene->clear();
    p_map->draw(*scene);

    // Alle Straßen des Weges rot und breit zeichnen
    for (const Street* s : weg) {
        const_cast<Street*>(s)->drawRed(*scene);
    }
}


void MainWindow::on_pushButton_Path_clicked()
{
    PathDialog dialog(p_map->getCities(), this);
    int result = dialog.exec();

    if (result == QDialog::Accepted) {
        QString startName = dialog.getStartCity();
        QString endName = dialog.getEndCity();

        if (startName == endName) {
            QMessageBox::warning(this, "Fehler", "Start und Ziel dürfen nicht gleich sein!");
            return;
        }

        QVector<Street*> weg = Dijkstra::search(*p_map, startName, endName);

        if (weg.isEmpty()) {
            QMessageBox::information(this, "Ergebnis", "Kein Weg gefunden!");
            return;
        }

        qDebug() << "Gefundener Weg:";
        for (const Street* s : weg) {
            qDebug() << "Von" << s->getStartCity()->getName()
            << " nach " << s->getEndCity()->getName();
        }

        scene->clear();
        p_map->draw(*scene);

        for (const Street* s : weg) {
            s->drawRed(*scene);
        }
    }
}

