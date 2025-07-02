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
    bool addStreet(Street* street) override;
    City* findCity(const QString cityName) const override;
    QVector<Street*> getStreetList(const City* city) const override;
    City* getOppositeCity(const Street* street, const City* city) const override;
    double getLength(const Street* street) const override;

    QVector<City*> getCities() const override {
        return m_cities;
    }

private:
    QVector<City*> m_cities; // list city pointers at the map
    QVector<Street*> m_streets; //list street pointers at map
};

#endif // MAP_H
