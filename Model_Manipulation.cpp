#include <iostream>
#include <string>
#include <fstream>
#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include "vertex.h"
#include <stdlib.h>
#include "ReadBMP.h"
#include "ImageManipulation.h"
using namespace std;
void switch_models(int index);
int WindowWidth = 600, WindowHeight = 600;
double posX = 0.0, posY = 0.0, posZ = 0.0, posInc = 0.1, angleInc = 2.0;
double rotateX = 0.0, rotateY = 0.0, rotateZ = 0.0;
static double scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0;
int option = 0, axisornot = 0;
bool mousePanMode=false, mouseZoomMode=false, mouseRotationMode=false;
int mouseX = 0, mouseY = 0;
float eyeX=0, eyeY=0, eyeZ=0, focusX=0, focusY=0, focusZ=0, upX=0, upY=1, upZ=0;
int size = 1000;
//-------------Models ---------------
vertex Manipulation;
vertex Manipulation2;
vertex Manipulation3;
vertex Manipulation4;

float transX=0, transY=0, transZ=0, transparent=1.0;
bool displayWireFrame = true, displayVertices = false, displayFaces = false, DisplayTextures = false;
GLuint   textureNumber[20];

//---------------------------------------------------------------------
void InitTransparent()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glClearColor(0,0,0,0);
}
//---------------------------Box------------------------------------------
void DrawBox(){

glBindTexture(GL_TEXTURE_2D, textureNumber[1]);

// Front face
glBegin(GL_QUADS);
glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
glTexCoord2f(1, 0); glVertex3f(size, 0, 0);
glTexCoord2f(1, 1); glVertex3f(size, size, 0);
glTexCoord2f(0, 1); glVertex3f(0, size, 0);
glEnd();

// Back face
glBegin(GL_QUADS);
glTexCoord2f(0, 0); glVertex3f(0, 0, size);
glTexCoord2f(1, 0); glVertex3f(size, 0, size);
glTexCoord2f(1, 1); glVertex3f(size, size, size);
glTexCoord2f(0, 1); glVertex3f(0, size, size);
glEnd();

// Left face
glBegin(GL_QUADS);
glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
glTexCoord2f(1, 0); glVertex3f(0, 0, size);
glTexCoord2f(1, 1); glVertex3f(0, size, size);
glTexCoord2f(0, 1); glVertex3f(0, size, 0);
glEnd();

// Right face
glBegin(GL_QUADS);
glTexCoord2f(0, 0); glVertex3f(size, 0, 0);
glTexCoord2f(1, 0); glVertex3f(size, 0, size);
glTexCoord2f(1, 1); glVertex3f(size, size, size);
glTexCoord2f(0, 1); glVertex3f(size, size, 0);
glEnd();

// Top face
glBegin(GL_QUADS);
glTexCoord2f(0, 0); glVertex3f(0, size, 0);
glTexCoord2f(1, 0); glVertex3f(size, size, 0);
glTexCoord2f(1, 1); glVertex3f(size, size, size);
glTexCoord2f(0, 1); glVertex3f(0, size, size);
glEnd();

// Bottom face
glBegin(GL_QUADS);
glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
glTexCoord2f(1, 0); glVertex3f(size, 0, 0);
glTexCoord2f(1, 1); glVertex3f(size, 0, size);
glTexCoord2f(0, 1); glVertex3f(0, 0, size);
glEnd();



}
//-----------Sphere-----------------------
void drawSphere(float radius, int slices, int stacks, int num) {
    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureNumber[num]);

    gluSphere(quadric, radius, slices, stacks);

    glDisable(GL_TEXTURE_2D);

    gluDeleteQuadric(quadric);
}
//----------------Rectangle-------------------------
void DrawRectangle(float width, float height, int num)
{
    glBindTexture(GL_TEXTURE_2D, textureNumber[num]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0); glVertex3f(width, 0, 0);
    glTexCoord2f(1, 1); glVertex3f(width, height, 0);
    glTexCoord2f(0, 1); glVertex3f(0, height, 0);
    glEnd();
}

//------------------------------------fog-------------------
void setupFog()
{
    GLfloat fogColor[4] = {0.5, 0.5, 0.5, 1.0}; // Fog color (gray)
    glFogi(GL_FOG_MODE, GL_LINEAR); // Set the fog mode to linear
    glFogfv(GL_FOG_COLOR, fogColor); // Set the fog color
    glFogf(GL_FOG_DENSITY, 0.05); // Set the fog density
    glHint(GL_FOG_HINT, GL_NICEST); // Set the fog hint to the nicest quality
    glFogf(GL_FOG_START, 500.0); // Set the fog start distance
    glFogf(GL_FOG_END, 1000.0); // Set the fog end distance
    glEnable(GL_FOG); // Enable fog
}

//-----------------------------road sign----------------------------------------

void drawSquare(float width, float height, int num)
{
    glBindTexture(GL_TEXTURE_2D, textureNumber[num]);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);  // Texture coordinate for the bottom-left vertex
    glVertex3f(-width / 2.0f, -height / 2.0f, 0.0f);

    glTexCoord2f(1.0f, 0.0f);  // Texture coordinate for the bottom-right vertex
    glVertex3f(width / 2.0f, -height / 2.0f, 0.0f);

    glTexCoord2f(1.0f, 1.0f);  // Texture coordinate for the top-right vertex
    glVertex3f(width / 2.0f, height / 2.0f, 0.0f);

    glTexCoord2f(0.0f, 1.0f);  // Texture coordinate for the top-left vertex
    glVertex3f(-width / 2.0f, height / 2.0f, 0.0f);

    glEnd();
}

void drawCylinder(float height, float radius, int slices)
{
    GLUquadricObj* quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, textureNumber[20]);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // Rotate around X-axis by 90 degrees
    gluCylinder(quadObj, radius, radius, height, slices, 1);
    glPopMatrix();

    gluDeleteQuadric(quadObj);
}
void drawRoadSign(int num)
{
    float poleHeight = 20.0f;
    float poleRadius = 1.0f;
    int poleSlices = 40;

    float signWidth = 20.0f;
    float signHeight = 10.0f;

    // Draw the pole (cylinder)
    glPushMatrix();
    drawCylinder(poleHeight, poleRadius, poleSlices);
    glPopMatrix();

    // Draw the signboard (square)
    glPushMatrix();
    glTranslatef(0, 0, 1);
    drawSquare(signWidth, signHeight, num);
    glPopMatrix();
}
//-------------------------------------TV--------------
void drawTV(float size, int num, int num2)
{
    // Set the front face vertices
    float frontVertices[4][3] = {
        {-size, -size, size},
        {size, -size, size},
        {size, size, size},
        {-size, size, size}
    };

    // Set the back face vertices
    float backVertices[4][3] = {
        {-0.5 * size, -0.5 * size, -size},
        {0.5 * size, -0.5 * size, -size},
        {0.5 * size, 0.5 * size, -size},
        {-0.5 * size, 0.5 * size, -size}
    };

    // Set the texture coordinates for front face
    float frontTexCoords[4][2] = {
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
        {0.0, 1.0}
    };

    // Set the texture coordinates for side faces
    float sideTexCoords[4][2] = {
        {0.0, 0.0},
        {1.0, 0.0},
        {1.0, 1.0},
        {0.0, 1.0}
    };

    glBindTexture(GL_TEXTURE_2D, textureNumber[num]);

    // Draw the front face
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5); // Gray color
    for (int i = 0; i < 4; i++) {
        glTexCoord2fv(frontTexCoords[i]);
        glVertex3fv(frontVertices[i]);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, textureNumber[num2]);

    // Draw the back face
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        glVertex3f(backVertices[i][0], backVertices[i][1], backVertices[i][2]);
    }
    glEnd();


    // Draw the side faces
    glBegin(GL_QUADS);

    glTexCoord2fv(sideTexCoords[0]);
    glVertex3fv(frontVertices[0]);
    glTexCoord2fv(sideTexCoords[1]);
    glVertex3fv(backVertices[0]);
    glTexCoord2fv(sideTexCoords[2]);
    glVertex3fv(backVertices[3]);
    glTexCoord2fv(sideTexCoords[3]);
    glVertex3fv(frontVertices[3]);

    glTexCoord2fv(sideTexCoords[0]);
    glVertex3fv(frontVertices[1]);
    glTexCoord2fv(sideTexCoords[1]);
    glVertex3fv(backVertices[1]);
    glTexCoord2fv(sideTexCoords[2]);
    glVertex3fv(backVertices[2]);
    glTexCoord2fv(sideTexCoords[3]);
    glVertex3fv(frontVertices[2]);

    glTexCoord2fv(sideTexCoords[0]);
    glVertex3fv(frontVertices[2]);
    glTexCoord2fv(sideTexCoords[1]);
    glVertex3fv(backVertices[2]);
    glTexCoord2fv(sideTexCoords[2]);
    glVertex3fv(backVertices[3]);
    glTexCoord2fv(sideTexCoords[3]);
    glVertex3fv(frontVertices[3]);

    glTexCoord2fv(sideTexCoords[0]);
    glVertex3fv(frontVertices[0]);
    glTexCoord2fv(sideTexCoords[1]);
    glVertex3fv(backVertices[0]);
    glTexCoord2fv(sideTexCoords[2]);
    glVertex3fv(backVertices[1]);
    glTexCoord2fv(sideTexCoords[3]);
    glVertex3fv(frontVertices[1]);
    glEnd();
}

//----------------------My Display-----------------------------------------------
static float angle = 0, angle2 = 0 ;
void myDisplayFunc(void)
{
    // set the lighting
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    GLfloat amb_light[] = { 0.5f,0.5f,0.5f,1.0f };
    GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightpos[] = {0.f,0.f,200.0f,1.0f};

    glLightfv( GL_LIGHT0, GL_AMBIENT, amb_light );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glEnable( GL_LIGHT0 );
    glEnable( GL_COLOR_MATERIAL );
    glShadeModel( GL_SMOOTH );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
    glDepthFunc( GL_LEQUAL );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_LIGHTING);
    glPopMatrix();
    // start of the models display
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotateZ, 0.0f, 0.0f, 1.0f);
    glScalef(scaleX, scaleY, scaleZ);
    // First group of transformations and rendering calls for Model 1: Plant
    glPushMatrix();
    glTranslatef(-55, 40, -100);
    glScalef(250, 250, 250);
    if (axisornot % 2 == 1)
        Manipulation.DrawAxis();  // Press

    if (displayWireFrame)
        Manipulation.DisplayWireFrame(transparent);
    if (displayFaces)
        Manipulation.DisplayFaces(transparent);
    if (displayVertices)
        Manipulation.DisplayVertices();
    if (DisplayTextures) {
        glBindTexture(GL_TEXTURE_2D, textureNumber[5]);
        glEnable(GL_TEXTURE_2D);
        Manipulation.DisplayTexture(transparent);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    // Second group of transformations and rendering calls for Model 2: Buffalo
    glPushMatrix();
    glTranslatef(-75, -5, -125);
    glScalef(200, 200, 200);
    if (axisornot % 2 == 1)
        Manipulation2.DrawAxis();  // Press

    if (displayWireFrame)
        Manipulation2.DisplayWireFrame(transparent);
    if (displayFaces)
        Manipulation2.DisplayFaces(transparent);
    if (displayVertices)
        Manipulation2.DisplayVertices();
    if (DisplayTextures) {
        glBindTexture(GL_TEXTURE_2D, textureNumber[5]);
        glEnable(GL_TEXTURE_2D);
        Manipulation2.DisplayTexture(transparent);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    // Third group of transformations and rendering calls for Model 3: Radio
    glPushMatrix();
    glTranslatef(-135, -100, -165);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    glScalef(2, 2, 2);
    if (axisornot % 2 == 1)
        Manipulation3.DrawAxis();  // Press

    if (displayWireFrame)
        Manipulation3.DisplayWireFrame(transparent);
    if (displayFaces)
        Manipulation3.DisplayFaces(transparent);
    if (displayVertices)
        Manipulation3.DisplayVertices();
    if (DisplayTextures) {
        glBindTexture(GL_TEXTURE_2D, textureNumber[5]);
        glEnable(GL_TEXTURE_2D);
        Manipulation3.DisplayTexture(transparent);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    // Fourth group of transformations and rendering calls for Model 4: Ball Boy
    glPushMatrix();
    glTranslatef(-135, -190, -145);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    glScalef(60, 40, 40);
    if (axisornot % 2 == 1)
        Manipulation4.DrawAxis();  // Press

    if (displayWireFrame)
        Manipulation4.DisplayWireFrame(transparent);
    if (displayFaces)
        Manipulation4.DisplayFaces(transparent);
    if (displayVertices)
        Manipulation4.DisplayVertices();
    if (DisplayTextures) {
        glBindTexture(GL_TEXTURE_2D, textureNumber[5]);
        glEnable(GL_TEXTURE_2D);
        Manipulation4.DisplayTexture(transparent);
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();

    // Remaining rendering calls
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-size / 2.0f, -size / 2.0f, -size / 2.0f);
    DrawBox(); // background
    setupFog();
    glDisable(GL_TEXTURE_2D);
    // Planets
    glEnable(GL_TEXTURE_2D);
    glTranslatef(150, 100, 100);
    glScalef(1.3, 1.3, 1.3);
    drawSphere(10, 26, 26, 2);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D); // earth and moon
    glPushMatrix();
    glTranslatef(150, 200, 150);
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    drawSphere(20, 26, 26, 0);

    glTranslatef(50, 0, 0); // Translate to the right of the first sphere
    glRotatef(angle2, 0.0f, 1.0f, 0.0f); // Rotate around the y-axis
    float distance = 50.0f; // Distance from the first sphere
    float angleRadians = angle2 * 3.14159f / 180.0f; // Convert angle to radians
    float posX = distance * cos(angleRadians);
    float posZ = distance * sin(angleRadians);
    glTranslatef(posX, 0.0f, posZ); // Position in a circular motion around the first sphere
    drawSphere(10, 26, 26, 4);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glTranslatef(100, 100, 100);
    glScalef(1, 1, 1);
    drawSphere(10, 26, 26, 5);
    glDisable(GL_TEXTURE_2D);
    // Road signs
    glEnable(GL_TEXTURE_2D);
    glTranslatef(0, 35, 0);
    drawRoadSign(8);
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glTranslatef(250, 100, 10);
    glRotatef(180, 0.0f, 0.0f, 1.0f);
    drawRoadSign(9);
    glDisable(GL_TEXTURE_2D);
    // Tv
    glEnable(GL_TEXTURE_2D);
    glTranslatef(-30, 50, 50);
    glRotatef(0, 0.0f, 0.0f, 1.0f);
    drawTV(10.0, 7, 10);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glPopMatrix();


    angle += 0.5f;
    angle2 += 0.2f;
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

//-----------------My code----------------------
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / height, 1, 100);
}


//----------------------------------------------------
void viewing()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, focusX, focusY, focusZ, upX, upY, upZ);

}
void mySpecialFunc(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN  :
        rotateX += angleInc;
        break;
    case GLUT_KEY_UP    :
        rotateX -= angleInc;
        break;
    case GLUT_KEY_RIGHT :
        rotateY += angleInc;
        break;
    case GLUT_KEY_LEFT  :
        rotateY -= angleInc;
        break;
    case GLUT_KEY_HOME  :
        rotateX = 0.0, rotateY = 0.0, rotateZ = 0.0;
        posX = 0.0, posY = 0.0, posZ = 0.0;
        scaleX = 1.0, scaleY = 1.0, scaleZ = 1.0;
        break;
    case GLUT_KEY_F1    :
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    case GLUT_KEY_F2    :
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    }
    glutPostRedisplay();
}
void myKeyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 's': axisornot += 1; //On or Off the axis
                  break;
        case 'x': transX +=0.05; break;
        case 'X': transX -=0.05; break;
        case 'y': transY +=0.05; break;
        case 'Y': transY -=0.05; break;
        case 'z': transZ +=0.05; break;
        case 'Z': transZ -=0.05; break;
        case 'v':
        case 'V': displayVertices = true, displayFaces = false; displayWireFrame = false; DisplayTextures = false; break;
        case 'f':
        case 'F': displayVertices = false, displayFaces = true; displayWireFrame = false; DisplayTextures = false; break;
        case 'w':
        case 'W': displayVertices = false, displayFaces = false; displayWireFrame = true; DisplayTextures = false; break;
        case 't':
        case 'T': displayVertices = false, displayFaces = false; displayWireFrame = false; DisplayTextures = true; break;

    }

    glutPostRedisplay();
}
void myReshapeFunc(int width, int height)
{
    WindowWidth  = width;
    WindowHeight = height;
    glViewport(0, 0, width, height);
}
void myMotionFunc(int x, int y)
{
    y = WindowHeight - y;
    if(mousePanMode)
    {
        posX += (x - mouseX)*0.5;
        posY += (y - mouseY)*0.5;
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
    if(mouseZoomMode)
    {
        GLdouble inc = (mouseY - y)*0.005;
        scaleX += inc;
        scaleY += inc;
        scaleZ += inc;
        mouseY = y;
        glutPostRedisplay();
    }
    if(mouseRotationMode)
    {
        rotateX += (mouseY - y)*0.5;
        rotateY += (x - mouseX)*0.5;
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }

}
void myMouseFunc(int button, int state, int x, int y)
{
    y = WindowHeight - y;
    switch (button)
    {
    case GLUT_MIDDLE_BUTTON:
        if (state==GLUT_DOWN && !mousePanMode)
        {
            mouseX = x;
            mouseY = y;
            mousePanMode = true;
        }
        if (state==GLUT_UP &&  mousePanMode)
        {
            mousePanMode = false;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state==GLUT_DOWN && !mouseZoomMode)
        {
            mouseY = y;
            mouseZoomMode = true;
        }
        if (state==GLUT_UP && mouseZoomMode)
        {
            mouseZoomMode = false;
        }
        break;
    case GLUT_LEFT_BUTTON:
        if (state==GLUT_DOWN && !mouseRotationMode)
        {
            mouseX = x;
            mouseY = y;
            mouseRotationMode = true;
        }
        if (state==GLUT_UP &&  mouseRotationMode)
        {
            mouseRotationMode = false;
        }
        break;
    }
}

void switch_models(int index)
{
    string skeleton_filename;
    string points_filename[5];

    switch(index)
    {
    case 0:

        points_filename[0] = "data/plant.ply";
        points_filename[1] = "data/buffalo.ply";
        points_filename[2] = "data/Radio_clean.ply";
        points_filename[3] = "data/ball_boy.ply";
        eyeX=40, eyeY=40, eyeZ=20, focusX=0, focusY=0, focusZ=0, upX=0.0, upY=0.2, upZ=1;
        break;

    }
//-------------Model 1 ---------------
    cout << "Switched model to " << points_filename[0] << endl;
   Manipulation.read3DModel(points_filename[0].c_str());
//-------------Model 2 ---------------

    cout << "Switched model to " << points_filename[1] << endl;
   Manipulation2.read3DModel(points_filename[1].c_str());
//-------------Model 3 ---------------

    cout << "Switched model to " << points_filename[2] << endl;
   Manipulation3.read3DModel(points_filename[2].c_str());
//-------------Model 4 ---------------

    cout << "Switched model to " << points_filename[3] << endl;
   Manipulation4.read3DModel(points_filename[3].c_str());

}
void myInit()
{
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowPosition(300, 100); // Set top-left position
    glutInitWindowSize(WindowWidth, WindowHeight); //Set width and height
    glutCreateWindow("Model Manipulation");// Create display window


     switch_models(0);

    InitTransparent();

    viewing();
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    glEnable(GL_NORMALIZE);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutDisplayFunc(myDisplayFunc);  // Specify the display callback function
    glutReshapeFunc(myReshapeFunc);
    glutKeyboardFunc(myKeyboardFunc);
    glutSpecialFunc(mySpecialFunc);
    glutMouseFunc(myMouseFunc);
    glutMotionFunc(myMotionFunc);

    //------------Start of Texture Mapping code---------------------
    MyImageStruct  myImage = { 0, 0, 0 };
    char   *fileNames[] = { "textures/earthmab.bmp", "textures/background.bmp", "textures/venusmeb.bmp" ,"textures/jupeqb.bmp", "textures/moonb.bmp", "textures/marsb.bmp"
    ,"textures/radio/Radio_Base.bmp", "textures/tv/try.bmp", "textures/road_sign.bmp", "textures/road_sign2.bmp","textures/tv/tv_Screen.bmp"};


   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   glGenTextures(sizeof(fileNames)/ sizeof(fileNames[0]) , textureNumber);
   for (int j=0; j<sizeof(fileNames)/ sizeof(fileNames[0]) ; j++)
   {
    ReadBMP(fileNames[j], &myImage);
    //CropImageToPowerOf2( &myImage, 128, 128);
    glBindTexture(GL_TEXTURE_2D, textureNumber[j]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,                // defining a 2D texture
                 0,                            // level (not multi-resolution)
                 GL_RGBA,                      // format of OpenGL's texture
                 myImage.Width, myImage.Height,// dimensions of the image
                 0,                            // border
                 GL_RGB, GL_UNSIGNED_BYTE,     // format of image
                 myImage.Pixels);              // pixel data of image
    // Reclaim the memory used by this image
    free( myImage.Pixels );
    }
    //--------------End of Texture Mapping code-------------------
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);


    cout<<"------------------------------------------------------------"<<endl;
    cout<<"Instruction:"<<endl;
    cout<<"s - On or Off the Axis"
        <<"\nHome - to reset model"
        <<"\nw or W - to display model WireFrame"
        <<"\nv or V - to display model vertices"
        <<"\nf or F - to display model surfaces"
        <<"\nf or T - to display model texture"

        <<endl;

    cout<<"------------------------------------------------------------"<<endl;
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    myInit();
    glutMainLoop();
    return 0;
}
