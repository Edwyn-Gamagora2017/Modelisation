#include <string>

#include "vec3.h"

#pragma once
class point3d
{
	// coordonnees du point3d
	double x = 0;
	double y = 0;
	double z = 0;

public:
	point3d(double x, double y, double z);
	~point3d();

	static point3d * zero();

	double getX();
	double getY();
	double getZ();

	void set(double x, double y, double z);
	void setX(double x);
	void setY(double y);
	void setZ(double z);

	std::string toString();

	vec3 vectorFrom( point3d origin );
	vec3 toVector();
	static point3d fromVector(vec3 vect);
	point3d add( double x, double y, double z );
};

