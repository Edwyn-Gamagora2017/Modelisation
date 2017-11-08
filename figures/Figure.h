#ifndef FIGURE_H
#define FIGURE_H

#include "vec3.h"
#include "point3d.h"
#include "FigureFace.h"
#include "Point.h"
#include <deque>

#pragma once
class Figure
{
protected:
	vec3 * rotation;
	vec3 * scale;
	vec3 * translation;
	point3d * couleur;
    std::deque< point3d * > points;
    std::deque< FigureFace * > faces;
    bool inverseNormal;
    bool doubleSense;

public:
	Figure( vec3 * rotation, vec3 * scale, vec3 * translation, point3d * couleur, bool inverseNormal, bool doubleSense );
	~Figure();

	vec3 * getRotation();
	vec3 * getScale();
	vec3 * getTranslation();
	point3d * getCouleur();
	bool getInverseNormal();
	bool getDoubleSense();

	std::deque< point3d* > getPoints();
	std::deque< FigureFace* > getFaces();
	void setPoints(std::deque< point3d* > points);
	void setFaces( std::deque< FigureFace* > faces );

    void centralizeFigure();
    void normalizeFigure();

protected:
    void setRotation(vec3 * rotation);
	void setScale(vec3 * scale);
	void setTranslation(vec3 * translation);
	void setCouleur(point3d * couleur);
	void setInverseNormal(bool inverseNormal);
	void setDoubleSense(bool doubleSense);

	virtual void generatePointsAndFaces();
};

#endif // FIGURE_H
