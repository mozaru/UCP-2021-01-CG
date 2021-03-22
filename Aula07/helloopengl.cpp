#include "helloopengl.h"
#include<GL/gl.h>
#include<math.h>
#include<iostream>
#include<QDateTime>
#include<QMouseEvent>
#include<QKeyEvent>

typedef struct
{
    double x,y;
} Ponto;

HelloOpenGL::HelloOpenGL(QWidget *parent) : QOpenGLWidget(parent)
{
    cx=cy=0.0;

    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
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

void HelloOpenGL::renderText(double x, double y, QString text)
{
/*    int width = this->width();
    int height = this->height();

    GLdouble model[4][4], proj[4][4];
    GLint view[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, &model[0][0]);
    glGetDoublev(GL_PROJECTION_MATRIX, &proj[0][0]);
    glGetIntegerv(GL_VIEWPORT, &view[0]);
    GLdouble textPosX = 0, textPosY = 0, textPosZ = 0;

    textPosY = height - textPosY; // y is inverted

    QPainter *painter = (QPainter *)this->sharedPainter();
    painter->setPen(Qt::yellow);
    painter->setFont(QFont("Helvetica", 8));
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->drawText(textPosX, textPosY, text); // z = pointT4.z + distOverOp / 4
    painter->end();
*/
}

void HelloOpenGL::keyPressEvent(QKeyEvent* e)
{
    std::cout << "tecla "<< e->key() << std::endl;
    if (e->key()==Qt::Key_Escape)
    {
        std::cout << "tecla escape pressionada" << std::endl;
        exit(0);
    }
}

void HelloOpenGL::mouseReleaseEvent(QMouseEvent *q)
{
    double x = q->position().x();
    double y = q->position().y();

    std::cout << "x:" << x << std::endl;
    std::cout << "y:" << y << std::endl;
    std::cout << "w:" << this->width() << std::endl;
    std::cout << "h:" << this->height() << std::endl;
    std::cout << "cx:" << this->width()/2 << std::endl;
    std::cout << "cy:" << this->height()/2 << std::endl;

    int max = this->width()>this->height() ? this->width():this->height();

    int centroJanelaX = this->width()/2;
    int centroJanelaY = this->height()/2;

    cx = (double)(x-centroJanelaX)/(max/2);
    cy = (double)(centroJanelaY-y)/(max/2);
}


void HelloOpenGL::paintGL()
{
    static int contFrames=0;
    static long long lastTime=QDateTime::currentMSecsSinceEpoch();

    static double ang=0;
    int max = this->width()>this->height() ? this->width():this->height();
    glViewport((this->width()-max)/2, (this->height()-max)/2, max, max);
    //glViewport(0,0, this->width(), this->height());


    glPushMatrix();
    ang += 1;
    glTranslatef(cx,cy,0);
    glRotatef(ang,0,0,1);
    //aqui fazemos nosso desenho
    glColor3d(255,0,0);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0,-0.5);
        glVertex2f(0.5,0.5);
        glVertex2f(-0.5,0.5);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(cx,cy,0);
    glColor3d(0,0,255);
    glPointSize(10);
    glBegin(GL_POINTS);
        glVertex2f(0,0);
    glEnd();
    glPopMatrix();


    contFrames++;
    if (QDateTime::currentMSecsSinceEpoch()-lastTime > 1000)
    {
        std::cout << "FPS:" << contFrames << std::endl;
        contFrames = 0;
        lastTime = QDateTime::currentMSecsSinceEpoch();
    }


    this->update();
}
