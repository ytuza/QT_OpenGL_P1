#include "mainwindow.h"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
{
    setSurfaceType(QWindow::OpenGLSurface);


    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);

    setFormat(format);

    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();

    context->makeCurrent(this);
    openGLFunctions = context->functions();

    zoomScale = 0.01;
}

MainWindow::~MainWindow()
{

}


void MainWindow::initializeGL()
{
    resizeGL(this->width(),this->height());

}

void MainWindow::wheelEvent(QWheelEvent *ev){


    QPoint numDegrees = ev->angleDelta();
    if (numDegrees.y() < 0)  zoomScale = zoomScale/1.1;
    if (numDegrees.y() > 0)  zoomScale = zoomScale*1.1;
    update(); // call paintGL()

    qDebug() << zoomScale;

}

void MainWindow::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0,0,w,h);

   qreal aspectratio = qreal(w)/qreal(h);
   glOrtho(-1* aspectratio,1*aspectratio,-1,1,1,-1);


}

void MainWindow::paintGL()
{

    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glScaled(zoomScale, zoomScale, zoomScale);

    paintRect(Point(0.0,0.0),100);
    //paintc_2(5,0.3);
    paintc_3(5,0.3,70);

    glFlush();


}


void MainWindow::paintRect(Point center, float sari){
    float ma = sari/2;
    glBegin(GL_LINE_LOOP);
    glColor3d(0,255,0);

    glVertex2f(center.x+ma, center.y+ma);
    glVertex2f(center.x+ma, center.y-ma);
    glVertex2f(center.x-ma, center.y-ma);
    glVertex2f(center.x-ma, center.y+ma);


    glEnd();
}



void MainWindow::paintCirc(Point center, float rad){
    int lineAmount = 100;

    GLfloat DPi = 2.0 * M_PI;
    //qDebug()<< DPi << " <- ";

    glBegin(GL_LINE_LOOP);
        glColor3d(0,0,255);
        for(int i = 0; i <= lineAmount;i++) {
            glVertex2f(
                center.x + (rad * cos(i * DPi / lineAmount)),
                center.y + (rad * sin(i * DPi / lineAmount))
            );
        }
    glEnd();
}


void MainWindow::paintc_1(int cant, float porc){
    Point c(0.0,0.0);
    float l = 40;

    for(int i =0; i < cant;i++){
        paintCirc(c,l);
        c.x = c.x-(l*porc);
        l = l*(1-porc);
    }
}

void MainWindow::paintc_2(int cant, float porc){
    Point c(0.0,0.0);
    float l = 40;

    for(int i =0; i < cant;i++){
        paintCirc(c,l);
        c.x = c.x+(2*l-l*porc);
        l = l*(1-porc);
    }
}

void MainWindow::paintc_3(int cant, float porc, float ang){
    Point c(0.0,0.0);
    float l = 40;

    ang=ang*M_PI/180;

    for(int i =0; i < cant;i++){
        paintCirc(c,l);
        c.x = c.x+qCos(ang)*(2*l-l*porc);
        c.y = c.y+qSin(ang)*(2*l-l*porc);
        l = l*(1-porc);
    }
}
