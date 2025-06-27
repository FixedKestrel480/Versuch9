#include "map.h"
#include <QDebug>

Map::Map() {}

void Map::addCity(City* stadt) {
    m_cities.append(stadt);
    //qDebug() << "Stadt hinzugefügt:" << stadt->name();
}


void Map::addStreet(Street* street) {
    // Check if both cities are already in the map
    if (!m_cities.contains(street->getStartCity()) ||
        !m_cities.contains(street->getEndCity())) {
        qDebug() << "Straße nicht hinzugefügt eine der Städte fehlt.";
        return;
    }
    m_streets.append(street);
    qDebug() << "Straße hinzugefügt.";
}

void Map::draw(QGraphicsScene& scene) {
    //for every city and street that has been added to the list draw it
    for (Street* s : m_streets)
        s->draw(scene);
    for (City* c : m_cities)
        c->draw(scene);
}
