#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <QDebug>
#include <QKeyEvent>
#include <QCursor>
#include <QGuiApplication>
#include <vector>

// To make things simpler, I'm using glu to generate our perspective matrix
// I understand that glu has caused some issues in the past, but right now this is easiser.
// if this causes anyone any issues, or if you have to edit the .pro at all to get this to work, let me know and I will do this manually
#include <GL/glu.h>
#include "Tetris.h"
#include "Ground.h"
#include "Tetris_Graphics.h"

///
/// This class is basically what we draw things on. Based on how main is setup, it seems like this class is also what drives everything
/// The protected functions are fairly self explanatory with their names.
/// THe paintGl() function iterates through gameObjects and displays them.
///
class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

    void keyPressEvent(QKeyEvent *); // logs which keys are pressed
    //void keyReleaseEvent(QKeyEvent *); // logs which keys are released

    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);
    void lose();
public slots:
    void UpdateAnimation();
    void GameAdvance();

private:
    QOpenGLContext *context;
    QOpenGLFunctions *openGLFunctions;

    // For right now, I will set up an abstract "GObject" Class that we can use for all of the tetris pieces, and any other scenery (ground, etc.) that we want / need
    // TODO: that ^
    // Vector<GObject*> gameObjects // Is called every update to draw vertices. Depending on how you want to implement the game we might want to do this differently, but for now I will go with this.


    float lastX=0, lastY=0; // keeps track of where the cursor is

    float cam_x=0, cam_y=0, cam_z=0, cam_x_r=0, cam_y_r=0, cam_z_r=0; // The position of the camera

    bool key_w=0,  key_a=0,    key_s=0,    key_d=0; // keeps track of which keys are pressed
    bool key_up=0, key_down=0, key_left=0, key_right=0; // keeps track of which keys are pressed

    QCursor cursor;
    Tetris t;
    Ground g;
    TetrisGraphics tg;
};


#endif // MAINWINDOW_H
