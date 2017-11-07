#include "Square.h"
#include "../utils.h"

Square::Square( vec3 * center, double width, double height, point3d * couleur, bool inverseNormal, bool doubleSense )
: Figure::Figure(new vec3(0,0,0),new vec3(0,0,0),new vec3(0,0,0),couleur,inverseNormal,doubleSense)
{
    this->width = width;
    this->height = height;
    this->center = center;

    this->generatePointsAndFaces();
}

Square::Square( vec3 * rotation, vec3 * scale, vec3 * translation, point3d * couleur, bool inverseNormal, bool doubleSense )
: Square::Square(new vec3(0.,0.,0.),1.,1.,couleur,inverseNormal,doubleSense)
{
    this->rotation = rotation;
    this->scale = scale;
    this->translation = translation;
}

void Square::generatePointsAndFaces()
{
    // Points
    /*
    3 4
    1 2
    */
    this->points.push_back( new Point( new vec3( this->center->getX()-this->width/2.,this->center->getY()-this->height/2.,this->center->getZ()), 0 ));
    this->points.push_back( new Point( new vec3( this->center->getX()+this->width/2.,this->center->getY()-this->height/2.,this->center->getZ()), 1 ));
    this->points.push_back( new Point( new vec3( this->center->getX()-this->width/2.,this->center->getY()+this->height/2.,this->center->getZ()), 2 ));
    this->points.push_back( new Point( new vec3( this->center->getX()+this->width/2.,this->center->getY()+this->height/2.,this->center->getZ()), 3 ));
    // Faces
    std::deque<FigureFace*> f = FigureFace::SquareFigureFace( this->points[0], this->points[1], this->points[2], this->points[3], this->inverseNormal, this->doubleSense );
    this->faces.insert( this->faces.end(), f.begin(), f.end() );
}

Square::~Square()
{}
