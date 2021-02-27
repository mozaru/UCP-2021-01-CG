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
    //glViewport(0,0, this->width(), this->height());

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
      glColor3f(c, 0.0f, 0.0f);
      glVertex2f(-1.0f,-1.0f);

      glColor3f(0.0f, c, 0.0f);
      glVertex2f( 1.0f,-1.0f);

      glColor3f(0.0f, 0.0f, c);
      glVertex2f( 1.0f,1.0f);

      glColor3f(c, c, 0.0f);
      glVertex2f(-1.0f,0.0f);
    glEnd();
    c =c + delta;
    if ( (c>=1 && delta>0) || (c<=0 && delta <0) )
        delta = -delta;
}
