#include "OffFile.h"

#include <iostream>
#include <fstream>
#include <deque>
#include "utils.h"
#include "vec3.h"
#include "figures/FigureFace.h"

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
	std::deque<Point*> points;
	std::deque<FigureFace*> faces;

	double x,y,z;
	int pPerFace, pIndex;
	FOR( i, nPoints )
	{
        reader >> x >> y >> z;
	    points.push_back( new Point(new vec3( x,y,z ), i) );
	}
	FOR( i, nFaces )
	{
	    reader >> pPerFace;
	    std::deque<Point*> pointsFace;

	    FOR(j,pPerFace)
	    {
            reader >> pIndex;
            pointsFace.push_back( points[ pIndex ] );
	    }

	    if( pPerFace >= 3 )
        {
            // Normal from the fist points
            vec3 normal = pointsFace[1]->getCoordinates()->soustraction( *pointsFace[0]->getCoordinates() ).produitVectoriel( pointsFace[2]->getCoordinates()->soustraction( *pointsFace[0]->getCoordinates() ) );
            faces.push_back( new FigureFace( pointsFace, normal ) );
        }
	}

	reader.close();

	Figure * resultat = new Figure( new vec3(0,0,0), new vec3(1,1,1), new vec3(0,0,0), new point3d(255,255,255,-1), false, false );
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
	    writer << f->getPoints()[i]->getCoordinates()->getX() << " " << f->getPoints()[i]->getCoordinates()->getY() << " " << f->getPoints()[i]->getCoordinates()->getZ() << std::endl;
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
	cout << "Edges: " << f->getFaces().size() << std::endl;
}
