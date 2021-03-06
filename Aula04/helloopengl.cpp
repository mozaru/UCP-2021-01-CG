#include "helloopengl.h"
#include<GL/gl.h>
#include<math.h>


HelloOpenGL::HelloOpenGL(QWidget *parent) : QOpenGLWidget(parent)
{

}

void desenharCirculo(double x0, double y0, double raio, bool borda=true, int qtdPontos=100)
{
   double ang,delta,x,y;
   glBegin(borda?GL_LINE_LOOP:GL_POLYGON);
        delta = 2*M_PI/qtdPontos;
        for(int i=0; i<qtdPontos;i++)
        {
            ang = i*delta;
            x = x0+raio*cos(ang);
            y = y0+raio*sin(ang);
            glVertex2d(x,y);
        }
   glEnd();
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
    int min = this->width()<this->height()?this->width():this->height();
    glViewport(0,0, min, min);

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


    desenharCirculo(0,0,0.3);

    desenharCirculo(0,0.7,0.3, true, 300);

    desenharCirculo(0,-0.7,0.3, true, 3);

    desenharCirculo(0.7,0,0.3, false);

    glPopMatrix();

    c =c + delta;
    if ( (c>=1 && delta>0) || (c<=0 && delta <0) )
        delta = -delta;
}
