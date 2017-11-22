#ifndef SURFACE_H
#define SURFACE_H

#include "data_structure/Figure.h"
#include "data_structure/Curve.h"
#include <deque>

class Surface :
    public Figure
{
    protected:
        std::deque< std::deque< Point3d > > controlPoints;
        int amountSamples;

    public:
        Surface( std::deque< std::deque< Point3d > > controlPoints, int amountSamples, Point3d * couleur, bool inverseNormal, bool doubleSense );
        ~Surface();

    protected:
        virtual void generatePointsAndFaces();
};

#endif // SURFACE_H
