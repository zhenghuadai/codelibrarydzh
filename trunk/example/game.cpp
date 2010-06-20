/*
 * Copyright (c) 1993-2003, Silicon Graphics, Inc.
 * All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright
 * notice and this permission notice appear in supporting documentation,
 * and that the name of Silicon Graphics, Inc. not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS" AND
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION, LOSS OF
 * PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD
 * PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE
 * OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor clauses
 * in the FAR or the DOD or NASA FAR Supplement.  Unpublished - rights
 * reserved under the copyright laws of the United States.
 *
 * Contractor/manufacturer is:
 *	Silicon Graphics, Inc.
 *	1500 Crittenden Lane
 *	Mountain View, CA  94043
 *	United State of America
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 *  teapots.c
 *  This program demonstrates lots of material properties.
 *  A single light source illuminates the objects.
 */
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

GLuint teapotList;
static GLfloat spin = 0.0;
static float eyeZ = 8.0;
static float eyeX = 0.0;
static float eyeY = 0.0;
const double LEFT = 0.0;
const double RIGHT= 16.0;
const double TOP = 16.0;
const double BOTTOM=16.0;

void spinDisplay(void)
{
   spin = spin + 2.0;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}

GLfloat random(GLfloat bottom, GLfloat top)
{
    GLfloat f = (1.0 * rand())/(1.0*RAND_MAX+1.0);
//    GLfloat f = drand48();
    f = f* (top - bottom) + bottom;
    return f;
}

/*
 * Initialize depth buffer, projection matrix, light source, and lighting
 * model.  Do not specify a material property here.
 */
void init(void)
{
   GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
   GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat position[] = {0.0, 3.0, 3.0, 0.0};

   GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
   GLfloat local_view[] = {0.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

   glFrontFace(GL_CW);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_AUTO_NORMAL);
   glEnable(GL_NORMALIZE);
   glEnable(GL_DEPTH_TEST); 
/*  be efficient--make teapot display list  */
   teapotList = glGenLists(1);
   glNewList (teapotList, GL_COMPILE);
   glutSolidTeapot(1.0);
   glEndList ();
}

/*
 * Move object into position.  Use 3rd through 12th 
 * parameters to specify the material property.  Draw a teapot.
 */
void renderTeapot(GLfloat x, GLfloat y, GLfloat z,
   GLfloat ambr, GLfloat ambg, GLfloat ambb,
   GLfloat difr, GLfloat difg, GLfloat difb,
   GLfloat specr, GLfloat specg, GLfloat specb, GLfloat shine)
{
   GLfloat mat[4];

   glPushMatrix();
   glTranslatef(x, y, z);
   glRotatef(spin, 0.0, 0.0, 1.0);
   mat[0] = ambr; mat[1] = ambg; mat[2] = ambb; mat[3] = 1.0;
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
   mat[0] = difr; mat[1] = difg; mat[2] = difb;
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
   mat[0] = specr; mat[1] = specg; mat[2] = specb;
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
   glMaterialf(GL_FRONT, GL_SHININESS, shine * 128.0);
   glCallList(teapotList);
   glPopMatrix();
}

/**
 *  First column:  emerald, jade, obsidian, pearl, ruby, turquoise
 *  2nd column:  brass, bronze, chrome, copper, gold, silver
 *  3rd column:  black, cyan, green, red, white, yellow plastic
 *  4th column:  black, cyan, green, red, white, yellow rubber
 */
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
   renderTeapot(random(-16.0, 16.0), 11.0, 0.0, 0.0, 0.05, 0.0, 0.4, 0.5, 0.4,
      0.04, 0.7, 0.04, .078125);
   renderTeapot(14.0, 6.0,  2.0, 0.05, 0.0, 0.0, 0.5, 0.4, 0.4,
      0.7, 0.04, 0.04, .078125);
   renderTeapot(14.0, 5.0, 0.0,  0.05, 0.05, 0.05, 0.5, 0.5, 0.5,
      0.7, 0.7, 0.7, .078125);
   renderTeapot(14.0, 2.0, 0.0,  0.05, 0.05, 0.0, 0.5, 0.5, 0.4,
      0.7, 0.7, 0.04, .078125);
   glFlush();
   glutSwapBuffers();
}


void resetProject(int w, int h)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
//      glFrustum(0.0, 16.0, 0.0, 16.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
      glOrtho(0.0, 16.0, 0.0, 16.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glFrustum(0.0, 16.0*(GLfloat)w/(GLfloat)h, 0.0, 16.0, -10.0, 10.0);
    gluLookAt(eyeX,eyeY,eyeZ,.0,.0,-100.0,.0,1.0,.0);
   glMatrixMode(GL_MODELVIEW);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glFrustum(0.0, 16.0, 0.0, 16.0*(GLfloat)h/(GLfloat)w, 5, 10.0);
//      glOrtho(0.0, 16.0, 0.0, 16.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glFrustum(0.0, 16.0*(GLfloat)w/(GLfloat)h, 0.0, 16.0, -10.0, 10.0);
    gluLookAt(eyeX,eyeY,eyeZ,.0,.0,-100.0,.0,1.0,.0);
   glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
         break;
      case GLUT_MIDDLE_BUTTON:
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
      case 'a':
         eyeX -= 0.2;
         if(eyeX<LEFT) eyeX = LEFT;
         break;
      case 'd':
         eyeX += 0.2;
         if(eyeX>RIGHT) eyeX = RIGHT;
         break;
      case 'w':
         eyeY +=0.2;
         if(eyeY > TOP) eyeY = TOP;
         break;
      case 's':
         eyeY -=0.2;
         if(eyeY <BOTTOM) eyeY = BOTTOM ;
         break;
      case 'q':
         eyeZ +=0.2;
         if(eyeZ > TOP) eyeZ = TOP;
         break;
      case 'e':
         eyeZ -=0.2;
         if(eyeZ > TOP) eyeZ = TOP;
         break;
      case 'r':
         eyeX =0.0;
         eyeY =0.0;
         break;
   }
   resetProject( 600, 600);
   glutPostRedisplay();
}

/*
 * Main Loop 
 */
int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(600, 600);
   glutInitWindowPosition(50,50);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutMouseFunc(mouse);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}
