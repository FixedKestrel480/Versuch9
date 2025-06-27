#ifndef CITY_H
#define CITY_H
#include <QString>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>

/**
 * @class City
 * @brief Represents a city with a name and coordinates.
 */
class City
{
public:
    /**
     * @brief Constructor.
     * @param name Name of the city.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    City(QString name, int x, int y);
    /**
     * @brief Draws the city on the given QGraphicsScene.
     * @param scene Reference to the graphics scene.
     */
    void draw(QGraphicsScene& scene) const;
    int getX() const { return x; }
    int getY() const { return y; }
    QString getName() const { return name;}

private:
    QString name; //name of the city
    int x;//x coordinate
    int y; //y coordinate
    static const int size = 30;
};

#endif // CITY_H
