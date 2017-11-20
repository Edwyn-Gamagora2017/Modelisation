#include "OffFile.h"

#include <iostream>
#include <fstream>
#include <deque>
#include "utils.h"
#include "../figures/data_structure/vec3.h"
#include "../figures/data_structure/FigureFace.h"

Figure * OffFile::readFile( string filename )
{
    std::ifstream reader;
	reader.open( string(filename+".off").c_str() );
	if( !reader.is_open() ){ PRINT("FILE ERROR"); reader.close(); return NULL; }

	string type;
	reader >> type;
	if( type != "OFF" ){ reader.close(); return NULL; }

	int nPoints, nFaces, nEdges;
	reader >> nPoints >> nFaces >> nEdges;
	std::deque<Point3d*> points;
	std::deque<FigureFace*> faces;

	double x,y,z;
	int pPerFace, pIndex;
	FOR( i, nPoints )
	{
        reader >> x >> y >> z;
	    points.push_back( new Point3d(x,y,z, i) );
	}
	FOR( i, nFaces )
	{
	    reader >> pPerFace;
	    std::deque<Point3d*> pointsFace;

	    FOR(j,pPerFace)
	    {
            reader >> pIndex;
            pointsFace.push_back( points[ pIndex ] );
	    }

	    if( pPerFace >= 3 )
        {
            // Normal from the fist points
            vec3 normal = pointsFace[1]->toVector().soustraction( pointsFace[0]->toVector() ).produitVectoriel( pointsFace[2]->toVector().soustraction( pointsFace[0]->toVector() ) );
            faces.push_back( new FigureFace( pointsFace, normal, i ) );
        }
	}

	reader.close();

	Figure * resultat = new Figure( new vec3(0,0,0), new vec3(1,1,1), new vec3(0,0,0), new Point3d(255,255,255,-1), false, false );
	resultat->setPoints( points );
	resultat->setFaces( faces );

	resultat->centralizeFigure();
	resultat->normalizeFigure();

	return resultat;
}

void OffFile::writeFile( Figure * f, string filename )
{
    std::ofstream writer;
	writer.open( string(filename+".off").c_str() );
	if( !writer.is_open() ){ PRINT("FILE ERROR"); writer.close(); return; }

	writer << "OFF" << std::endl;
	writer << f->getPoints().size() << " " << f->getFaces().size() << " " << 0 << std::endl;

	FOR(i,f->getPoints().size())
	{
	    writer << f->getPoints()[i]->getX() << " " << f->getPoints()[i]->getY() << " " << f->getPoints()[i]->getZ() << std::endl;
	}
	FOR(i,f->getFaces().size())
	{
	    writer << f->getFaces()[i]->getPoints().size() << " ";
	    FOR(j,f->getFaces()[i]->getPoints().size())
	    {
	        writer << f->getFaces()[i]->getPoints()[j]->getIndex() << " ";
	    }
	    writer << std::endl;
	}

	writer.close();
}

void OffFile::printInfo( Figure * f )
{
	cout << "Vertices: " << f->getPoints().size() << std::endl;
	cout << "Edges: " << f->getEdges().size() << std::endl;
	cout << "Faces: " << f->getFaces().size() << std::endl;
}
