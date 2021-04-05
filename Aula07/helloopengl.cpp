#include "helloopengl.h"
#include<GL/gl.h>
#include<math.h>
#include<iostream>
#include<QDateTime>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QPainter>

typedef struct
{
    double x,y;
} Ponto;

HelloOpenGL::HelloOpenGL(QWidget *parent) : QOpenGLWidget(parent)
{
    cx=cy=0.0;

    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();


    connect(this, &HelloOpenGL::invalidate, this, [this] {
        qDebug() << "invalidate";
         //m_context->makeCurrent(m_surf);
        this->makeCurrent();
        this->paintGL();
        this->doneCurrent();
        // m_context->doneCurrent();
        this->glFlush();
        //m_context->swapBuffers(m_surf);
    }, Qt::QueuedConnection);
}



GLuint LoadGLTextures(QString path){

    QImage img;
    GLuint tex;

    if(!img.load(path)){

        qDebug()<<"Image loading failed";
    }

    QImage t = (img.convertToFormat(QImage::Format_RGBA8888)).mirrored();

    glGenTextures(1, &tex);

    glBindTexture(GL_TEXTURE_2D, tex);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture( GL_TEXTURE_2D, 0);


    return tex;
}

GLuint textura;
void HelloOpenGL::initializeGL()
{
    m_context = context()->currentContext();
    m_surf = context()->currentContext()->surface();
    //QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    //glFuncs->glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    this->initializeOpenGLFunctions();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    textura = LoadGLTextures("C:\\Aulas\\202101- UCP - CG\\Aula07\\azulejo.jpg");

    glEnable(GL_TEXTURE_2D);

}

void HelloOpenGL::resizeGL(int width, int height)
{
    Q_UNUSED(width);
    Q_UNUSED(height);
}

void HelloOpenGL::renderText(int x, int y, QString text)
{
    QPainter painter(this);
    painter.setPen(Qt::yellow);
    painter.setFont(QFont("Helvetica", 16));
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.drawText(x, y, text); // z = pointT4.z + distOverOp / 4
    painter.end();
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


/*void HelloOpenGL::invalidate()
{

}*/

void HelloOpenGL::paintGL()
{
    static int contFrames=0;
    static int FPS = 0;
    static long long lastTime=QDateTime::currentMSecsSinceEpoch();

    static double ang=0;
    int max = this->width()>this->height() ? this->width():this->height();
    glViewport((this->width()-max)/2, (this->height()-max)/2, max, max);
    //glViewport(0,0, this->width(), this->height());

    glBindTexture( GL_TEXTURE_2D, 0);


    float final = 1.0;
    glPushMatrix();
    glColor3d(0,0,0);
    glBegin(GL_QUADS);
            //glTexCoord2f(0,0);
            glVertex3f(-1,-1,0);
            //glTexCoord2f(final,0);
            glVertex3f( 1,-1,0);
            //glTexCoord2f(final,final);
            glVertex3f( 1, 1,0);
            //glTexCoord2f(0,final);
            glVertex3f(-1, 1,0);
        glEnd();
    //
    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();


    glPushMatrix();
    ang += 1;
    glTranslatef(cx,cy,0);
    glRotatef(ang,0,0,1);
    //aqui fazemos nosso desenho
    glColor3d(0,255,255);
    glBindTexture( GL_TEXTURE_2D, textura);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(1.5,0);
        glVertex2f(0.0,-0.5);
        glTexCoord2f(3,3);
        glVertex2f(0.5,0.5);
        glTexCoord2f(0,3);
        glVertex2f(-0.5,0.5);
    glEnd();
    glPopMatrix();
    glBindTexture( GL_TEXTURE_2D, 0);

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
        //std::cout << "FPS:" << contFrames << std::endl;
        FPS = contFrames;
        contFrames = 0;
        lastTime = QDateTime::currentMSecsSinceEpoch();
    }
    QString s= QString("FPS:%1").arg(FPS);
    renderText(10,25,s);

    this->update();
}
