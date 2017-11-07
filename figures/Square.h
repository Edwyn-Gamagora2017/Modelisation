#ifndef SQUARE_H
#define SQUARE_H

#pragma once
#include "Figure.h"

class Square
: public Figure
{
    protected:
        vec3 * center;
        double width;
        double height;

    public:
        Square( vec3 * center, double width, double height, point3d * couleur, bool inverseNormal, bool doubleSense );
        Square( vec3 * rotation, vec3 * scale, vec3 * translation, point3d * couleur, bool inverseNormal, bool doubleSense );
        ~Square();

    protected:
        virtual void generatePointsAndFaces();
};
#endif // SQUARE_H
