#include "Figure.h"
#include <iostream>

Figure::Figure( vec3 * rotation, vec3 * scale, vec3 * translation, Point3d * couleur, bool inverseNormal, bool doubleSense ){
    this->setRotation( rotation );
    this->setScale( scale );
    this->setTranslation( translation );
    this->setCouleur( couleur );
    this->setInverseNormal( inverseNormal );
    this->setDoubleSense( doubleSense );
}
Figure::~Figure(){
    /*for( int i = 0; i < this->points.size(); i++ )
    {
        if( this->points[i] ) delete this->points[i];
    }*/
}

void Figure::setRotation(vec3 * rotation){
    this->rotation = rotation;
}
void Figure::setScale(vec3 * scale){
    this->scale = scale;
}
void Figure::setTranslation(vec3 * translation){
    this->translation = translation;
}
void Figure::setCouleur(Point3d * couleur){
    this->couleur = couleur;
}
void Figure::setInverseNormal(bool inverseNormal){
    this->inverseNormal = inverseNormal;
}
void Figure::setDoubleSense(bool doubleSense){
    this->doubleSense = doubleSense;
}

vec3 * Figure::getRotation(){
    return this->rotation;
}
vec3 * Figure::getScale(){
    return this->scale;
}
vec3 * Figure::getTranslation(){
    return this->translation;
}
Point3d * Figure::getCouleur(){
    return this->couleur;
}
bool Figure::getInverseNormal(){
    return this->inverseNormal;
}
bool Figure::getDoubleSense(){
    return this->doubleSense;
}

std::deque<Point3d*> Figure::getPoints()
{
    return this->points;
}
std::deque<Edge*> Figure::getEdges()
{
    return this->edges;
}
std::deque<FigureFace*> Figure::getFaces()
{
    return this->faces;
}

Edge * Figure::hasEdge( Point3d * pA, Point3d * pB ){
    for(int i=0; i<this->edges.size(); i++){
        if( this->edges[i]->hasPoints( pA, pB ) ){
            return this->edges[i];
        }
    }
    return NULL;
}
void Figure::setPoints(std::deque< Point3d* > points)
{
    this->points = points;
}
void Figure::setFaces( std::deque< FigureFace* > faces )
{
    this->faces = faces;

    // Calculate Edges
    for(int i=0; i<this->faces.size(); i++){
        std::deque<Point3d*> pointsFace = this->faces[i]->getPoints();
        for(int j=0; j<pointsFace.size(); j++){
            Point3d * p1 = pointsFace[j];
            Point3d * p2 = pointsFace[(j+1)%pointsFace.size()];

            Edge * existingEdge = this->hasEdge( p1, p2 );
            if( existingEdge == NULL ){
                existingEdge = new Edge( p1, p2, this->edges.size() );
                this->edges.push_back( existingEdge );
            }
            // Associate Edge to face
            existingEdge->associateTo( this->faces[i] );
            this->faces[i]->includeEdge( existingEdge );
        }
    }
}

void Figure::centralizeFigure()
{
    if( this->points.size() > 0 )
    {
        vec3 centreResult = this->points[0]->toVector();

        for(int i=1; i<this->points.size(); i++)
        {
            centreResult = centreResult.addition( this->points[i]->toVector() );
        }

        centreResult = centreResult.division( this->points.size() );

        for(int i=0; i<this->points.size(); i++)
        {
            vec3 centeredPoint = this->points[i]->toVector().soustraction( centreResult );
            this->points[i]->set( centeredPoint.getX(), centeredPoint.getY(), centeredPoint.getZ() );
        }
    }
}

vec3 positiveValues(vec3 v)
{
    if( v.getX() < 0 ) v.setX( v.getX()*-1. );
    if( v.getY() < 0 ) v.setY( v.getY()*-1. );
    if( v.getZ() < 0 ) v.setZ( v.getZ()*-1. );
    return v;
}

void Figure::normalizeFigure()
{
    // TODO must be centralized
    if( this->points.size() > 0 )
    {
        double normeResult = this->points[0]->toVector().norme();

        for(int i=1; i<this->points.size(); i++)
        {
            double normePoint = this->points[i]->toVector().norme();
            if( normePoint > normeResult ) normeResult = normePoint;
        }

        for(int i=0; i<this->points.size(); i++)
        {
            vec3 normalizedPoint = this->points[i]->toVector().division( normeResult );
            this->points[i]->set( normalizedPoint.getX(), normalizedPoint.getY(), normalizedPoint.getZ() );
        }
        /*vec3 maxResult = positiveValues( *this->points[0] );

        for(int i=1; i<this->points.size(); i++)
        {
            vec3 positive = positiveValues( *this->points[i] );
            if( positive.getX() > maxResult.getX() ) maxResult.setX( positive.getX() );
            if( positive.getY() > maxResult.getY() ) maxResult.setY( positive.getY() );
            if( positive.getZ() > maxResult.getZ() ) maxResult.setZ( positive.getZ() );
        }

        for(int i=0; i<this->points.size(); i++)
        {
            vec3 normalizedPoint = this->points[i]->division( maxResult );
            this->points[i]->set( normalizedPoint.getX(), normalizedPoint.getY(), normalizedPoint.getZ() );
        }*/
    }
}

void Figure::generatePointsAndFaces(){}
