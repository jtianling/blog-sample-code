#ifndef OPENGL_H
#define OPENGL_H

#include <QtOpenGL/QtOpenGL>
#include <QtGui/QWidget>
#include "ui_opengl.h"

class OpenGL : public QGLWidget
{
    Q_OBJECT

public:
    OpenGL(QGLWidget *parent = 0);
    ~OpenGL();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    void draw();

private:
    Ui::OpenGLClass ui;
};

#endif // OPENGL_H
