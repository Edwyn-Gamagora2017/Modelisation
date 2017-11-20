#ifndef FIGURE_H
#define FIGURE_H

#include "vec3.h"
#include "Point3d.h"
#include "Edge.h"
#include "FigureFace.h"
#include <deque>

#pragma once
class Figure
{
protected:
	vec3 * rotation;
	vec3 * scale;
	vec3 * translation;
	Point3d * couleur;
    std::deque< Point3d * > points;
    std::deque< Edge * > edges;
    std::deque< FigureFace * > faces;
    bool inverseNormal;
    bool doubleSense;

public:
	Figure( vec3 * rotation, vec3 * scale, vec3 * translation, Point3d * couleur, bool inverseNormal, bool doubleSense );
	~Figure();

	vec3 * getRotation();
	vec3 * getScale();
	vec3 * getTranslation();
	Point3d * getCouleur();
	bool getInverseNormal();
	bool getDoubleSense();

	std::deque< Point3d* > getPoints();
	std::deque< Edge* > getEdges();
	std::deque< FigureFace* > getFaces();
	void setPoints(std::deque< Point3d* > points);
	void setFaces( std::deque< FigureFace* > faces );

    void centralizeFigure();
    void normalizeFigure();

protected:
    void setRotation(vec3 * rotation);
	void setScale(vec3 * scale);
	void setTranslation(vec3 * translation);
	void setCouleur(Point3d * couleur);
	void setInverseNormal(bool inverseNormal);
	void setDoubleSense(bool doubleSense);

	Edge* hasEdge( Point3d * pA, Point3d * pB );

	virtual void generatePointsAndFaces();
};

#endif // FIGURE_H
