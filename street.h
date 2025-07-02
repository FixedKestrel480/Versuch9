#ifndef STREET_H
#define STREET_H
#include "city.h"
#include <QGraphicsScene>
/**
 * @class Street
 * @brief Represents a street that connects two cities.
 */
class Street
{
public:
    /**
     * @brief Constructor.
     * @param start Pointer to the start city.
     * @param end Pointer to the end city.
     */
    Street(City* start, City* end);
    /**
     * @brief Draw the street as a black line between the two cities.
     * @param scene QGraphicsScene to draw on.
     */
    void draw(QGraphicsScene& scene) const;

    City* getStartCity() const;
    City* getEndCity() const;
    void drawRed(QGraphicsScene& scene) const;

private:
    City* startCity;
    City* endCity;
};

#endif // STREET_H
