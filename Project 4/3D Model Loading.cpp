// Edgar Abundiz
// ID: 109379198
// CSCI 172
// Project 4 3D Model Loading
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>

#define PI 3.14159

using namespace std;

bool WireFrame= false;
float i =0;
float xpos =0;
float ypos =0;
float Wwidth,Wheight;

//setting default values
GLfloat rotateX = 0;
GLfloat rotateY = 0;
GLfloat rotateZ = 0;
GLfloat translateZ = 0;

//Creating the model
GLfloat Vertices[8][3] =
{
{0.0, 0.0, 0.0},
{0.0, 0.0, 1.0},
{0.0, 1.0, 0.0},
{0.0, 1.0, 1.0},
{1.0, 0.0, 0.0},
{1.0, 0.0, 1.0},
{1.0, 1.0, 0.0},
{1.0, 1.0, 1.0},
};

GLfloat Normals[6][3] =
{
{0.0, 0.0, 1.0},
{0.0, 0.0,-1.0},
{0.0, 1.0, 0.0},
{0.0,-1.0, 0.0},
{1.0, 0.0, 0.0},
{-1.0, 0.0, 0.0},
};

GLint ind[12][6] =
{

{1,2, 7,2, 5,2},
{1,2, 3,2, 7,2},
{1,6, 4,6, 3,6},
{1,6, 2,6, 4,6},
{3,3, 8,3, 7,3},
{3,3, 4,3, 8,3},
{5,5, 7,5, 8,5},
{5,5, 8,5, 6,5},
{1,4, 5,4, 6,4},
{1,4, 6,4, 2,4},
{2,1, 6,1, 8,1},
{2,1, 8,1, 4,1},
};

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



/* GLUT callback Handlers */

static void resize(int width, int height)
{
     double Ratio;

     Wwidth = (float)width;
     Wheight = (float)height;

     Ratio= (double)width /(double)height;

    glViewport(0,0,(GLsizei) width,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective (45.0f,Ratio,0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


 }

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,6,0.0,0.0,0.0,0.0,1.0,100.0);

    //Rotation and translation functions
    glTranslated(-0.5, -0.5, translateZ);
    glRotatef(rotateX, 1.0, 0.0, 0.0);  //for rotating around x axis
    glRotatef(rotateY, 0.0, 1.0, 0.0);  //for rotating around y axis
    glRotatef(rotateZ, 0.0, 0.0, 1.0);  //for rotating around z axis

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    // your code here
    //Drawing out the cube with colors
    glBegin(GL_TRIANGLES);
    int i = 0;
    while (i < 12)
    {
    glColor3f(Vertices[ind[i][0]-1][0], Vertices[ind[i][0]-1][1],Vertices[ind[i][0]-1][2]);
    glNormal3f(Normals[ind[i][1]-1][0], Normals[ind[i][1]-1][1], Normals[ind[i][1]-1][2]);
    glVertex3f(Vertices[ind[i][0]-1][0], Vertices[ind[i][0]-1][1],Vertices[ind[i][0]-1][2]);

    glColor3f(Vertices[ind[i][2]-1][0],Vertices[ind[i][2]-1][1],Vertices[ind[i][2]-1][2]);
    glNormal3f(Normals[ind[i][3]-1][0], Normals[ind[i][3]-1][1], Normals[ind[i][3]-1][2]);
    glVertex3f(Vertices[ind[i][2]-1][0],Vertices[ind[i][2]-1][1],Vertices[ind[i][2]-1][2]);


    glColor3f(Vertices[ind[i][4]-1][0],Vertices[ind[i][4]-1][1],Vertices[ind[i][4]-1][2]);
    glNormal3f(Normals[ind[i][5]-1][0], Normals[ind[i][5]-1][1], Normals[ind[i][5]-1][2]);
    glVertex3f(Vertices[ind[i][4]-1][0],Vertices[ind[i][4]-1][1],Vertices[ind[i][4]-1][2]);

    i += 1;
    }
    glEnd();
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

	  case 'w':
		WireFrame =!WireFrame;
	       break;

      case 'd':  //rotate clockwise around z axis
        rotateZ = ((int)rotateZ+2)%360;
        break;

      case 'a':  //rotate counterclockwise around z axis
        rotateZ = ((int)rotateZ-2)%360;
        break;
    }
}


void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_END: //zoom in
        translateZ += (float) 1.0f;
        break;

    case GLUT_KEY_HOME: //zoom out
        translateZ -= (float) 1.0f;
        break;

    case GLUT_KEY_DOWN: //rotate down on x axis
        rotateX = ((int)rotateX+2)%360;
        break;

    case GLUT_KEY_UP: //rotate up on x axis
        rotateX= ((int)rotateX-2)%360;
        break;

    case GLUT_KEY_RIGHT: //rotate right on y axis
        rotateY =((int)rotateY+2)%360;
        break;

    case GLUT_KEY_LEFT: //rotate left on y axis
        rotateY= ((int)rotateY-2)%360;
        break;

   }
  glutPostRedisplay();
}


static void idle(void)
{
    // Use parametric equation with t increment for xpos and y pos
    // Don't need a loop
    glutPostRedisplay();
}


static void init(void)
{
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glClearColor(0.5f, 1.5f, 1.0f, 0.0f);                 // assign a color you like

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Project Assignment 4");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
