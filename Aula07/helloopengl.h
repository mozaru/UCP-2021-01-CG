#ifndef HELLOOPENGL_H
#define HELLOOPENGL_H

#include <QOpenGLWidget>
#include<QOpenGLFunctions>

class HelloOpenGL : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit HelloOpenGL(QWidget *parent = nullptr);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    void renderText(int x, int y, QString text);
    void mouseReleaseEvent(QMouseEvent *q) override;
    void keyPressEvent(QKeyEvent* e) override;
private:
    double cx,cy;
    QOpenGLContext *m_context;
    QSurface *m_surf;

signals:
    void invalidate();
};

#endif // HELLOOPENGL_H
