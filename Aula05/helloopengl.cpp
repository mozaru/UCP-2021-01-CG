#include "helloopengl.h"
#include<GL/gl.h>
#include<math.h>

typedef struct
{
    double x,y;
} Ponto;

HelloOpenGL::HelloOpenGL(QWidget *parent) : QOpenGLWidget(parent)
{

}

void desenharCirculo(double raio, bool fill = false, int qtdPontos = 300)
{
   double ang,salto,x,y;
   const double _ANG_FINAL_ = 2*M_PI;

   glBegin(fill?GL_POLYGON : GL_LINE_LOOP);
        salto = 2*M_PI/qtdPontos;
        for(ang = 0; ang < _ANG_FINAL_; ang += salto)
        {
            x = raio*cos(ang);
            y = raio*sin(ang);
            glVertex2d(x,y);
        }
   glEnd();
}

void desenharM(double size = 1.0, bool fill = false)
{
    const Ponto Pontos[] = {
        {-0.54, -0.62},
        {-0.39,	1.00},
        {0.00, 0.45},
        {0.39, 1.00},
        {0.54, -0.62 }};
    glBegin(fill?GL_POLYGON : GL_LINE_STRIP);
         for(int i=0; i<5; i++)
             glVertex2d(Pontos[i].x * size,Pontos[i].y * size);
    glEnd();
}


void preencherW(double size = 1.0)
{
    const Ponto Pontos[] = {
        {-0.54, 0.62},
        {-0.39,	-1.00},
        {0.00, 0.45},
        {0.39, -1.00},
        {0.54, 0.62 }};

    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);

    // set stencil buffer to invert value on draw, 0 to 1 and 1 to 0
    glStencilFunc(GL_ALWAYS, 0, 1);
    glStencilOp(GL_INVERT, GL_INVERT, GL_INVERT);

    // disable writing to color buffer
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<5; i++)
        glVertex2d(Pontos[i].x * size,Pontos[i].y * size);
    glEnd();


    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    // enable color again
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glBegin(GL_TRIANGLE_FAN);
         for(int i=0; i<5; i++)
             glVertex2d(Pontos[i].x * size,Pontos[i].y * size);
    glEnd();
    glDisable(GL_STENCIL_TEST);
}


double GrauToRad(double ang)
{
    return ang/360.0f*2*M_PI;
}

void verticesArco(double raio, double ang0, double ang1, int qtdPontos=100)
{
   double ang,salto,x,y;
   ang0 = GrauToRad(ang0);
   ang1 = GrauToRad(ang1);
   ///glBegin(GL_LINE_STRIP);
    salto = 2*M_PI/qtdPontos;
    if (ang0<ang1)
        for(ang=ang0; ang<ang1; ang=ang+salto)
        {
            x = raio*cos(ang);
            y = raio*sin(ang);
            glVertex2d(x,y);
        }
    else
        for(ang=ang0; ang>ang1; ang=ang-salto)
        {
            x = raio*cos(ang);
            y = raio*sin(ang);
            glVertex2d(x,y);
        }
    x = raio*cos(ang1);
    y = raio*sin(ang1);
    glVertex2d(x,y);

   //glEnd();
}

void desenharToro2D(double ang0, double ang1, double r0, double r1)
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
    verticesArco( r0, ang0, ang1, 300);
    verticesArco(r1, ang1-GAMBI, ang0+GAMBI, 300);
    glEnd();

    // set stencil buffer to only keep pixels when value in buffer is 1
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

    // enable color again
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glBegin(GL_TRIANGLE_FAN);
    verticesArco(r0, ang0, ang1, 300);
    verticesArco(r1, ang1-GAMBI, ang0+GAMBI, 300);
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
    int min = this->width()<this->height() ? this->width():this->height();
    glViewport((this->width()-min)/2, (this->height()-min)/2, min, min);

    glPushMatrix();


    glLineWidth(5);

    glColor3f(0.0f, 0.7f, 0.0f);
    desenharCirculo(0.9, true);

    glColor3f(0.0f, 0.0f, 0.0f);
    desenharCirculo(0.9);


    glPushMatrix();
    glTranslated(0.4,0.5,0);
    glColor3f(1.0f, 1.0f, 0.0f);
    desenharCirculo(0.05, true);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.5,0.3,0);
    glColor3f(1.0f, 1.0f, 0.0f);
    desenharCirculo(0.05, true);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.3,0.35,0);
    glColor3f(1.0f, 1.0f, 0.0f);
    desenharCirculo(0.08, true);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.2,0,0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2);
    desenharM(0.6, true);
    glPopMatrix();


    glPushMatrix();
    glTranslated(0.2,-0.2,0);
    glColor3f(0.3f, 0.3f, 1.0f);
    preencherW(0.5);
    glPopMatrix();


    glPushMatrix();
    glTranslated(-0.18,-1.0,0);
    glColor3f(0.3f, 0.3f, 1.0f);
    desenharToro2D(120, 40, 1.4, 1.25);
    glPopMatrix();


    glPopMatrix();
}
