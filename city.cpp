#include "city.h"
#include <QGraphicsEllipseItem>   // for the red point
#include <QGraphicsTextItem>      // for the name
#include <QBrush>                 // for the inside
#include <QPen>                   // for borders

City::City(QString name, int x, int y): name(name), x(x), y(y) {}
void City::draw(QGraphicsScene& scene) const
{
    qDebug() << "Zeichne Stadt:" << name << "bei" << x << "," << y;


    // drawing point
    scene.addEllipse(x, y, 4, 4, QPen(Qt::red), QBrush(Qt::red, Qt::SolidPattern));

    //Show text
    QGraphicsTextItem* text = new QGraphicsTextItem;
    text->setPlainText(name);
    text->setPos(x, y - 20);
    scene.addItem(text);
}
