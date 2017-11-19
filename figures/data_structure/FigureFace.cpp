#include "FigureFace.h"

#include <math.h>

FigureFace::FigureFace(std::deque<Point3d *> points, vec3 normal)
{
    this->points = points;
    this->normal = normal;
}

std::deque<Point3d*> FigureFace::getPoints()
{
    return this->points;
}

FigureFace::~FigureFace()
{

}

FigureFace* FigureFace::TriangleFigureFaceBasic(Point3d* pointA, Point3d* pointB, Point3d* pointC, bool inverseNormal)
{
    /*
    C
    | \
    A--B
    */
    std::deque<Point3d *> pointsT;
    pointsT.push_back( pointA );
    if( !inverseNormal )
        { pointsT.push_back( pointB ); pointsT.push_back( pointC ); }
    else
        { pointsT.push_back( pointC ); pointsT.push_back( pointB ); }
    pointsT.push_back( pointA );
    vec3 normalTriangle = pointB->vectorFrom(*pointA).produitVectoriel( pointC->vectorFrom(*pointA) ).normalized();

    return new FigureFace( pointsT, (inverseNormal?normalTriangle.negative():normalTriangle) );
}

std::deque<FigureFace*> FigureFace::TriangleFigureFace(Point3d* pointA, Point3d* pointB, Point3d* pointC, bool inverseNormal, bool doubleSense)
{
    std::deque<FigureFace*> result;
    result.push_back( FigureFace::TriangleFigureFaceBasic( pointA, pointB, pointC, inverseNormal ) );
    if(doubleSense) result.push_back( FigureFace::TriangleFigureFaceBasic( pointA, pointB, pointC, !inverseNormal ) );
    return result;
}

std::deque<FigureFace*> FigureFace::SquareFigureFace( Point3d * pointA, Point3d * pointB, Point3d * pointC, Point3d * pointD, bool inverseNormal, bool doubleSense )
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

std::deque<FigureFace*> FigureFace::SectionFigureFace( std::deque<Point3d*> pointsA, std::deque<Point3d*> pointsB, bool closed, bool inverseNormal, bool doubleSense )
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

std::deque<FigureFace*> FigureFace::CouvercleFigureFace( std::deque<Point3d*> points, bool inverseNormal, bool doubleSense, bool cutCenter )
{
    /*
         P2
         |
    P3 - C - P1
         |
         P4
    */
    std::deque<FigureFace*> result;
    // ATTENTION
    Point3d * centerPoint = points[ points.size() ];
    for( int i = 0; i < points.size()-(cutCenter?0:1); i++ )
    {
        std::deque<FigureFace*> t = TriangleFigureFace( centerPoint, points[i], points[(i+1)%points.size()], inverseNormal, doubleSense );
        result.insert( result.end(), t.begin(), t.end() );
    }
    return result;
}
