#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QOpenGLWindow(), t(), g(&t), tg(&t) {

    setSurfaceType(QWindow::OpenGLSurface);

    //// Setup opengl format
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,2); // For some reason the labs use 2.2
    format.setDepthBufferSize(1024);
    setFormat(format);

    //// Setup opengl context (the thing that is drawn on)
    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);

    cursor = QCursor(Qt::BlankCursor);
    QApplication::setOverrideCursor(cursor);
    QApplication::changeOverrideCursor(cursor);

    // Not entirely sure what this does, besides setting up a timer. Might be important for refresh rate, which seemed to be done manually.
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(UpdateAnimation()));
    timer->start(20);

    QTimer *gamelogic_timer = new QTimer(this);
    connect(gamelogic_timer, SIGNAL(timeout()),this, SLOT(GameAdvance()));
    gamelogic_timer->start(1000);

    t.spawn_piece();

}


MainWindow::~MainWindow() {
    //delete context; // For some reason the context wasn't being deleted before.
}


void MainWindow::initializeGL() {
    //glEnable — enable or disable server-side GL capabilities
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    resizeGL(this->width(),this->height());
}


void MainWindow::resizeGL(int w, int h) {
    //set viewport
    glViewport(0,0,w,h);

    //initialize projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* multiply the current matrix by a perspective matrix
     * void glFrustum(GLdouble left, GLdouble right,GLdouble bottom,GLdouble top,GLdouble nearVal,GLdouble farVal);
     * left, right: Specify the coordinates for the left and right vertical clipping planes.
     * bottom, top: Specify the coordinates for the bottom and top horizontal clipping planes.
     * nearVal, farVal: Specify the distances to the near and far depth clipping planes. Both distances must be positive.
     */
    glFrustum(-10, +10, -10, +10, 20.0, 100.0);

    //initialize modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -17.0);

    lastX = w/2;
    lastY = h/2;
    cursor.setPos(this->x() + lastX,this->y() + lastY);
}


void MainWindow::paintGL() {
    //removing previous frame
    glClearColor(0.5f,0.5f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glTranslatef(0.0, 0.0, -35.0);
    glRotatef(cam_x_r, 1.0, 0.0, 0.0);
    glRotatef(cam_y_r, 0.0, 1.0, 0.0);
    glRotatef(cam_z_r, 0.0, 0.0, 1.0);

    g.draw(1.0f);
    tg.draw();
    glFlush();

    if (key_w) {
        t.control(FORWARD);
        key_w = false; // don't do again unless repressed
    }
    if (key_s) {
        t.control(BACK);
        key_s = false; // don't do again unless repressed
    }
    if (key_a) {
        t.control(LEFT);
        key_a = false;
    }
    if (key_d) {
        t.control(RIGHT);
        key_d = false;
    }
    if (key_down) {
        if (t.control(DOWN) == LOSS) {
            lose();
        }
        key_down = false;
    }
    if (key_left) {
        t.control(PITCH);
        key_left = false;
    }
    if (key_right) {
        t.control(ROLL);
        key_right = false;
    }
    if (key_up) {
        t.control(YAW);
        key_up = false;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    // If you need to check more keys, add them here
    if (event->key() == Qt::Key_W) {
        key_w = true;
    }
    if (event->key() == Qt::Key_A) {
        key_a = true;
    }
    if (event->key() == Qt::Key_S) {
        key_s = true;
    }
    if (event->key() == Qt::Key_D) {
        key_d = true;
    }
    if (event->key() == Qt::Key_Up) {
        key_up = true;
    }
    if (event->key() == Qt::Key_Down) {
        key_down = true;
    }
    if (event->key() == Qt::Key_Left) {
        key_left = true;
    }
    if (event->key() == Qt::Key_Right) {
        key_right = true;
    }
    if (event->key() == Qt::Key_Escape) {
        qApp->exit();
    }
}

/*void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_W) {
        key_w = false;
    }
    if (event->key() == Qt::Key_A) {
        key_a = false;
    }
    if (event->key() == Qt::Key_S) {
        key_s = false;
    }
    if (event->key() == Qt::Key_D) {
        key_d = false;
    }
    if (event->key() == Qt::Key_Up) {
        key_up = false;
    }
    if (event->key() == Qt::Key_Down) {
        key_down = false;
    }
    if (event->key() == Qt::Key_Left) {
        key_left = false;
    }
    if (event->key() == Qt::Key_Right) {
        key_right = false;
    }
}*/

void MainWindow::mousePressEvent(QMouseEvent *event) {

}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    float newX = event->x(), newY = event->y();
    float deltaX = newX - lastX, deltaY = newY - lastY;

    cursor.setPos(this->x() + lastX,this->y() + lastY);
    event->accept();

    float sensitivity = 0.1;

    cam_z_r += deltaX * sensitivity;
    cam_x_r += deltaY * sensitivity;

    cursor.setPos(this->x() + lastX,this->y() + lastY);
}

void MainWindow::UpdateAnimation() {
    this->update();
}

void MainWindow::GameAdvance() {
    if (t.advance() == LOSS) {
        lose();
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    paintGL();
}


void MainWindow::resizeEvent(QResizeEvent *event) {
    resizeGL(this->width(),this->height());
    this->update();
}

void MainWindow::lose() {
    qApp->exit(); // replace this with a loss screen
}
