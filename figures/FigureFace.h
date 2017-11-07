#ifndef FIGUREFACE_H
#define FIGUREFACE_H

#include <deque>
#include "Point.h"

class FigureFace
{
    std::deque<Point *> points;
    vec3 normal;

    public:
        FigureFace( std::deque<Point *> points, vec3 normal );
        virtual ~FigureFace();

        static std::deque<FigureFace *> TriangleFigureFace( Point * pointA, Point * pointB, Point * pointC, bool inverseNormal, bool doubleSense );
        static std::deque<FigureFace *> SquareFigureFace( Point * pointA, Point * pointB, Point * pointC, Point * pointD, bool inverseNormal, bool doubleSense );
        static std::deque<FigureFace *> SectionFigureFace( std::deque<Point*> pointsA, std::deque<Point*> pointsB, bool closed, bool inverseNormal, bool doubleSense );
        static std::deque<FigureFace *> CouvercleFigureFace( std::deque<Point*> points, bool inverseNormal, bool doubleSense, bool cutCenter );  // the center is the last element in the list

        std::deque<Point *> getPoints();

    private:
        static FigureFace * TriangleFigureFaceBasic( Point * pointA, Point * pointB, Point * pointC, bool inverseNormal );
};

#endif // FIGUREFACE_H
