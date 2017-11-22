#include "Surface.h"

Surface::Surface( std::deque< std::deque< Point3d > > controlPoints, int amountSamples, Point3d * couleur, bool inverseNormal, bool doubleSense )
: Figure::Figure(new vec3(0,0,0),new vec3(0,0,0),new vec3(0,0,0),couleur,inverseNormal,doubleSense)
{
    this->controlPoints = controlPoints;
    this->amountSamples = amountSamples;

    this->generatePointsAndFaces();
}
Surface::~Surface(){}

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
        int indexEndSup = indexStartInf-1;
        int indexEndInf = (i+2)*nPointsPerCurve-1;
        std::deque<Point3d*> pSup, pInf;
        pSup.insert( pSup.end(), this->points.begin()+indexStartSup, this->points.begin()+indexEndSup );
        pInf.insert( pInf.end(), this->points.begin()+indexStartInf, this->points.begin()+indexEndInf );

        std::deque<FigureFace*> fSection = FigureFace::SectionFigureFace( pSup, pInf, false, this->inverseNormal, this->doubleSense );
        this->faces.insert( this->faces.end(), fSection.begin(), fSection.end() );
    }
}
