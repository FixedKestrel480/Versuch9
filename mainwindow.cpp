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
#include "streetdialog.h"


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
       // ui->Buttonmap->show();
        ui->draw_city->show();

    } else {
        ui->pushButton_testDrawCity->hide();
        ui->pushButton_addStadt->hide();
       // ui->Buttonmap->hide();
        ui->draw_city->hide();
    }
}


void MainWindow::on_pushButton_city_clicked()
{
    while(true)
    {
        //create window so user can give coordinated and city name
        CityDialog dialog(this);
        int result = dialog.exec();

        //qDebug() << "Dialog:" << result;
        // if ok
        if (result != QDialog::Accepted)
        {
            //if the user clicks canceled out of the function
            qDebug() << "Dialog canceled.";
            return;
        }
        // Uswe clicked Ok
        QString name = dialog.getCityName();
        int x = dialog.getX();
        int y = dialog.getY();
        // validate that the name is not empty
        if (name.trimmed().isEmpty())
        {
            QMessageBox::warning(this, "Fehler", "Bitte einen gültigen Namen eingeben!");
            continue; // show the dialog again
        }
        // validate that the coordinates are no negative
        if (x < 0 || y < 0)
        {
            QMessageBox::warning(this, "Fehler", "Bitte gültige Koordinaten eingeben!");
            continue;
        }

        //if everything is correct create and add it
        qDebug() << "Stadt erzeugen:" << name << "in" << x << "," << y;

        City* neueStadt = new City(name, x, y);
        p_map->addCity(neueStadt);
        neueStadt->draw(*scene);

        // Salir del bucle
        break;

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
        //const
        City *city = testMap.getOppositeCity(s, a);
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



void MainWindow::testDijkstra()
{

    // Create cities with specific coordinates
    City* ciudad1 = new City("C1", 0, 0);
    City* ciudad2 = new City("C2", 100, 100);
    City* ciudad3 = new City("C3", 200, 100);
    City* ciudad4 = new City("C4", 50, 0);
    City* ciudad5 = new City("C5", 150, 80);

    // Add to map
    p_map->addCity(ciudad1);
    p_map->addCity(ciudad2);
    p_map->addCity(ciudad3);
    p_map->addCity(ciudad4);
    p_map->addCity(ciudad5);

    // Conect cities with streets
    p_map->addStreet(new Street(ciudad1, ciudad2));
    p_map->addStreet(new Street(ciudad2, ciudad3));
    p_map->addStreet(new Street(ciudad2, ciudad4));
    p_map->addStreet(new Street(ciudad4, ciudad5));
    p_map->addStreet(new Street(ciudad5, ciudad3));
    p_map->addStreet(new Street(ciudad1, ciudad4));

    //Draw complete map
    p_map->draw(*scene);

    // Execute Dijikstra algorithm to find "C1" to "C3"
    QVector<Street*> resultado = Dijkstra::search(*p_map, "C1", "C3");

    // Validate if the path has not been found
    if (resultado.isEmpty())
    {
        qDebug() << "Path betwwen C1 and C3 has not been found verified that the two exist and are connected";
    }
    else
    {
        // Show the shortes path in console
        qDebug() << "shortest path found between C1 and C3:";
        for (int i = 0; i < resultado.size(); ++i)
        {
            Street* calle = resultado[i];
            qDebug() << calle->getStartCity()->getName() << " -> " << calle->getEndCity()->getName();
            // draw the street
            calle->drawRed(*scene);
        }
    }
}

void MainWindow::on_pushButton_TestDijikstra_clicked()
{
    testDijkstra();
}


void MainWindow::on_pushButton_Path_clicked()
{
    //creates dialog so user select cities of start and end
    PathDialog dialog(p_map->getCities(), this);
    int result = dialog.exec();

    // if ok
    if (result == QDialog::Accepted) {
        QString startName = dialog.getStartCity(); // obtain the city name of the city selected by the user
        QString endName = dialog.getEndCity(); //obtan city end name

        //verify that the two cities are different
        if (startName == endName) {
            QMessageBox::warning(this, "Fehler", "Start und Ziel dürfen nicht gleich sein!");
            return;
        }
//execute dijikstra to find shortest path
        QVector<Street*> weg = Dijkstra::search(*p_map, startName, endName);

        //verify if noth path has been encountered
        if (weg.isEmpty()) {
            QMessageBox::information(this, "Ergebnis", "Kein Weg gefunden!");
            return;
        }

        qDebug() << "Gefundener Weg:";
        for (const Street* s : weg) {
            qDebug() << "Von" << s->getStartCity()->getName()
            << " nach " << s->getEndCity()->getName();
        }

        scene->clear(); //clear scene
        p_map->draw(*scene); //draw all streets and cities

        //draw in red the shortes path
        for (const Street* s : weg) {
            s->drawRed(*scene);
        }
    }
}


void MainWindow::on_pushButton_clicked()
{
    if (p_map->getCities().size() < 2) {
        QMessageBox::warning(this, "Fehler", "Es müssen mindestens zwei Städte existieren!");
        return;
    }

    StreetDialog dialog(p_map->getCities(), this);
    int result = dialog.exec();

    if (result != QDialog::Accepted)
        return;

    QString startName = dialog.getStartCity();
    QString endName = dialog.getEndCity();

    if (startName == endName) {
        QMessageBox::warning(this, "Fehler", "Start und Ziel dürfen nicht gleich sein!");
        return;
    }

    City* startCity = p_map->findCity(startName);
    City* endCity = p_map->findCity(endName);

    if (!startCity || !endCity) {
        QMessageBox::warning(this, "Fehler", "Eine oder beide Städte wurden nicht gefunden!");
        return;
    }

    Street* street = new Street(startCity, endCity);
    bool success = p_map->addStreet(street);

    if (!success) {
        QMessageBox::information(this, "Info", "Straße konnte nicht hinzugefügt werden.");
        delete street; // no memory leak
        return;
    }

    // draw the scene
    p_map->draw(*scene);
}

