#include "point3d.h"
#include "../utils.h"

point3d::point3d(double x, double y, double z, int index) {
	this->set(x, y, z);
	this->index = index;
}

point3d::~point3d() {
}

point3d * point3d::zero(int index) {
	return new point3d(0, 0, 0, index);
}

double point3d::getX() {
	return this->x;
}
double point3d::getY() {
	return this->y;
}
double point3d::getZ() {
	return this->z;
}
int point3d::getIndex(){
    return this->index;
}

void point3d::set(double x, double y, double z) {
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}
void point3d::setX(double x) {
	this->x = x;
}
void point3d::setY(double y) {
	this->y = y;
}
void point3d::setZ(double z) {
	this->z = z;
}

std::string point3d::toString() {
	return "( " + doubleToStr(this->getX()) + " , " + doubleToStr(this->getY()) + " , " + doubleToStr(this->getZ()) + " )";
}

vec3 point3d::vectorFrom( point3d origin )
{
    return vec3( this->getX(), this->getY(), this->getZ() ).soustraction(vec3( origin.getX(), origin.getY(), origin.getZ() ));
}
vec3 point3d::toVector()
{
    return this->vectorFrom( point3d(0,0,0,this->index) );
}
point3d point3d::fromVector(vec3 vect, int index)
{
    return point3d( vect.getX(), vect.getY(), vect.getZ(), index );
}
point3d point3d::add( double x, double y, double z )
{
    return point3d( this->getX()+x, this->getY()+y, this->getZ()+z, this->index );
}
