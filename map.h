#ifndef MAP_H
#define MAP_H
#include <QVector>
#include "city.h"
#include "abstractmap.h"
#include "street.h"
/**
 * @class Map
 * @brief stores and draws cities and streets.
 */
class Map : public AbstractMap
{
public:
    Map();
    /**
     * @brief Add a city to the map.
     * @param stadt Pointer to the City to add.
     */
    void addCity(City* stadt) override;
    /**
     * @brief Draw all cities and streets in the map.
     * @param scene QGraphicsScene to draw on.
     */
    void draw(QGraphicsScene& scene);
    /**
     * @brief Add a street to the map.
     * @param street Pointer to the Street to add.
     */
    void addStreet(Street* street) override;
private:
    QVector<City*> m_cities; // list city pointers at the map
    QVector<Street*> m_streets; //list street pointers at map
};

#endif // MAP_H
