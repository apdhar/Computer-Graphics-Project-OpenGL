#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <cmath>
#include<math.h>
#include "BmpLoader.h"

double windowHeight=800, windowWidth=600;
double eyeX=15.0, eyeY=200.0, eyeZ=20.0, refX = 15, refY=200,refZ=0;
float rotationAngle = 0.0;
float angle = 0.0f; //orbit
float rad_1 = 25.0f;
unsigned int ID;
GLboolean switchOne = false, switchTwo=false, switchThree=false;

float angle_mars = 0.0;
float angular_velocity_mars = 0.01;

float angle_erth = 0.0;
float angular_velocity_erth = 0.008;

float angle_ven = 0.0;
float angular_velocity_ven = 0.005;


float angle_4 = 0.0;
float angular_velocity_4 = 0.007;

float angle_5 = 0.0;
float angular_velocity_5 = 0.003;

float angle_6 = 0.0;
float angular_velocity_6 = 0.009;

static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};



static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void drawCube(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();
}



void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glutSolidSphere (3.0, 20, 16);
}



static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};

void drawpyramid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[PquadIndices[i][0]][0], v_pyramid[PquadIndices[i][0]][1], v_pyramid[PquadIndices[i][0]][2],
                    v_pyramid[PquadIndices[i][1]][0], v_pyramid[PquadIndices[i][1]][1], v_pyramid[PquadIndices[i][1]][2],
                    v_pyramid[PquadIndices[i][2]][0], v_pyramid[PquadIndices[i][2]][1], v_pyramid[PquadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}

void drawTexturedSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ,int x, GLfloat shine = 90) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, x); // Replace 2 with the actual texture ID

    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {ambX, ambY, ambZ, 1.0};
    GLfloat mat_diffuse[] = {difX, difY, difZ, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    for (int i = 0; i < 20; i++) {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= 16; j++) {
            for (int k = 0; k < 2; k++) {
                float u = static_cast<float>(j) / 16.0f;
                float v = static_cast<float>(i + k) / 20.0f;

                float theta = 2.0f * M_PI * u;
                float phi = M_PI * v;

                float x = 3.0f * sin(phi) * cos(theta);
                float y = 3.0f * sin(phi) * sin(theta);
                float z = 3.0f * cos(phi);

                glTexCoord2f(u, v);
                glVertex3f(x, y, z);

                u = static_cast<float>(j) / 16.0f;
                v = static_cast<float>(i + k + 1) / 20.0f;

                theta = 2.0f * M_PI * u;
                phi = M_PI * v;

                x = 3.0f * sin(phi) * cos(theta);
                y = 3.0f * sin(phi) * sin(theta);
                z = 3.0f * cos(phi);

                glTexCoord2f(u, v);
                glVertex3f(x, y, z);
            }
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}

void base(){

        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(-50,-0.5,-120);
    glScalef(50,0.2,70);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 15);
    glPushMatrix();
    glTranslatef(-50,-0.5,-120);
    glScalef(0.2,200,70);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 15);
    glPushMatrix();
    glTranslatef(100,-0.5,-120);
    glScalef(0.2,200,70);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 15);
    glPushMatrix();
    glTranslatef(-50,0,-120);
    glScalef(100,200,0.2);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 15);
    glPushMatrix();
    glTranslatef(-50,600,-120);
    glScalef(50,0.2,70);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void entrance(){

    //left arch
    glPushMatrix();
    glTranslatef(5,0,20);
    glScalef(0.3,5,8);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();

    //right arch
    glPushMatrix();
    glTranslatef(16.1,0,20);
    glScalef(0.3,5,8);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();

    //celling arch
    glPushMatrix();
    glTranslatef(5,15,20);
    glScalef(4,3,8);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();

    //floor arch
    glPushMatrix();
    glTranslatef(5,0,20);
    glScalef(4,0.2,8);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();

    //celling gray
    glPushMatrix();
    glTranslatef(6.5,16.5,20.5);
    glScalef(3,2,8);
    drawCube(0.6, 0.6, 0.5,0.6, 0.6, 0.5);
    glPopMatrix();

                glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 16);
    glPushMatrix();
    glTranslatef(5,85,30);
    glScalef(20,15,2);
    drawCube(0.6, 0.6, 0.6,0.6, 0.6, 0.6);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);


                glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 17);
        glPushMatrix();
    glTranslatef(85,85,30);
    glScalef(22,15,2);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
            glDisable(GL_TEXTURE_2D);



}

void building(){

        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    //front wall left
    glPushMatrix();
    glTranslatef(0,0,20);
    glScalef(2,17,0.3);
    drawCube(0.6, 0.6, 0.5,0.6, 0.6, 0.5);
    glPopMatrix();

    //front wall right
    glPushMatrix();
    glTranslatef(16,0,20);
    glScalef(2,17,0.3);
    drawCube(0.6, 0.6, 0.5,0.6, 0.6, 0.5);
    glPopMatrix();

    //front wall center
    glPushMatrix();
    glTranslatef(5,45,20);
    glScalef(5.5,2,0.3);
    drawCube(0.6, 0.6, 0.5,0.6, 0.6, 0.5);
    glPopMatrix();


    //front wall center2
    glPushMatrix();
    glTranslatef(5,16,19.5);
    glScalef(5.5,11,0.3);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();

    //left wall center2
    glPushMatrix();
    glTranslatef(-16.5,0,20);
    glScalef(6,17,0.3);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();

    //right wall center2
    glPushMatrix();
    glTranslatef(22,0,20);
    glScalef(50.3,17,0.3);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
                        glDisable(GL_TEXTURE_2D);


    //floor
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 5);
    glPushMatrix();
    glTranslatef(-16,0,-70);//50
    glScalef(63,0.3,30);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    //roof
        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 5);
    glPushMatrix();
    glTranslatef(-16,50,-70);//50
    glScalef(63,0.3,30);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);



    //left wall
            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(-16.5,0,-70);//50
    glScalef(0.3,17,30);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
                glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);
    glPushMatrix();
    glTranslatef(-16,6,-62);//50
    glScalef(0.5,13,17);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //right wall
                glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(172.0,0,-70);//50
    glScalef(0.3,17,30);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    glTranslatef(171.5,6,-62);//50
    glScalef(0.5,13,17);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //back wall
                    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(-16,0,-70);//50
    glScalef(63,17,0.3);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
                        glDisable(GL_TEXTURE_2D);


    //back wall gray
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
    glPushMatrix();
    glTranslatef(0,6,-69);//50
    glScalef(50,13,0.5);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void tree(){
    //glColor3f(0.4, 0.1, 0.0);
    glPushMatrix();
    glTranslatef(0.0,-0.5,0.0);
    glScalef(0.22, 0.3, 0.20);//(0.04, 0.6, 0.0001);
    drawCube(0.4, 0.1, 0.0,0.4, 0.1, 0.0);
    glPopMatrix();

           //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(0.3,0.2,0.3);
       glScalef(0.03, 0.32, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

           //glColor3f(0.6, 0.9, 0.2);
    glPushMatrix();
    glTranslatef(0.2,0.8,0.2);
    glScalef(0.1, 0.05, 0.1);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.9, 0.2,0.6, 0.9, 0.2);
    glPopMatrix();

               //glColor3f(0.6, 0.8, 0.1);
    glPushMatrix();
    glTranslatef(0.1,0.9,0.1);
    glScalef(0.15, 0.2, 0.15);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.8, 0.1,0.6, 0.8, 0.1);
    glPopMatrix();

               //glColor3f(0.6, 0.9, 0.2);
    glPushMatrix();
    glTranslatef(0.2,1.4,0.2);
    glScalef(0.1, 0.08, 0.1);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.9, 0.2,0.6, 0.9, 0.2);
    glPopMatrix();
}


void floor2(){
        //left wall
                    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(-16.5,40,-70);//50
    glScalef(0.3,19,30);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);
    glPushMatrix();
    glTranslatef(-16,6,-62);//50
    glScalef(0.5,11,17);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //right wall
                        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(172.0,40,-70);//50
    glScalef(0.3,19,30);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 4);
    glPushMatrix();
    glTranslatef(171.5,6,-62);//50
    glScalef(0.5,11,17);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //back wall
                            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(-16,40,-70);//50
    glScalef(63,19,0.3);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
        //back wall gray
    glPushMatrix();
    glTranslatef(0,55,-69);//50
    glScalef(50,11,0.5);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

        //roof
                glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 5);
    glPushMatrix();
    glTranslatef(-16,96,-70);//50
    glScalef(63,0.3,30);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //front wall
        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(-16,40,20);//50
    glScalef(63,19,0.3);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);




}


void basement(){
        //left wall
                    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(-16.5,40,-70);//50
    glScalef(0.3,19,30);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);



    //right wall
                        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(172.0,40,-70);//50
    glScalef(0.3,19,30);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);



    //back wall
                            glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(-16,40,-70);//50
    glScalef(63,19,0.3);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
        //back wall gray
    glPushMatrix();
    glTranslatef(0,55,-69);//50
    glScalef(50,11,0.5);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

        //roof
                glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 5);
    glPushMatrix();
    glTranslatef(-16,96,-70);//50
    glScalef(63,0.3,30);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //front wall
        glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(-16,40,20);//50
    glScalef(63,19,0.3);
    drawCube(1.0, 1.0, 1.1,1.0, 1.0, 1.0);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);

                glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 5);
    glPushMatrix();
    glTranslatef(-16,40,-70);//50
    glScalef(63,0.3,30);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void rover(){

    glPushMatrix();
    glTranslatef(10,11,-40);
    glScalef(3.5,1.6,3);
    drawCube(0.6,0.7,0.9,0.6,0.7,0.9);
    glPopMatrix();

    //leg1
    glPushMatrix();
    glTranslatef(10,5.5,-40.5);
    glScalef(0.3,3,0.3);
    drawCube(0.6,0.7,0.9,0.6,0.7,0.9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.3,5.5,-40);
    glScalef(0.4,0.4,0.4);
    drawSphere(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //leg2
    glPushMatrix();
    glTranslatef(15,5.5,-40.5);
    glScalef(0.3,3,0.3);
    drawCube(0.6,0.7,0.9,0.6,0.7,0.9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(15.3,5.5,-40);
    glScalef(0.4,0.4,0.4);
    drawSphere(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();


    //leg3
    glPushMatrix();
    glTranslatef(19,5.5,-40.5);
    glScalef(0.3,3,0.3);
    drawCube(0.6,0.7,0.9,0.6,0.7,0.9);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(19.3,5.5,-40);
    glScalef(0.4,0.4,0.4);
    drawSphere(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();


    //leg2-1
    glPushMatrix();
    glTranslatef(10,5.5,-31.5);
    glScalef(0.3,3,0.3);
    drawCube(0.6,0.7,0.9,0.6,0.7,0.9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10.3,5.5,-31);
    glScalef(0.4,0.4,0.4);
    drawSphere(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //leg2-2
    glPushMatrix();
    glTranslatef(15,5.5,-31.5);
    glScalef(0.3,3,0.3);
    drawCube(0.6,0.7,0.9,0.6,0.7,0.9);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(15.3,5.5,-31);
    glScalef(0.4,0.4,0.4);
    drawSphere(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();


    //leg2-3
    glPushMatrix();
    glTranslatef(19,5.5,-31.5);
    glScalef(0.3,3,0.3);
    drawCube(0.6,0.7,0.9,0.6,0.7,0.9);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(19.3,5.5,-31);
    glScalef(0.4,0.4,0.4);
    drawSphere(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19.5,13,-35.5);
    glScalef(0.3,3,0.3);
    drawCube(0.6,0.7,0.9,0.6,0.7,0.9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19,22,-38.5);
    glScalef(0.5,1.0,2);
    drawCube(0.6,0.7,0.9,0.6,0.7,0.9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19.8,22.5,-37.8);
    glScalef(0.3,0.7,1.6);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();



}

void satelight(){
    glPushMatrix();
    glTranslatef(86,18,-40);
    glScalef(3,8,2);
    drawCube(0.3,0.4,0.5,0.3,0.4,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(86,10,-42);
    glScalef(3,1.2,3);
    drawCube(0.5,0.6,0.5,0.5,0.6,0.5);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(90.5,31,-36);
    glScalef(1,1,1);
    drawSphere(0.5,0.6,0.8,0.5,0.6,0.8);
    glPopMatrix();



    glPushMatrix();
    glTranslatef(88.5,11,-39);
    glScalef(1.5,7,1);
    drawCube(0.3,0.4,0.5,0.3,0.4,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(89,28,-39);
    glScalef(8,3,0.5);
    drawCube(0.3,0.4,0.5,0.3,0.4,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(90.5,29,-40);
    glScalef(7,2,1);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(69,28,-39);
    glScalef(8,3,0.5);
    drawCube(0.3,0.4,0.5,0.3,0.4,0.5);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(71.5,29,-40);
    glScalef(7,2,1);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();
}

void stage (){
    //stage
    glPushMatrix();
    glTranslatef(0,2,-50);
    glScalef(10,0.7,10);
    drawCube(1.0,1.0,1.0,1.0,1.0,1.0);
    glPopMatrix();

    //leg1
    glPushMatrix();
    glTranslatef(0,4,-21);
    glScalef(0.3,4.5,0.3);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //leg2
    glPushMatrix();
    glTranslatef(0,4,-50);
    glScalef(0.3,4.5,0.3);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();


    //leg3
    glPushMatrix();
    glTranslatef(29,4,-21);
    glScalef(0.3,4.5,0.3);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //leg4
    glPushMatrix();
    glTranslatef(29,4,-50);
    glScalef(0.3,4.5,0.3);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //bar
    glPushMatrix();
    glTranslatef(0,17.5,-21);
    glScalef(9.9,0.3,0.3);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //bar2
    glPushMatrix();
    glTranslatef(0,17.5,-50);
    glScalef(0.3,0.3,9.9);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //bar3
    glPushMatrix();
    glTranslatef(0,17.5,-50);
    glScalef(9.9,0.3,0.3);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //bar4
    glPushMatrix();
    glTranslatef(29,17.5,-50);
    glScalef(0.3,0.3,9.9);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();
}

void rocket(){

    glPushMatrix();
    glTranslatef(30,0,-20);//50

    glTranslatef(38,0,-10);
    glPushMatrix();
    glTranslatef(0,110,-30);
    glScalef(18,4,8);
    drawCube(1.0,1.0,1.0,1.0,1.0,1.0);
    glPopMatrix();

    //window1
    glPushMatrix();
    glTranslatef(25,117,-7);
    glScalef(0.8,0.8,0.8);
    drawSphere(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //window2
    glPushMatrix();
    glTranslatef(35,117,-7);
    glScalef(0.8,0.8,0.8);
    drawSphere(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //window21
    glPushMatrix();
    glTranslatef(25,117,-30);
    glScalef(0.8,0.8,0.8);
    drawSphere(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    //window22
    glPushMatrix();
    glTranslatef(35,117,-30);
    glScalef(0.8,0.8,0.8);
    drawSphere(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,106,-30);
    glScalef(23,2.5,8);
    drawCube(1.0,1.0,1.0,1.0,1.0,1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,99,-30);
    glScalef(23,2.5,8);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(52,115,-28);
    glScalef(1,2,7);
    drawCube(0.0,0.5,0.9,0.0,0.5,0.9);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(69,113,-31);
    glScalef(3,6.5,12.5);
    glRotatef(-90,0,0,1);
    drawpyramid(0.5,0.5,0.5,0.5,0.5,0.5);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(2,120,-28);
    glScalef(3,4,0.5);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(2,120,-10);
    glScalef(3,4,0.5);
    drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
    glPopMatrix();
    glPopMatrix();
}

void planet(int x){
    glPushMatrix();
    glTranslatef(110,175,-20);
    glScalef(4,4,4);
    drawTexturedSphere(1.0,1.0,1.0,1.0,1.0,1.0,x);
    glPopMatrix();
}






void light0()
{
        glPushMatrix();
    //top left farthest corner
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 0.5, 0.5, 0.5, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 60, 70.0, -10.0, 1.0 };



    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    glPopMatrix();

}


void light1()
{
        glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 0.5, 0.5, 0.5, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 60, 220.0, -10.0, 1.0 };


    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);

    glPopMatrix();

}


void light2()
{
        glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 0.5, 0.5, 0.5, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0, -30.0, -30.0, 1.0 };


    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);

    GLfloat light_direction[] = { 0.0, 0.0, -1.0 };  // Spotlight direction
    GLfloat light_cutoff = 75.0;  // Spotlight cutoff angle

    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_direction);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, light_cutoff);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);  // Adjust the spotlight exponent as needed

    glPopMatrix();

}

void updateAngles() {
    angle_mars += angular_velocity_mars;
    angle_erth += angular_velocity_erth;
    angle_ven += angular_velocity_ven;
    angle_4 += angular_velocity_4;
    angle_5 += angular_velocity_5;
}

void drawVerticalTorus(float centerX, float centerY, float centerZ, float radius, float thickness) {
    const int numSegments = 100;

    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f); // Set color to black
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate the torus to be vertical
    glutWireTorus(thickness, radius, numSegments, numSegments);
    glPopMatrix();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(90,1,1,1000);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  0,1,0); //7,2,15, 0,0,0, 0,1,0
        updateAngles();


    glPushMatrix();
    glScalef(3,1,3);
    glTranslatef(0,0,-20);
    base();
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1.8,1.2);
    entrance();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0,1.5,2.0);
    building();
    glPopMatrix();

    glPushMatrix();
    glScalef(1.0,1.5,2.0);
    floor2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,80,0);
    glScalef(1.0,1.5,2.0);
    floor2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,160,0);
    glScalef(1.0,1.5,2.0);
    floor2();
    glPopMatrix();



    glPushMatrix();
    glTranslatef(60,70,-10);
    glScalef(0.2,0.2,0.2);
    drawSphere(1,1,0.2,1,1,0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(60,220,-10);
    glScalef(0.2,0.2,0.2);
    drawSphere(1,1,0.2,1,1,0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,-40);
    /////////////////
    float centerX = 15.0; // Adjust this based on the actual center of your rover
    float centerY = 13.0; // Adjust this based on the actual center of your rover
    float centerZ = -35.75; // Adjust this based on the actual center of your rover
    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(rotationAngle, 0.0, 1.0, 0.0);
    glTranslatef(-centerX, -centerY, -centerZ);
    rover();
    glPopMatrix();

    glPushMatrix();
    stage();
    glPopMatrix();

    float centerX_sat = 87.0; // Adjust this based on the actual center of your rover
    float centerY_sat = 18.0; // Adjust this based on the actual center of your rover
    float centerZ_sat = -40.0; // Adjust this based on the actual center of your rover
    glPushMatrix();
    glTranslatef(centerX_sat, centerY_sat, centerZ_sat);
    glRotatef(rotationAngle, 0.0, 1.0, 0.0);
    glTranslatef(-centerX_sat, -centerY_sat, -centerZ_sat);
    satelight();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(70,0,0);
    stage();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-25,0,0);
    float centerX_roc = 68.0; // Adjust this based on the actual center of your rover
    float centerY_roc = 105.0; // Adjust this based on the actual center of your rover
    float centerZ_roc = -42.0; // Adjust this based on the actual center of your rover
    glPushMatrix();
    glTranslatef(centerX_roc, centerY_roc, centerZ_roc);
    glRotatef(rotationAngle, 1.0, 0.0, 0.0);
    glTranslatef(-centerX_roc, -centerY_roc, -centerZ_roc);
    rocket();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(65,75,0);
    glScalef(2.6,1,1);
    stage();
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-25,0,-30);
    glPushMatrix();
    planet(9);
    glPopMatrix();

    float centerX_is = 71.0; // Adjust this based on the actual center of your rover
    float centerY_is = 168.0; // Adjust this based on the actual center of your rover
    float centerZ_is = -2.0;
    float orbitRadius = 18.0;
    float x = centerX_is + orbitRadius * cos(angle); //orbit code
    float y = centerY_is; //orbit code
    float z = centerZ_is + orbitRadius * sin(angle); //orbit code
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(0.4,0.4,0.4);
    satelight();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(80,145,20);
    glScalef(1.8,1,1);
    stage();
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,0,-20);
    //1
    glPushMatrix();
    glTranslatef(-90,120,-25);
    glScalef(0.8,0.8,0.8);
    planet(7);
    glPopMatrix();

    //2
    glPushMatrix();
    glTranslatef(-60,120,-25);
    glScalef(0.8,0.8,0.8);
    planet(8);
    glPopMatrix();


    //3
    glPushMatrix();
    glTranslatef(-30,120,-25);
    glScalef(0.8,0.8,0.8);
    planet(9);
    glPopMatrix();


    //4
    glPushMatrix();
    glTranslatef(-0,120,-25);
    glScalef(0.8,0.8,0.8);
    planet(10);
    glPopMatrix();


    //5
    glPushMatrix();
    glTranslatef(30,120,-25);
    glScalef(0.8,0.8,0.8);
    planet(11);
    glPopMatrix();


    //6
    glPushMatrix();
    glTranslatef(60,120,-25);
    glScalef(0.8,0.8,0.8);
    planet(12);
    glPopMatrix();




    glPushMatrix();
    glTranslatef(-3,223,-10);
    glScalef(5.5,1,0.7);
    stage();
    glPopMatrix();
    glPopMatrix();

    //1st floor trees
    glPushMatrix();
    glTranslatef(-10,6,-60);
    glScalef(8,8,8);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(60,6,-60);
    glScalef(8,8,8);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(120,6,-60);
    glScalef(8,8,8);
    tree();
    glPopMatrix();

    //2nd floor trees
    glPushMatrix();
    glTranslatef(-10,82,-60);
    glScalef(8,8,8);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(60,82,-60);
    glScalef(8,8,8);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(120,82,-60);
    glScalef(8,8,8);
    tree();
    glPopMatrix();

    //3rd floor trees
    glPushMatrix();
    glTranslatef(30,150,-60);
    glScalef(8,8,8);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(120,150,-60);
    glScalef(8,8,8);
    tree();
    glPopMatrix();

    //basement
    glPushMatrix();
    glTranslatef(-45,-170,0);
    glScalef(2.0,1.5,3.0);
    basement();
    glPopMatrix();


    glPushMatrix();
    glTranslated(85,-30,-50);
    drawSphere(1,1,0.2,1,1,0.2);
    glPopMatrix();


    glPushMatrix();
    glTranslated(-25,-260,-30);
    planet(6);
    glPopMatrix();

    float centerX_mar = 42.0; // Adjust this based on the actual center of your rover
    float centerY_mar = -155.0; // Adjust this based on the actual center of your rover
    float centerZ_mar = -45.0;
        float rad_1 = 25.0f;
    glPushMatrix();
    glTranslatef(42,70,-5);
        drawVerticalTorus(centerX_mar, centerY_mar, centerZ_mar, rad_1, 0.1);
        glPopMatrix();
    float x_mars = centerX_mar + rad_1 * cos(angle_mars); //orbit code
    float y_mars = centerY_mar; //orbit code
    float z_mars = centerZ_mar + rad_1 * sin(angle_mars); //orbit code
    glPushMatrix();
    glTranslatef(x_mars,y_mars,z_mars);
    glScalef(0.4,0.4,0.4);
    planet(7);
    glPopMatrix();

    float centerX_erth = 42.0; // Adjust this based on the actual center of your rover
    float centerY_erth = -155.0; // Adjust this based on the actual center of your rover
    float centerZ_erth = -45.0;
    float rad_2 = 45.0f;
        glPushMatrix();
    glTranslatef(42,70,-5);
        drawVerticalTorus(centerX_mar, centerY_mar, centerZ_mar, rad_2, 0.1);
        glPopMatrix();
    float x_erth = centerX_erth + rad_2 * cos(angle_erth); //orbit code
    float y_erth = centerY_erth; //orbit code
    float z_erth = centerZ_erth + rad_2 * sin(angle_erth); //orbit code
    glPushMatrix();
    glTranslatef(x_erth,y_erth,z_erth);
    glScalef(0.4,0.4,0.4);
    planet(8);
    glPopMatrix();

    float centerX_ven = 42.0; // Adjust this based on the actual center of your rover
    float centerY_ven = -155.0; // Adjust this based on the actual center of your rover
    float centerZ_ven = -45.0;
    float rad_3 = 65.0f;
            glPushMatrix();
    glTranslatef(42,70,-5);
        drawVerticalTorus(centerX_mar, centerY_mar, centerZ_mar, rad_3, 0.1);
        glPopMatrix();
    float x_ven = centerX_ven + rad_3 * cos(angle_ven); //orbit code
    float y_ven = centerY_ven; //orbit code
    float z_ven = centerZ_ven + rad_3 * sin(angle_ven); //orbit code
    glPushMatrix();
    glTranslatef(x_ven,y_ven,z_ven);
    glScalef(0.4,0.4,0.4);
    planet(9);
    glPopMatrix();

        float centerX_4 = 42.0; // Adjust this based on the actual center of your rover
    float centerY_4 = -155.0; // Adjust this based on the actual center of your rover
    float centerZ_4 = -45.0;
    float rad_4 = 85.0f;
            glPushMatrix();
    glTranslatef(42,70,-5);
        drawVerticalTorus(centerX_4, centerY_4, centerZ_4, rad_4, 0.1);
        glPopMatrix();
    float x_4 = centerX_4 + rad_4 * cos(angle_4); //orbit code
    float y_4 = centerY_4; //orbit code
    float z_4 = centerZ_4 + rad_4 * sin(angle_4); //orbit code
    glPushMatrix();
    glTranslatef(x_4,y_4,z_4);
    glScalef(0.4,0.4,0.4);
    planet(10);
    glPopMatrix();

            float centerX_5 = 42.0; // Adjust this based on the actual center of your rover
    float centerY_5 = -155.0; // Adjust this based on the actual center of your rover
    float centerZ_5 = -45.0;
    float rad_5 = 105.0f;
            glPushMatrix();
    glTranslatef(42,70,-5);
        drawVerticalTorus(centerX_5, centerY_5, centerZ_5, rad_5, 0.1);
        glPopMatrix();
    float x_5 = centerX_5 + rad_5 * cos(angle_5); //orbit code
    float y_5 = centerY_5; //orbit code
    float z_5 = centerZ_5 + rad_5 * sin(angle_5); //orbit code
    glPushMatrix();
    glTranslatef(x_5,y_5,z_5);
    glScalef(0.4,0.4,0.4);
    planet(11);
    glPopMatrix();




    glPopMatrix();

    glutSwapBuffers();
}


void update(int value) {

        angle += 0.01f;  // Adjust the speed of the orbit

    if (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    // Update the rotation angle
    rotationAngle += 0.5; // Adjust the rotation speed as needed

    // Ensure the rotation angle stays within 360 degrees
    if (rotationAngle > 360.0) {
        rotationAngle -= 360.0;
    }

    // Redraw the scene
    glutPostRedisplay();

    // Set up the next update
    glutTimerFunc(16, update, 0); // Adjust the timer interval as needed
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case 'w': // move eye point upwards along Y axis
            eyeY+=1.0;
            refY+=1.0;
            break;
        case 's': // move eye point downwards along Y axis
            eyeY-=1.0;
            refY-=1.0;
            break;
        case 'a': // move eye point left along X axis
            eyeX-=1.0;
            refX-=1.0;
            break;
        case 'd': // move eye point right along X axis
            eyeX+=1.0;
            refX+=1.0;
            break;
        case 'o':  //zoom out
            eyeZ+=1;
            refZ+=1;
            break;
        case 'i': //zoom in
            eyeZ-=1;
            refZ-=1;
            break;
        case 'q': //back to default eye point and ref point
                eyeX=0.0; eyeY=2.0; eyeZ=40.0;
                refX=0.0; refY=0.0; refZ=0.0;
            break;
        case 'j': // move ref point upwards along Y axis
            refY+=1.0;
            break;
        case 'n': // move ref point downwards along Y axis
            refY-=1.0;
            break;
        case 'b': // move ref point left along X axis
            refX-=1.0;
            break;
        case 'm': // move eye point right along X axis
            refX+=1.0;
            break;
        case 'k':  //move ref point away from screen/ along z axis
            refZ+=1;
            break;
        case 'l': //move ref point towards screen/ along z axis
            refZ-=1;
            break;
        case '1': //back to default eye point and ref point
                eyeX=35.0; eyeY=20.0; eyeZ=20.0;
                refX=35.0; refY=20.0; refZ=0.0;
            break;
        case '2': //back to default eye point and ref point
                eyeX=105.0; eyeY=110.0; eyeZ=20.0;
                refX=105.0; refY=110.0; refZ=0.0;
            break;
        case '3': //back to default eye point and ref point
                eyeX=125.0; eyeY=160.0; eyeZ=20.0;
                refX=125.0; refY=160.0; refZ=0.0;
            break;
        case '4': //back to default eye point and ref point
                eyeX=25.0; eyeY=260.0; eyeZ=20.0;
                refX=25.0; refY=260.0; refZ=0.0;
            break;
        case '5': //back to default eye point and ref point
                eyeX=-15.0; eyeY=-80.0; eyeZ=20.0;
                refX=-15.0; refY=-80.0; refZ=0.0;
            break;
        case '6': //to turn on and off light one
            if(switchThree == false)
            {
                switchThree = true;
                glEnable( GL_LIGHT2); break;
            }
            else if(switchThree == true)
            {
                switchThree = false;
                 glDisable( GL_LIGHT2); break;
            }
        case '7': //to turn on and off light one
            if(switchOne == false)
            {
                switchOne = true;
                glEnable( GL_LIGHT0); break;
            }
            else if(switchOne == true)
            {
                switchOne = false;
                 glDisable( GL_LIGHT0); break;
            }
        case '8': //to turn on and off light two
            if(switchTwo == false)
            {
                switchTwo = true;
                glEnable( GL_LIGHT1); break;
            }
            else if(switchTwo == true)
            {
                switchTwo = false;
                glDisable( GL_LIGHT1); break;
            }
        case 27:    // Escape key
            exit(1);
    }

    glutPostRedisplay();
}

void fullScreen(int w, int h)
{
    //Prevent a divide by zero, when window is too short;you cant make a window of zero width.
    if (h == 0)
        h = 1;
    float ratio = (GLfloat)w / (GLfloat)h;         //Calculate aspect ratio of the window

    //Set the perspective coordinate system
    glMatrixMode(GL_PROJECTION);                   //Use the Projection Matrix
    glLoadIdentity();                              //Reset Matrix

    glViewport(0, 0, w, h);                        //Set the viewport to be the entire window
    gluPerspective(120, ratio, 1, 3000);             //Set the correct perspective.
    //glFrustum(-2.5,2.5,-2.5,2.5, ratio, 200);
    glMatrixMode(GL_MODELVIEW);                    //Get Back to the Modelview
}

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);

    std::cout<<"To move Eye point:"<< std::endl;
    std::cout<<"w: up"<<std::endl;
    std::cout<<"s: down"<<std::endl;
    std::cout<<"a: left"<<std::endl;
    std::cout<<"d: right"<<std::endl;
    std::cout<<"i: zoom in"<<std::endl;
    std::cout<<"o: zoom out"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"To move Camera point:"<< std::endl;
    std::cout<<"j: up"<<std::endl;
    std::cout<<"n: down"<<std::endl;
    std::cout<<"b: left"<<std::endl;
    std::cout<<"m: right"<<std::endl;
    std::cout<<"l: move nearer"<<std::endl;
    std::cout<<"k: move far"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"Press q to move to default position"<<std::endl;

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Test Prototype");


    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\wall.bmp");//1
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\space.bmp");//2
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\gal10.bmp");//3
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\gal11.bmp");//4
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\floor.bmp");//5
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\sun1.bmp");//6
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\mercury.bmp");//7
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\venus.bmp");//8
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\earth.bmp");//9
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\mars.bmp");//10
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\saturn.bmp");//11
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\neptune.bmp");//12
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\air.bmp");//13
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\grass.bmp");//14
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\sky.bmp");//15
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\nasa.bmp");//16
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\cgip\\nasa\\bmp\\flag.bmp");//17


    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable( GL_LIGHT0);
    glEnable( GL_LIGHT1);
    glEnable( GL_LIGHT2);
    light0();
    light1();
    light2();


    glutReshapeFunc(fullScreen);
    glutDisplayFunc(display);
    glutKeyboardFunc(myKeyboardFunc);
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    return 0;
}
