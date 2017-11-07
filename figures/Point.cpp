#include "Point.h"

Point::Point( vec3 * coordinates, int index )
{
    this->coordinates = coordinates;
    this->index = index;
}
Point::~Point(){}

vec3 * Point::getCoordinates()
{
    return this->coordinates;
}
int Point::getIndex()
{
    return this->index;
}
void Point::setIndex( int index )
{
    this->index = index;
}
