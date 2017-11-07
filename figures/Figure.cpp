#include "Figure.h"

Figure::Figure( vec3 * rotation, vec3 * scale, vec3 * translation, point3d * couleur, bool inverseNormal, bool doubleSense ){
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
void Figure::setCouleur(point3d * couleur){
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
point3d * Figure::getCouleur(){
    return this->couleur;
}
bool Figure::getInverseNormal(){
    return this->inverseNormal;
}
bool Figure::getDoubleSense(){
    return this->doubleSense;
}

std::deque<Point*> Figure::getPoints()
{
    return this->points;
}
std::deque<FigureFace*> Figure::getFaces()
{
    return this->faces;
}
void Figure::setPoints(std::deque< Point* > points)
{
    this->points = points;
}
void Figure::setFaces( std::deque< FigureFace* > faces )
{
    this->faces = faces;
}

void Figure::centralizeFigure()
{
    if( this->points.size() > 0 )
    {
        vec3 centreResult = *this->points[0]->getCoordinates();

        for(int i=1; i<this->points.size(); i++)
        {
            centreResult = centreResult.addition( *this->points[i]->getCoordinates() );
        }

        centreResult = centreResult.division( this->points.size() );

        for(int i=0; i<this->points.size(); i++)
        {
            vec3 centeredPoint = this->points[i]->getCoordinates()->soustraction( centreResult );
            this->points[i]->getCoordinates()->set( centeredPoint.getX(), centeredPoint.getY(), centeredPoint.getZ() );
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
        double normeResult = this->points[0]->getCoordinates()->norme();

        for(int i=1; i<this->points.size(); i++)
        {
            double normePoint = this->points[i]->getCoordinates()->norme();
            if( normePoint > normeResult ) normeResult = normePoint;
        }

        for(int i=0; i<this->points.size(); i++)
        {
            vec3 normalizedPoint = this->points[i]->getCoordinates()->division( normeResult );
            this->points[i]->getCoordinates()->set( normalizedPoint.getX(), normalizedPoint.getY(), normalizedPoint.getZ() );
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
