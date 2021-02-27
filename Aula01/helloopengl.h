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

signals:

};

#endif // HELLOOPENGL_H
