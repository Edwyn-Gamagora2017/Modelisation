#include "Surface.h"

#include <iostream>

Surface::Surface( std::deque< std::deque< Point3d > > controlPoints, int amountSamples, Point3d * couleur, bool inverseNormal, bool doubleSense )
: Figure::Figure(new vec3(0,0,0),new vec3(0,0,0),new vec3(0,0,0),couleur,inverseNormal,doubleSense)
{
    this->controlPoints = controlPoints;
    this->amountSamples = amountSamples;

    this->surfaceControl = new SurfaceControl( controlPoints, couleur, inverseNormal, doubleSense );

    this->generatePointsAndFaces();
}
Surface::~Surface(){
    delete( this->surfaceControl );
}

SurfaceControl * Surface::getSurfaceControl(){
    return this->surfaceControl;
}

void Surface::generatePointsAndFaces(){
    // points created by Casteljau's curve
    for( int i=0; i<this->controlPoints.size(); i++ ){
        int initialIndex = this->points.size();
        std::deque< vec3 > curve = Curve::casteljau( this->controlPoints[i], this->amountSamples );
        for( int j = 0; j < curve.size(); j++ ){
            this->points.push_back( new Point3d( curve[j].getX(), curve[j].getY(), curve[j].getZ(), initialIndex+j ) );
        }
    }

    // Faces
    for( int i=0; i<this->controlPoints.size()-1; i++ ){
        int nPointsPerCurve = this->amountSamples+2;
        int indexStartSup = i*nPointsPerCurve;
        int indexStartInf = (i+1)*nPointsPerCurve;
        int indexEndSup = indexStartInf;
        int indexEndInf = (i+2)*nPointsPerCurve;

        std::deque<Point3d*> pSup, pInf;
        pSup.insert( pSup.end(), this->points.begin()+indexStartSup, this->points.begin()+indexEndSup );
        pInf.insert( pInf.end(), this->points.begin()+indexStartInf, this->points.begin()+indexEndInf );

        std::deque<FigureFace*> fSection = FigureFace::SectionFigureFace( pSup, pInf, false, this->inverseNormal, this->doubleSense );
        this->faces.insert( this->faces.end(), fSection.begin(), fSection.end() );
    }

    // TODO SetFaces to generate Edges
    this->centralizeFigure();
	this->normalizeFigure();
}

Surface * Surface::example(){
    std::deque< std::deque< Point3d > > controlPoints;
    std::deque< Point3d > controlPointsCurve;

    controlPointsCurve.push_back( Point3d( 0,0,0, 0 ) );
    controlPointsCurve.push_back( Point3d( 0,1,0, 0 ) );
    controlPointsCurve.push_back( Point3d( 0,2,0, 0 ) );
    controlPoints.push_back( controlPointsCurve );

    controlPointsCurve.clear();
    controlPointsCurve.push_back( Point3d( 1,0,0, 0 ) );
    controlPointsCurve.push_back( Point3d( 1,1,1, 0 ) );
    controlPointsCurve.push_back( Point3d( 1,2,1, 0 ) );
    controlPoints.push_back( controlPointsCurve );

    controlPointsCurve.clear();
    controlPointsCurve.push_back( Point3d( 2,0,0, 0 ) );
    controlPointsCurve.push_back( Point3d( 2,1,1, 0 ) );
    controlPointsCurve.push_back( Point3d( 2,2,1, 0 ) );
    controlPoints.push_back( controlPointsCurve );

    controlPointsCurve.clear();
    controlPointsCurve.push_back( Point3d( 3,0,0, 0 ) );
    controlPointsCurve.push_back( Point3d( 3,1,0, 0 ) );
    controlPointsCurve.push_back( Point3d( 3,2,0, 0 ) );
    controlPoints.push_back( controlPointsCurve );

    return new Surface( controlPoints, 5, new Point3d(1,1,0, 0), false, true );
}
