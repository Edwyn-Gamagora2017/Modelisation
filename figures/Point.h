#ifndef POINT_H
#define POINT_H

#include "../vec3.h"

class Point
{
    protected:
        vec3 * coordinates;
        int index;
    public:
        Point( vec3 * coordinates, int index );
        virtual ~Point();

        vec3 * getCoordinates();
        int getIndex();
        void setIndex( int index );
};

#endif // POINT_H
