#include <string>

#include "vec3.h"

#pragma once
class Point3d
{
	// coordonnees du point3d
	double x = 0;
	double y = 0;
	double z = 0;
	// identifiant du point
	int index;

public:
	Point3d(double x, double y, double z, int index);
	~Point3d();

	static Point3d * zero(int index);

	double getX();
	double getY();
	double getZ();
	int getIndex();

	void set(double x, double y, double z);
	void setX(double x);
	void setY(double y);
	void setZ(double z);

	std::string toString();

	vec3 vectorFrom( Point3d origin );
	vec3 toVector();
	static Point3d fromVector(vec3 vect, int index);

	// Color
	Point3d add( double x, double y, double z );
};
