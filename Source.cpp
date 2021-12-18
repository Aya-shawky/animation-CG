#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <cstdio>
#include "glm.h"
#include <assert.h>
#include <fstream>
#include "imageloader.h"


#define PI 3.14

/*define object*/

const char* modelname1 = "data/plasticChair.obj";
const char* modelname2 = "data/com_bath2_jabon_pijo.obj";
/*
GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
*/
GLfloat light0_position[] = { 0, 0 , 2.0, 1.0 };

//camera
double eye[] = {0,  0.9, 2.396396};
double center[] = { 0, 0, 0 };
double up[] = { 0.0, 1.0, 0.0 };

// define texture

// RGBA
GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
// x , y, z, w
GLfloat light_position[] = { 0.5, 5.0, 0.0, 1.0 };
GLfloat lightPos1[] = { -1.0, -1.0, -1.0, 1.0 };

// define robot
void setposes(int framenum);
static int leftshoulderz = 0, leftshoulderx = 0, leftelbowz = 0, leftelbowx = 0, body = 0;
static int fingerBase1 = 0, fingerUp1 = 0;
static int fingerBase2 = 0, fingerUp2 = 0;
static int fingerBase3 = 0, fingerUp3 = 0;
static int fingerBase4 = 0, fingerUp4 = 0;
static int fingerBase5 = 0, fingerUp5 = 0;
static int Lefthipz = 0, Lefthipx = 0, LeftKneez = 0, LeftKneex = 0, LeftFoot = 0;


static int rightshoulderz = 0, rightshoulderx = 0, rightelbowz = 0, rightelbowx = 0;
static int fingerBase21 = 0, fingerUp21 = 0;
static int fingerBase22 = 0, fingerUp22 = 0;
static int fingerBase23 = 0, fingerUp23 = 0;
static int fingerBase24 = 0, fingerUp24 = 0;
static int fingerBase25 = 0, fingerUp25 = 0;
static int Righthipz = 0, Righthipx = 0, RightKneez = 0, RightKneex = 0, RightFoot = 0;

static int bodyx = 0, bodyy = 1, bodyz = -6;

int moving, startx, starty;

GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */



/*
int poses[24][14] = { {45,-55,-90,-90,0,0,20,90,0,0,0,0,0.904038,2.396396},{20,-10,-35,-65,0,15,-5,-5,10,0,0,0,0.904038,2.396396},
                     {45,-65,-35,-65,0,-30,-20,35,90,0,20,0,0.904038,2.396396},{-65,45,-80,-30,0,-20,-70,90,10,20,20,0,0,3.5},{0,0,0,0,0,0,0,0,0,0,0,0,0.904038,2.396396},
                      {0,-20,0,0,0,0,0,0,0,0,0,0,0.904038,2.396396},{0,-20,0,0,30,0,0,0,0,0,0,0,0.904038,2.396396},
                      {0,-30,0,0,70,0,0,0,0,0,0,0,0.904038,2.396396},{0,-30,0,-60,70,0,0,0,0,0,0,0,0.904038,2.396396},{0,-30,0,-60,90,0,0,0,0,0,0,0,0.904038,2.396396},
                      {0,-35,0,-35,90,0,0,0,0,0,0,0,0.904038,2.396396},{0,-35,0,10,90,0,0,0,0,0,0,0,0.904038,2.396396},
                      {0,0,0,10,90,0,0,0,0,0,0,0,0.904038,2.396396},{0,0,0,10,0,0,0,0,0,0,0,0,0.904038,2.396396},
                      {0,0,0,0,0,0,0,0,0,0,0,0,0.904038,2.396396}, {0,0,0,0,0,0,0,0,0,0,0,0,0.904038,2.396396}, {0,0,0,0,0,0,0,0,0,0,0,0,0.904038,2.396396},{0,0,0,0,0,0,0,0,0,0,0,0,0.904038,2.396396}, {0,0,0,0,0,0,0,0,0,0,0,-2,0,0.3},
                      {0,0,0,0,0,-60,-60,0,0,0,0,0,0.904038,2.396396},{0,0,0,0,0,-90,-90,0,0,0,0,0,0.904038,2.396396},
                      {0,0,0,0,0,-90,-90,0,50,0,0,0,0.904038,2.396396},{0,0,0,0,0,-90,-90,50,0,0,0,0.904038,2.396396},
                      {0,0,0,0,0,-90,-90,90,90,0,0,0,0.904038,2.396396} };
*/
int poses[24][14] = { 
    {45,-55,-90,-90,0,0,20,90,0,0,0,0,1,-4},
    {20,-10,-35,-65,0,15,-5,-5,10,0,-15,0,1,-2},                     
    {45,-65,-35,-65,0,-30,-20,35,90,0,0,0,1,0},
    {-65,45,-80,-30,0,-20,-70,90,10,20,20,0,1,2},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,2},                     
    {0,-20,0,0,0,0,0,0,0,0,0,0,1,2},
    {0,-20,0,0,30,0,0,0,0,0,0,0,1,2},
    {0,-30,0,0,70,0,0,0,0,0,0,0,1,2},
    {0,-30,0,-60,70,0,0,0,0,0,0,0,1,2},
    {0,-30,0,-60,90,0,0,0,0,0,0,0,1,2},
    {0,-35,0,-35,90,0,0,0,0,0,0,0,1,2},
    {0,-35,0,10,90,0,0,0,0,0,0,0,1,2},
    {0,0,0,10,90,0,0,0,0,0,0,0,1,2},
    {0,0,0,10,0,0,0,0,0,0,0,0,1,2},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,2},
    {0,0,0,0,0,0,0,0,0,0,0,2,1,2},
    {0,0,0,0,0,0,0,0,0,0,0,4,1,2},
    {0,0,0,0,0,-60,-60,0,0,0,0,4,1,2},
    {0,0,0,0,0,-90,-90,0,0,0,0,4,1,2},
    {0,0,0,0,0,-90,-90,0,50,0,0,4,1,2},
    {0,0,0,0,0,-90,-90,50,50,0,0,4,1,2},
    {0,0,0,0,0,-90,-90,90,90,0,0,4,1,2} };

GLuint _textureId; //The id of the texture

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image)
{
    GLuint textureId;
    glGenTextures(1, &textureId);			 //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,				  //Always GL_TEXTURE_2D
        0,							  //0 for now
        GL_RGB,					  //Format OpenGL uses for image
        image->width, image->height, //Width and height
        0,							  //The border of the image
        GL_RGB,					  //GL_RGB, because pixels are stored in RGB format
        GL_UNSIGNED_BYTE,			  //GL_UNSIGNED_BYTE, because pixels are stored
                                     //as unsigned numbers
        image->pixels);			  //The actual pixel data
    return textureId;						  //Returns the id of the texture
}


void drawmodel(char* filename)
{
    GLMmodel* model = glmReadOBJ(filename);
    glmUnitize(model);
    glmFacetNormals(model);
    glmVertexNormals(model, 90.0);
    glmScale(model, 0.6);
    glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
}

void crossProduct(double a[], double b[], double c[])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[])
{

    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];
}

void init(void)
{
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glEnable(GL_NORMALIZE);

    glShadeModel(GL_FLAT);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0, 1.0, 1.0, 20.0);
    //glMatrixMode(GL_MODELVIEW);
}


//Initializes 3D rendering
void initRendering()
{
    Image* image = loadBMP("images/grass1.bmp");
    _textureId = loadTexture(image);
    delete image;
    // Turn on the power
    glEnable(GL_LIGHTING);
    // Flip light switch
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    // assign light parameters
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    // Material Properties
    GLfloat lightColor1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor1);
    glEnable(GL_NORMALIZE);
    //Enable smooth shading
    glShadeModel(GL_SMOOTH);
    // Enable Depth buffer
    glEnable(GL_DEPTH_TEST);
}


void reset()
{
    double e[] = { 0.0, 0.0, 2 };
    double c[] = { 0.0, 0.0, 1.0 };
    double u[] = { 0.0, 1.0, 0.0 };
    for (int i = 0; i < 3; i++)
    {
        eye[i] = e[i];
        center[i] = c[i];
        up[i] = u[i];
    }
}





void display(void)
{
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

    glPushMatrix();
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBegin(GL_QUADS);
    glNormal3f(0.0, 2.0, 0.0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-4, -1, 2);
    glTexCoord2f(3.0f, 0.0f); glVertex3f(4, -1, 2);
    glTexCoord2f(3.0f, 3.0f); glVertex3f(4, -1, -2);
    glTexCoord2f(0.0f, 3.0f); glVertex3f(-4, -1, -2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    //object
    glPushMatrix();
    glTranslatef(0.7, -0.3, 0.1);
    glScalef(-1, 1, 1);
    drawmodel((char*)modelname1);
    glPopMatrix();

    //robot
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glScaled(0.2, 0.2, 0.2);
    glTranslatef(bodyx, bodyy, bodyz);

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef((GLfloat)body, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.5, 4.0, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    //   Head
    glPushMatrix();
    glTranslatef(0.0, 2.6, 0.0);
    glutWireSphere(0.42, 10, 10);
    glPopMatrix();

    glPopMatrix();

    //    Right Arm
    glPushMatrix();
    glTranslatef(-0.9, 1.85, 0.0);
    glRotatef((GLfloat)rightshoulderz, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rightshoulderx, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.55, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.0, -0.6, 0.0);
    glRotatef((GLfloat)rightelbowz, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rightelbowx, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.65, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

 

    //**********1
    glPushMatrix();
    glTranslatef(-0.1, -0.35, -0.1);
    glRotatef((GLfloat)fingerBase1, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)fingerUp1, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //*************2
    glPushMatrix();
    glTranslatef(-0.1, -0.35, 0.0);
    glRotatef((GLfloat)fingerBase2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)fingerUp2, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //*************3
    glPushMatrix();
    glTranslatef(-0.1, -0.35, 0.1);
    glRotatef((GLfloat)fingerBase3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)fingerUp3, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //*************4
    glPushMatrix();
    glTranslatef(0.1, -0.35, 0.0);
    glRotatef((GLfloat)fingerBase4, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)fingerUp4, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();


    //**********bottel*****
    glPushMatrix();
    glTranslatef(-0.1, -0.35, -0.1);
    drawmodel((char*)modelname2);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();

    //   Left Arm
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(0.9, 1.85, 0.0);
    glRotatef((GLfloat)leftshoulderz, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)leftshoulderx, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.55, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutWireCube(1.0);

    glPopMatrix();

    glTranslatef(0.0, -0.6, 0.0);
    glRotatef((GLfloat)leftelbowz, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)leftelbowx, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.65, 0.0);
    glPushMatrix();
    glScalef(0.3, 1.25, 0.3);
    glutWireCube(1.0);
    glPopMatrix();

    //**********1
    glPushMatrix();
    glTranslatef(0.1, -0.35, -0.1);
    glRotatef((GLfloat)fingerBase21, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)fingerUp21, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //*************2
    glPushMatrix();
    glTranslatef(0.1, -0.35, 0.0);
    glRotatef((GLfloat)fingerBase22, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)fingerUp22, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //*************3
    glPushMatrix();
    glTranslatef(0.1, -0.35, 0.1);
    glRotatef((GLfloat)fingerBase23, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)fingerUp23, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();
    //*************4
    glPushMatrix();
    glTranslatef(-0.1, -0.35, 0.0);
    glRotatef((GLfloat)fingerBase24, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.4, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glTranslatef(0.0, -0.1, 0.0);
    glRotatef((GLfloat)fingerUp24, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glPushMatrix();
    glScalef(0.1, 0.3, 0.1);
    glutWireCube(1);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();


    //   Right Leg
    glPushMatrix();
    glTranslatef(-0.55, -2.0, 0.0);
    glRotatef((GLfloat)Righthipz, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)Righthipx, 1.0, 0.0, 0.0);
    glTranslatef(0.05, -0.9, 0.0);

    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.0, -0.8, 0.0);
    glRotatef((GLfloat)RightKneez, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)RightKneex, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.8, 0.0);

    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    glTranslatef(0.0, -1.0, 0.0);
    glRotatef((GLfloat)RightFoot, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.55, 0.5, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();

    //  Left Leg
    glPushMatrix();
    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(0.55, -2.0, 0.0);
    glRotatef((GLfloat)Lefthipz, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)Lefthipx, 1.0, 0.0, 0.0);
    glTranslatef(-0.05, -0.9, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutWireCube(1.0);

    glPopMatrix();

    glTranslatef(0.0, -0.8, 0.0);
    glRotatef((GLfloat)LeftKneez, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)LeftKneex, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -0.9, 0.0);
    glPushMatrix();
    glScalef(0.5, 1.7, 0.5);
    glutWireCube(1.0);

    glPopMatrix();

    glTranslatef(0.0, 0.0, 0.0);
    glRotatef((GLfloat)LeftFoot, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.0, 0.0);
    glPushMatrix();
    glScalef(0.55, 0.5, 1.0);
    glutSolidCube(1.0);

    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();

}

// Rotation about vertical direction
void lookRight()
{
    rotatePoint(up, PI / 20, eye);
}

void lookLeft()
{
    rotatePoint(up, -PI / 20, eye);
}

// Rotation about horizontal direction

void lookUp()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, PI / 20, eye);
    rotatePoint(horizontal, PI / 20, up);
}

void lookDown()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -PI / 20, eye);
    rotatePoint(horizontal, -PI / 20, up);
}

// Forward and Backward
void moveForward()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    double speed = 0.1;
    eye[0] += direction[0] * speed;
    eye[1] += direction[1] * speed;
    eye[2] += direction[2] * speed;

    center[0] += direction[0] * speed;
    center[1] += direction[1] * speed;
    center[2] += direction[2] * speed;
}

void moveBackword()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    double speed = 0.1;
    eye[0] -= direction[0] * speed;
    eye[1] -= direction[1] * speed;
    eye[2] -= direction[2] * speed;

    center[0] -= direction[0] * speed;
    center[1] -= direction[1] * speed;
    center[2] -= direction[2] * speed;

}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        lookLeft();
        break;
    case GLUT_KEY_RIGHT:
        lookRight();
        break;
    case GLUT_KEY_UP:
        lookUp();
        break;
    case GLUT_KEY_DOWN:
        lookDown();
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        //camera's keys
    case '+':
        moveForward();
        glutPostRedisplay();
        break;
    case '-':
        moveBackword();
        glutPostRedisplay();
        break;
    case '0':
        reset();
        glutPostRedisplay();
        break;
        //   Left Arm
        // shoulder zzz
    case 's':
        if (leftshoulderz < 180) {
            leftshoulderz = (leftshoulderz + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'S':
        if (leftshoulderz > -20) {
            leftshoulderz = (leftshoulderz - 5) % 360;
            glutPostRedisplay();
        }
        break;
        // elbow zzz
    case 'E':
        if (leftelbowz < 0) {
            leftelbowz = (leftelbowz + 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'e':
        if (leftelbowz > -90) {
            leftelbowz = (leftelbowz - 5) % 180;
            glutPostRedisplay();
        }
        break;

        // shoulder xxx
    case 'I':
        if (leftshoulderx < 45) {
            leftshoulderx = (leftshoulderx + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'i':
        if (leftshoulderx > -180) {
            leftshoulderx = (leftshoulderx - 5) % 360;
            glutPostRedisplay();
        }
        break;
        // elbow xxx
    case 'J':
        if (leftelbowx < 10) {
            leftelbowx = (leftelbowx + 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'j':
        if (leftelbowx > -90) {
            leftelbowx = (leftelbowx - 5) % 180;
            glutPostRedisplay();
        }
        break;

        // Right Arm
        // Shoulder zzz
    case 'A':
        if (rightshoulderz < 20) {
            rightshoulderz = (rightshoulderz + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'a':
        if (rightshoulderz > -180) {
            rightshoulderz = (rightshoulderz - 5) % 360;
            glutPostRedisplay();
        }
        break;
        // Elbow zzz
    case 'w':
        if (rightelbowz < 90) {
            rightelbowz = (rightelbowz + 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'W':
        if (rightelbowz > 0) {
            rightelbowz = (rightelbowz - 5) % 180;
            glutPostRedisplay();
        }
        break;
        // Shoulder xxx
    case 'G':
        if (rightshoulderx < 45) {
            rightshoulderx = (rightshoulderx + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'g':
        if (rightshoulderx > -180) {
            rightshoulderx = (rightshoulderx - 5) % 360;
            glutPostRedisplay();
        }
        break;
        // Elbow xxx
    case 'H':
        if (rightelbowx < 10) {
            rightelbowx = (rightelbowx + 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'h':
        if (rightelbowx > -90) {
            rightelbowx = (rightelbowx - 5) % 180;
            glutPostRedisplay();
        }
        break;


        // Right Leg
    case 'x':
        if (Righthipx > -90) {
            Righthipx = (Righthipx - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'X':
        if (Righthipx < 90) {
            Righthipx = (Righthipx + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'z':
        if (RightKneex > -20) {
            RightKneex = (RightKneex - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'Z':
        if (RightKneex < 90) {
            RightKneex = (RightKneex + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'D':
        if (Righthipz < 20) {
            Righthipz = (Righthipz + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'd':
        if (Righthipz > -90) {
            Righthipz = (Righthipz - 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'R':
        if (RightKneez < 30) {
            RightKneez = (RightKneez + 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'r':
        if (RightKneez > -30) {
            RightKneez = (RightKneez - 5) % 180;
            glutPostRedisplay();
        }
        break;

        // Left Leg
    case 'f':
        if (Lefthipz < 90) {
            Lefthipz = (Lefthipz + 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'F':
        if (Lefthipz > -20) {
            Lefthipz = (Lefthipz - 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 't':
        if (LeftKneez < 50) {
            LeftKneez = (LeftKneez + 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'T':
        if (LeftKneez > -50) {
            LeftKneez = (LeftKneez - 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'c':
        if (Lefthipx > -90) {
            Lefthipx = (Lefthipx - 5) % 360;
            glutPostRedisplay();
        }
        break;
    case 'C':
        if (Lefthipx < 90) {
            Lefthipx = (Lefthipx + 5) % 360;
            glutPostRedisplay();
        }
        break;

    case 'v':
        if (LeftKneex > -20) {
            LeftKneex = (LeftKneex - 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'V':
        if (LeftKneex < 90) {
            LeftKneex = (LeftKneex + 5) % 180;
            glutPostRedisplay();
        }
        break;

    case 'l':
        if (RightFoot > -20) {
            RightFoot = (RightFoot - 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'L':
        if (RightFoot < 20) {
            RightFoot = (RightFoot + 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'k':
        if (LeftFoot > -20) {
            LeftFoot = (LeftFoot - 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'K':
        if (LeftFoot < 20) {
            LeftFoot = (LeftFoot + 5) % 180;
            glutPostRedisplay();
        }
        break;
    case 'o':
        if (bodyx < 20) {
            bodyx = (bodyx + 1) % 180;
            glutPostRedisplay();
        }
        break;
    case 'O':
        if (bodyx < 20) {
            bodyx = (bodyx - 1) % 180;
            glutPostRedisplay();
        }
        break;
    case 'p':
        if (bodyy < 20) {
            bodyy = (bodyy + 1) % 180;
            glutPostRedisplay();
        }
        break;
    case 'P':
        if (bodyy < 20) {
            bodyy = (bodyy - 1) % 180;
            glutPostRedisplay();
        }
        break;
    case '[':
        if (bodyz < 20) {
            bodyz = (bodyz + 1) % 180;
            glutPostRedisplay();
        }
        break;
    case ']':
        if (bodyz < 20) {
            bodyz = (bodyz - 1) % 180;
            glutPostRedisplay();
        }
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }
}




void main_menu(int value)
{
    if (value == 1)
    {
        printf(" left shoulder in x: %d \n ", leftshoulderx);
        printf("right shoulder in x : %d \n ", rightshoulderx);
        printf(" left elbow in x  : %d \n ", leftelbowx);
        printf("right elbow in x  : %d \n ", rightelbowx);
        printf("right elbow in z  : %d \n ", rightelbowz);
        printf("right hip in x   : %d \n ", Righthipx);
        printf("  left hip in x : %d \n ", Lefthipx);
        printf("left knee in x : %d \n ", LeftKneex);
        printf("right knee in x : %d \n ", RightKneex);
        printf(" right foot: %d \n  ", RightFoot);
        printf("left foot: %d \n  ", LeftFoot);
        printf("robot position x: %d \n ", bodyx);
        printf("robot position y: %d \n ", bodyy);
        printf("robot position z: %d \n ", bodyz);


    }
    else if (value == 2)
    {
        for (int i = 0; i < 3; i++)
            printf("eye [%d] = %f \n  ", i, eye[i]);
    }


}

void setposes(int framenum)
{
    leftshoulderx = poses[framenum][0];
    rightshoulderx = poses[framenum][1];
    leftelbowx = poses[framenum][2];
    rightelbowx = poses[framenum][3];
    rightelbowz = poses[framenum][4];
    Righthipx = poses[framenum][5];
    Lefthipx = poses[framenum][6];
    LeftKneex = poses[framenum][7];
    RightKneex = poses[framenum][8];
    RightFoot = poses[framenum][9];
    LeftFoot = poses[framenum][10];
    bodyx = poses[framenum][11];
    bodyy = poses[framenum][12];
    bodyz = poses[framenum][13];

    /*  eye[0] = poses[framenum][11];
      eye[1] = poses[framenum][12];
      eye[2] = poses[framenum][13];
      */

}

static int f = 0;
void timer(int value)
{
    f = f % 24;
    setposes(f);
    f++;
    glutPostRedisplay();
    glutTimerFunc(500, timer, 0);
}




int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(750, 750);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    initRendering();
    glutCreateMenu(main_menu);
    glutAddMenuEntry("capture position", 1);
    glutAddMenuEntry("capture eye", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutTimerFunc(0, timer, 0);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
