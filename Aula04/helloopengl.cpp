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

double GrauToRad(double ang)
{
    return ang/360.0f*2*M_PI;
}

void desenharArco(double x0, double y0, double raio, double ang0, double ang1, int qtdPontos=100)
{
   double ang,delta,x,y;
   ang0 = GrauToRad(ang0);
   ang1 = GrauToRad(ang1);
   //glBegin(GL_LINE_STRIP);
    delta = 2*M_PI/qtdPontos;
    if (ang0<ang1)
        for(ang=ang0; ang<=ang1; ang=ang+delta)
        {
            x = x0+raio*cos(ang);
            y = y0+raio*sin(ang);
            glVertex2d(x,y);
        }
    else
        for(ang=ang0; ang>=ang1; ang=ang-delta)
        {
            x = x0+raio*cos(ang);
            y = y0+raio*sin(ang);
            glVertex2d(x,y);
        }
    x = x0+raio*cos(ang1);
    y = y0+raio*sin(ang1);
    glVertex2d(x,y);

    //glEnd();
}

void desenharToro2D(double x, double y, double ang0, double ang1, double r0, double r1)
{
    const int GAMBI = 5;
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);

    // set stencil buffer to invert value on draw, 0 to 1 and 1 to 0
    glStencilFunc(GL_ALWAYS, 0, 1);
    glStencilOp(GL_INVERT, GL_INVERT, GL_INVERT);

    // disable writing to color buffer
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glBegin(GL_TRIANGLE_FAN);
    desenharArco(x, y, r0, ang0, ang1, 300);
    desenharArco(x, y, r1, ang1-GAMBI, ang0+GAMBI, 300);
    glEnd();

    // set stencil buffer to only keep pixels when value in buffer is 1
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    // enable color again
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glBegin(GL_TRIANGLE_FAN);
    desenharArco(x, y, r0, ang0, ang1, 300);
    desenharArco(x, y, r1, ang1-GAMBI, ang0+GAMBI, 300);
    glEnd();
    glDisable(GL_STENCIL_TEST);
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


    glColor3b(0, 0, 127);
    desenharCirculo(0.7,0,0.3, false);

    glLineWidth(2);
    glColor3b(127, 0, 127);
    glPointSize(1);
//       for(double r=0.4; r>=0.35; r=r-0.01)
//            desenharArco(0.8, -0.3, r, 45, 155, 300);

    desenharToro2D(0.6,-0.35, 112, 37, 0.5, 0.45);
    glPopMatrix();

    c =c + delta;
    if ( (c>=1 && delta>0) || (c<=0 && delta <0) )
        delta = -delta;
}
