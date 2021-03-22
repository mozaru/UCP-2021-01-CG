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
    void renderText(double x, double y, QString text);
    void mouseReleaseEvent(QMouseEvent *q) override;
    void keyPressEvent(QKeyEvent* e) override;
private:
    double cx,cy;

signals:

};

#endif // HELLOOPENGL_H
