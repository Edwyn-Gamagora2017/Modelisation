#include "FigureFace.h"

#include <math.h>

FigureFace::FigureFace(std::deque<Point *> points, vec3 normal)
{
    this->points = points;
    this->normal = normal;
}

std::deque<Point*> FigureFace::getPoints()
{
    return this->points;
}

FigureFace::~FigureFace()
{

}

FigureFace* FigureFace::TriangleFigureFaceBasic(Point* pointA, Point* pointB, Point* pointC, bool inverseNormal)
{
    /*
    C
    | \
    A--B
    */
    std::deque<Point *> pointsT;
    pointsT.push_back( pointA );
    if( !inverseNormal )
        { pointsT.push_back( pointB ); pointsT.push_back( pointC ); }
    else
        { pointsT.push_back( pointC ); pointsT.push_back( pointB ); }
    pointsT.push_back( pointA );
    vec3 normalTriangle = pointB->getCoordinates()->vectorFrom(*pointA->getCoordinates()).produitVectoriel( pointC->getCoordinates()->vectorFrom(*pointA->getCoordinates()) ).normalized();

    return new FigureFace( pointsT, (inverseNormal?normalTriangle.negative():normalTriangle) );
}

std::deque<FigureFace*> FigureFace::TriangleFigureFace(Point* pointA, Point* pointB, Point* pointC, bool inverseNormal, bool doubleSense)
{
    std::deque<FigureFace*> result;
    result.push_back( FigureFace::TriangleFigureFaceBasic( pointA, pointB, pointC, inverseNormal ) );
    if(doubleSense) result.push_back( FigureFace::TriangleFigureFaceBasic( pointA, pointB, pointC, !inverseNormal ) );
    return result;
}

std::deque<FigureFace*> FigureFace::SquareFigureFace( Point * pointA, Point * pointB, Point * pointC, Point * pointD, bool inverseNormal, bool doubleSense )
{
    /*
    C--D
    |  |
    A--B
    */
    std::deque<FigureFace*> result;
    std::deque<FigureFace*> t1 = TriangleFigureFace( pointA, pointB, pointC, inverseNormal, doubleSense );
    std::deque<FigureFace*> t2 = TriangleFigureFace( pointC, pointB, pointD, inverseNormal, doubleSense );
    result.insert( result.end(), t1.begin(), t1.end() );
    result.insert( result.end(), t2.begin(), t2.end() );
    return result;
}

std::deque<FigureFace*> FigureFace::SectionFigureFace( std::deque<Point*> pointsA, std::deque<Point*> pointsB, bool closed, bool inverseNormal, bool doubleSense )
{
    /*
    B1--B2
    |   |
    A1--A2
    */
    std::deque<FigureFace*> result;
    int amountPoints = std::min( pointsA.size(), pointsB.size() );
    for( int i = 0; i < amountPoints-(closed?0:1); i++ )
    {
        std::deque<FigureFace*> faces = SquareFigureFace( pointsA[i], pointsA[(i+1)%amountPoints], pointsB[i], pointsB[(i+1)%amountPoints], inverseNormal, doubleSense );
        result.insert( result.end(), faces.begin(), faces.end() );
    }
    return result;
}

std::deque<FigureFace*> FigureFace::CouvercleFigureFace( std::deque<Point*> points, bool inverseNormal, bool doubleSense, bool cutCenter )
{
    /*
         P2
         |
    P3 - C - P1
         |
         P4
    */
    std::deque<FigureFace*> result;
    Point * centerPoint = points[ points.size() ];
    for( int i = 0; i < points.size()-(cutCenter?0:1); i++ )
    {
        std::deque<FigureFace*> t = TriangleFigureFace( centerPoint, points[i], points[(i+1)%points.size()], inverseNormal, doubleSense );
        result.insert( result.end(), t.begin(), t.end() );
    }
    return result;
}
