#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>

#include "point.h"

class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void paintGL();

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);

    void wheelEvent(QWheelEvent *);
    float zoomScale;
    void paintRect(Point center, float sari);
    void paintCirc(Point center, float rad);

    void paintc_1(int cant, float porc);
    void paintc_2(int cant, float porc);
    void paintc_3(int cant, float porc, float ang);

private:
    QOpenGLContext *context;
    QOpenGLFunctions *openGLFunctions;

};

#endif // MAINWINDOW_H
