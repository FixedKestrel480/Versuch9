#include "map.h"
#include <QDebug>

Map::Map() {}

void Map::addCity(City* stadt) {
    m_cities.append(stadt);
    //qDebug() << "Stadt hinzugefügt:" << stadt->name();
}


bool Map::addStreet(Street* street) {
    // Check if both cities are already in the map
    if (!m_cities.contains(street->getStartCity()) ||
        !m_cities.contains(street->getEndCity())) {
        qDebug() << "Straße nicht hinzugefügt eine der Städte fehlt.";
        return false;
    }
    m_streets.append(street);
    qDebug() << "Straße hinzugefügt.";
    return true;
}

void Map::draw(QGraphicsScene& scene) {
    //for every city and street that has been added to the list draw it
    for (Street* s : m_streets)
        s->draw(scene);
    for (City* c : m_cities)
        c->draw(scene);
}

City* Map::findCity(const QString cityName) const {
    for (City* c : m_cities)
        if (c->getName() == cityName)
            return c;
    return nullptr;
}

QVector<Street*> Map::getStreetList(const City* city) const {
    QVector<Street*> list;
    for (Street* s : m_streets) {
        if (s->getStartCity() == city || s->getEndCity() == city)
            list.append(s);
    }
    return list;
}

City* Map::getOppositeCity(const Street* street, const City* city) const {
    if (street->getStartCity() == city)
        return street->getEndCity();
    if (street->getEndCity() == city)
        return street->getStartCity();
    return nullptr;
}

double Map::getLength(const Street* street) const {
    int dx = street->getEndCity()->getX() - street->getStartCity()->getX();
    int dy = street->getEndCity()->getY() - street->getStartCity()->getY();
    return std::sqrt(dx*dx + dy*dy);
}

