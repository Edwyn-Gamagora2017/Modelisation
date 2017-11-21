// 01triangle.cpp : Définit le point d'entrée pour l'application console.
//
#include <windows.h>

#include <string>
#include <iostream>

#include "figures/data_structure/vec3.h"
#include "figures/data_structure/Point3d.h"
#include "figures/data_structure/Figure.h"
#include "utils/utils.h"
#include "utils/OffFile.h"

#include "figures/Square.h"

#include "GL\glut.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>
//#include "struct.h"

/* au cas ou M_PI ne soit defini */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

#define WIDTH  600
#define HEIGHT 600

#define KEY_ESC 27

float angleX=0.0f; //angle de rotation en Y de la scene
float angleY=0.0f; //angle de rotation en X de la scene

float pasDeplacement=1.25;


//position lumiere
float xLitePos=0;
float yLitePos=10;
float zLitePos=-100;

float tx=0.0;
float ty=0.0;
float tz=0.0;

vec3 lightPosition( 2, 0, 0 );

void drawFigureFaces( Figure * f, GLenum mode, Point3d * couleur = new Point3d(0,0,0,-1) ){
	std::deque<FigureFace*> faces = f->getFaces();
	vec3 * scale = f->getScale();
    vec3 * translation = f->getTranslation();

    for(int i=0; i<faces.size(); i++)
    {
        glPushMatrix();
        //glBegin(GL_LINE_LOOP);
        //glBegin(GL_TRIANGLES);
        //glBegin(GL_POINTS);
        //glBegin(GL_POLYGON);
        glBegin(mode);

        for(int j=0; j< faces[i]->getPoints().size(); j++)
        {
            Point3d * p = faces[i]->getPoints()[j];

            // Color based on light
            float lightFactor = lightPosition.soustraction( p->toVector() ).normalized().produitScalaire( faces[i]->getNormal().normalized() );
            if( lightFactor < 0.1f ){
                // simulating environment light
                lightFactor = 0.1f;
            }
            glColor3f(lightFactor*couleur->getX(), lightFactor*couleur->getY(), lightFactor*couleur->getZ());

            glVertex3f(
              /*(p->getX()*scale->getX())+translation->getX(),
              (p->getY()*scale->getY())+translation->getY(),
              (p->getZ()*scale->getZ())+translation->getZ()*/
                p->getX(), p->getY(), p->getZ()
            );
        }
        // Closing figure
        Point3d * p = faces[i]->getPoints()[0];
        glVertex3f(p->getX(), p->getY(), p->getZ());

        glEnd();
        glPopMatrix();
    }
}

vec3 * origin = new vec3(0,0,0);
double width = 15.;
double height = 10.;
int nMeridiens = 20;
int nParallels = 15;
bool isTube = false;
bool normalInverse = false;
bool doubleSense = false;
int selectedFigure = 0;

Point3d * color_white   = new Point3d(1,1,1,-1);
Point3d * color_yellow  = new Point3d(1,1,0,-1);
Point3d * color_red     = new Point3d(1,0,0,-1);
Point3d * color_black   = new Point3d(0,0,0,-1);

Figure * f;

void createFigure()
{
    if( f != NULL ) delete f;

    switch( selectedFigure )
    {
        case 0: f    = OffFile::readFile( "maillages/triceratops" ); break;
//        case 0: f    = new Square(new vec3(),1,1,color_red,false,false); break;
        case 1: f    = OffFile::readFile( "maillages/max" ); break;
        case 2: f    = OffFile::readFile( "maillages/buddha" ); break;
        case 3: f    = OffFile::readFile( "maillages/bunny" ); break;
        case 4: default: f    = OffFile::readFile( "maillages/test" ); break;
    }

    f->printInfo();
}

/* initialisation d'OpenGL*/
static void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	// Si vous avez des choses à initialiser, c est ici.
	createFigure();
}

/* Dessin */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //effacement du buffer

	//Description de la scene
	glLoadIdentity();
	//rotation de la scene suivant les mouvements de la souris
	glRotatef(-angleY,0.0f,0.0f,1.0f);
	glRotatef(angleX,0.0f,1.0f,0.0f);
	glTranslatef(tx,ty,tz);

	glRotatef(-angleY,0.0f,0.0f,1.0f);
	glRotatef(angleX,0.0f,1.0f,0.0f);

	/****** Drawing ********/
	drawFigureFaces( f, GL_TRIANGLES, f->getCouleur() );
    drawFigureFaces( f, GL_LINE_STRIP, color_black );

	//affiche les axes du repere
		glColor3f(0.0,1.0,0.0); //Y vert
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,20,0);
		glEnd();

		glColor3f(0.0,0.0,1.0); //Z bleu
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(0,0,20);
		glEnd();

		glColor3f(1.0,0.0,0.0); //X rouge
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex3f(20,0,0);
		glEnd();

	glutSwapBuffers();// echange des buffers
}

/*void display(void)
{
	// clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);

	// draw white polygon (rectangle) with corners at
	// (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
	//

	//carre( point3d(1,1,1) );

	// Exercice 01
    drawFigure(c1,GL_LINE_LOOP);

	// Swap the buffers to show the one
	// on which we writed
	//
	glutSwapBuffers();
}*/

/*void init(void)
{
	// select clearing color
	glClearColor(0.0, 0.0, 0.0, 0.0);	//noir

	// initialize viewing values
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}*/

/* Au cas ou la fenetre est modifiee ou deplacee */
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //glOrtho(-20, 20, -20, 20, -10, 10);
   glOrtho(-2, 2, -2, 2, -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

GLvoid gestionSouris(int x, int y)
{
	angleX=x*720/WIDTH; //gere l'axe Oy
	angleY=-(y*180/HEIGHT-90)*4; //gere l'axe Ox

	glutPostRedisplay();
}

GLvoid gestionFleche(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP :
			tz+=int(pasDeplacement);glutPostRedisplay();
		break;

		case GLUT_KEY_DOWN :
			tz-=int(pasDeplacement);glutPostRedisplay();
		break;
	glutPostRedisplay();
	}

}

GLvoid window_key_down(unsigned char key, int x, int y)  //appuie des touches
{
    switch (key)
    {

    //deplacement de la camera
        case 'z':
            ty+=int(pasDeplacement);glutPostRedisplay();
        break;

        case 's':
            ty-=int(pasDeplacement);glutPostRedisplay();
        break;

        case 'q':
            tx-=int(pasDeplacement);glutPostRedisplay();
        break;

        case 'd':
            tx+=int(pasDeplacement);glutPostRedisplay();
        break;

        case 't':
            isTube = !isTube; createFigure(); glutPostRedisplay();
        break;
        case 'y':
            doubleSense = !doubleSense; createFigure(); glutPostRedisplay();
        break;
        case 'u':
            normalInverse = !normalInverse; createFigure(); glutPostRedisplay();
        break;
        case 'g':
            width+=1.; createFigure(); glutPostRedisplay();
        break;
        case 'h':
            width-=1.; createFigure(); glutPostRedisplay();
        break;
        case '0':case '1':case '2':case '3':case '4':case '5':case '6':
            selectedFigure = key-'0';
            createFigure(); glutPostRedisplay();
        break;

        // Save
        case 'w':
            printf ("Saving the mesh to 'maillaged/test'\n");
            OffFile::writeFile( f, "maillages/test" );
        break;
        // Remove faces
        case 'r':{
            printf ("Removing Faces from the Figure\n");
            int indexToRemove = 10;
            int amountToRemove = 10;
            for( int i=0; i<amountToRemove && indexToRemove<f->getFaces().size(); i++ ){
                f->removeFace( indexToRemove );
            }}
        break;

    //sortie
        case KEY_ESC:
            exit(0);
            break;

        default:
            printf ("La touche %d non active.\n", key);
        break;
        }
    glutPostRedisplay();
}

/*
* Declare initial window size, position, and display mode
* (double buffer and RGB).  Open window with "hello"
* in its title bar.  Call initialization routines.
* Register callback function to display graphics.
* Enter main loop and process events.
*/
int main(int argc, char** argv)
{
	glutInitWindowSize(1000, 1000);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Mes Figures");
    init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(&window_key_down);
    glutDisplayFunc(display);
    glutPassiveMotionFunc(gestionSouris);
    glutSpecialFunc(&gestionFleche);
    glutMainLoop();

	return 0;   /* ANSI C requires main to return int. */
}
