// Edgar Abundiz
// ID: 109379198
// CSCI 172
// Project 3 Quaternion Rotation

#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>

#include <math.h>
using namespace std;

bool WireFrame= false;

// The individual flags corresponding to the cube, the tea pot, and the sphere
bool cFlag = false;
bool tFlag= false;
bool sFlag = false;

// Initial values for zooming
GLdouble cTrans = -3.0; // Used for Cube
GLdouble cAngle = 0.0;  // Used for Cube
GLdouble sTrans = -1.0; // Used for sphere
GLdouble sAngle = 0.0;  // Used for sphere
GLdouble tTrans = 2.0;  // Used for tea pot
GLdouble tAngle = 0.0;  // Used for tea pot

//Prog 3 Variables
#define PI 3.14159
GLfloat matrixX[16];
GLfloat matrixY[16];
GLfloat matrixZ[16];
GLfloat x, y, z, w;

//Model rotation for X, Y, and Z indexes
static GLint rotateX = 0;
static GLint rotateY = 0;
static GLint rotateZ = 0;

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

   if(width<=height)
     {
         glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
         Ratio =  height/width;
      }
    else
      {
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
        Ratio = width /height;
      }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective (50.0f,Ratio,0.1f, 100.0f);
 }

void CreateMatrix(GLfloat *pMatrix)
{
    //First Row
    pMatrix[0] = 1.0f - 2.0f * (y * y + z * z);
    pMatrix[1] = 2.0f * (x * y - z * w);
    pMatrix[2] = 2.0f * (x * z + y * w);
    pMatrix[3] = 0.0f;

    //Second Row
    pMatrix[4] = 2.0f * (x * y + z * w);
    pMatrix[5] = 1.0f - 2.0f * (x * x + z * z);
    pMatrix[6] = 2.0f * (z * y - x * w);
    pMatrix[7] = 0.0f;

    //Third Row
    pMatrix[8] = 2.0f * (x * y - y * w);
    pMatrix[9] = 2.0f * (y * z + x * w);
    pMatrix[10] = 1.0f - 2.0f * (x * x + y * y);
    pMatrix[11] = 0.0f;

    //fourth Matrix
    pMatrix[12] = 0.0f;
    pMatrix[13] = 0.0f;
    pMatrix[14] = 0.0f;
    pMatrix[15] = 1.0f;
}

void CreateFromAxisAngle(GLfloat X, GLfloat Y, GLfloat Z, GLfloat degree)
{
    //First we want to convert the degrees to radians since the angle is assumed to be in radians
    GLfloat angle = (GLfloat)((degree / 180.0f) * PI);

    //Calculate the sin( theta / 2) once for optimization
    GLfloat result = (GLfloat)sin(angle/2.0f);

    //Calculate the w value by cos(theta / 2)
    w = (GLfloat)cos(angle / 2.0f);

    //Calculate the x, y, z of the quaternion
    x = (GLfloat)(X * result);
    y = (GLfloat)(Y * result);
    z = (GLfloat)(Z * result);

}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,5,10,0.0,0.0,0.0,0.0,1.0,0.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

	CreateMatrix(matrixX);                  //initial quatonion
	CreateFromAxisAngle(1, 0, 0, rotateX); 	//quatonion for x rotation
	glMultMatrixf(matrixX);                 //multiply original matrix

	CreateMatrix(matrixY);
	CreateFromAxisAngle(0, 1, 0, rotateY);  //quatonion for y rotation
	glMultMatrixf(matrixY);

	CreateMatrix(matrixZ);
	CreateFromAxisAngle(0, 0, 1, rotateZ);  //quatonion for z rotation
	glMultMatrixf(matrixZ);
/*
    // Creating Cube
    glPushMatrix();
    glColor3f(0,1.0,0); // sets color: green
    glTranslatef(3.5, 0.0, cTrans); // starting coordinate for cube, cTrans allows for zoom
    glRotatef(cAngle, 0.0, 1.0, 0.0); // rotate the object on Y axis
    glutSolidCube(2.5); // sets size of cube
    glPopMatrix();

    // Creating the sphere
    glPushMatrix();
    glColor3f(1.0,0,1.0); // sets color: purple
    glTranslatef(-3.5, 0.0, sTrans); // starting coordinate for sphere, sTrans allows for zoom
    glRotatef(sAngle, 0.0, 1.0, 0.0); // rotate the object
    glutSolidSphere(1, 30, 30); // size of sphere through its dimensions
    glPopMatrix();
*/
    // Creating the Tea pot
    glPushMatrix();
    glColor3f(1.0, 1.0, 0); // sets color: yellow
    glTranslatef(0.0, 0.0, 0.0); // starting coordinates of tea pot, sTrans allows for zoom
    //glRotatef(tAngle, 0.0, 1.0, 0.0); // rotates the object
    glutSolidTeapot(2); // size of tea pot
    glPopMatrix();

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
        /*case 'c': // manipulating the cub when c key is held down
            cFlag = true;
            sFlag = false;
            tFlag = false;
            break;
        case 's': // manipulating sphere when s key is held down
            sFlag = true;
            cFlag = false;
            tFlag = false;
            break;
        case 't': //manipulating tea pot when t key is held down
            tFlag = true;
            cFlag = false;
            sFlag = false;
            break;*/

        // w and s used to rotate around the X axis
        case 'w':
            rotateX = (rotateX + 5) % 360;
            break;
        case 's':
            rotateX = (rotateX - 5) % 360;
            break;
        // a and d used to rotate around Y axis
        case 'a':
            rotateY = (rotateY + 5) % 360;
            break;
        case 'd':
            rotateY = (rotateY - 5) % 360;
            break;
        //z and x used to rotate around z axis
        case 'z':
            rotateZ = (rotateZ + 5) % 360;
            break;
        case 'x':
            rotateZ = (rotateZ - 5) %360;
            break;
        //t used to toggle wireframe on and off
        case 't':
            if (WireFrame == false)
                WireFrame = true;
            else
                WireFrame = false;
            break;

    }
}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
        /*
    case GLUT_KEY_UP:  //move object away from you when pressing up
        if (cFlag) cTrans -= 0.5;
        else if (sFlag) sTrans -= 0.5;
        else tTrans -= 0.5;
    break;
    case GLUT_KEY_DOWN: // move object towards you when pressing down
        if (cFlag) cTrans += 0.5;
        else if (sFlag) sTrans += 0.5;
        else tTrans += 0.5;
    break;
    case GLUT_KEY_LEFT: // rotate clockwise when pressing left
        if (cFlag) cAngle -= 0.5;
        else if (sFlag) sAngle -= 0.5;
        else tAngle -= 0.5;
    break;
    case GLUT_KEY_RIGHT: // rotate counterclockwise when pressing right
        if (cFlag) cAngle += 0.5;
        else if (sFlag) sAngle += 0.5;
        else tAngle += 0.5;
    break;*/
   }
  glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

static void init(void)
{
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

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

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

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
