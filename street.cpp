#include "street.h"

Street::Street(City* start, City* end) : startCity(start), endCity(end){} //constructor

void Street::draw(QGraphicsScene& scene) const {
    //draw two  lines between the cities
    scene.addLine(startCity->getX(), startCity->getY(),
                  endCity->getX(), endCity->getY(),
                  QPen(Qt::black, 2));
}

City* Street::getStartCity() const {
    return startCity;
}

City* Street::getEndCity() const {
    return endCity;
}
void Street::drawRed(QGraphicsScene& scene) const
{
    QPen pen(Qt::red);
    pen.setWidth(4);
    scene.addLine(getStartCity()->getX(), getStartCity()->getY(),
                  getEndCity()->getX(), getEndCity()->getY(),
                  pen);
}
