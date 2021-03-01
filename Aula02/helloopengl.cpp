#include "helloopengl.h"
#include<GL/gl.h>


HelloOpenGL::HelloOpenGL(QWidget *parent) : QOpenGLWidget(parent)
{

}


void HelloOpenGL::initializeGL()
{
    //QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    //glFuncs->glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    this->initializeOpenGLFunctions();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void HelloOpenGL::resizeGL(int width, int height)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
}

void HelloOpenGL::paintGL()
{
    static double c = 1;
    static double delta = 0.05;
    glViewport(0,0, this->width(), this->height());

    glPushMatrix();

    glColor3f(0.0f, 1.0f, 0.0f);
    //glColor3ub(0, 0, 255);
    //glColor3b(0, 0, 127);

    glPointSize(10);
    glBegin(GL_POINTS);
      glColor3f(0, 0, 1);
      glVertex2f(0,0);
    glEnd();


    glPushMatrix();
    glTranslatef(0.3f,0,0);
    glRotatef(90, 0,0,1); //angulo em graus
    glScalef(3,3,0);

    glLineWidth(5);
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
      //glColor3f(c, 0.0f, 0.0f);
      glVertex2f(-0.1f,-0.2f);

      //glColor3f(0.0f, c, 0.0f);
      glVertex2f( 0.1f,-0.2f);

      //glColor3f(0.0f, 0.0f, c);
      glVertex2f( 0.1f,0.2f);

      //glColor3f(c, c, 0.0f);
      glColor3b(0, 0, 127);
      glVertex2f(-0.1f,0.2f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f,0,0);
    glPointSize(5);
    glBegin(GL_POINTS);
      glColor3f(1, 0, 0);
      glVertex2f(0,0);
    glEnd();
    glPopMatrix();


    glPopMatrix();

    c =c + delta;
    if ( (c>=1 && delta>0) || (c<=0 && delta <0) )
        delta = -delta;
}
