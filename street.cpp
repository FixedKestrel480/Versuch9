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
