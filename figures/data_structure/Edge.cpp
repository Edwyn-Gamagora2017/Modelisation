#include "Edge.h"

Edge::Edge( Point3d * _pointA, Point3d * _pointB, int _index ){
    this->pointA = _pointA;
    this->pointB = _pointB;
    this->index = _index;

    this->pointA->associateTo( this );
    this->pointB->associateTo( this );
}
Edge::~Edge(){}

bool Edge::hasPoint( Point3d * p ){
    if( p != NULL ){
        return (this->pointA->getIndex() == p->getIndex() || this->pointB->getIndex() == p->getIndex() );
    }
    return false;
}

/* GETTERS */
Point3d * Edge::getPointA(){
    return this->pointA;
}
Point3d * Edge::getPointB(){
    return this->pointB;
}
int Edge::getIndex(){
    return this->index;
}