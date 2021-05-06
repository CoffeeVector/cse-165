#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QOpenGLWindow(), t() {

    setSurfaceType(QWindow::OpenGLSurface);

    //// Setup opengl format
    //QSurfaceFormat format;
    //format.setProfile(QSurfaceFormat::CompatibilityProfile);
    //format.setVersion(4,3); // For some reason the labs use 2.2
    //setFormat(format);

    //// Setup opengl context (the thing that is drawn on)
    //context = new QOpenGLContext;
    //context->setFormat(format);
    //context->create();
    //context->makeCurrent(this);

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

    //GObject::context = context;
    //GObject::window = this;

    //// Instead of sending the camera location to the objects everytime, I just set up some static pointers that get us the same thing
    //GObject::cam_x = &cam_x;     // This could probably be simplified,
    //GObject::cam_y = &cam_y;     // but for now I am going to focus on
    //GObject::cam_z = &cam_z;     // getting the critical functions working
    //GObject::cam_x_r = &cam_x_r;
    //GObject::cam_y_r = &cam_y_r;
    //GObject::cam_z_r = &cam_z_r;

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

    int x, y, z;
    float r, g, b;
    float block_width = 0.9;
    //float color_width = 0.9;
    for (int i = 0; i < t.w*t.l*t.h; i++) {
        t.ind2sub(i, x, y, z);
        if (t.state[x][y][z] != NULL) {
            r = ((float) t.state[x][y][z]->r) / 255;
            g = ((float) t.state[x][y][z]->g) / 255;
            b = ((float) t.state[x][y][z]->b) / 255;
            int num_corners = 4*6;
            int cube_coords[num_corners][3] = {
                //bottom
                {0, 0, 0},
                {1, 0, 0},
                {1, 1, 0},
                {0, 1, 0},
                //top
                {0, 0, 1},
                {1, 0, 1},
                {1, 1, 1},
                {0, 1, 1},
                //front
                {0, 0, 0},
                {0, 1, 0},
                {0, 1, 1},
                {0, 0, 1},
                //back
                {1, 0, 0},
                {1, 1, 0},
                {1, 1, 1},
                {1, 0, 1},
                //left
                {0, 0, 0},
                {0, 0, 1},
                {1, 0, 1},
                {1, 0, 0},
                //right
                {0, 1, 0},
                {0, 1, 1},
                {1, 1, 1},
                {1, 1, 0},
            };

            int mode[] = {GL_FILL, GL_LINE};
            for (int i = 0; i < 2; i++) { // draw twice, once with borders, and another wth fill
                glPolygonMode(GL_FRONT_AND_BACK, mode[i]);
                glBegin(GL_QUADS); // bottom
                    if (i == 0) {
                        glColor3f(r, g, b);
                    } else {
                        glColor3f(0, 0, 0);
                    }
                    for (int corner = 0; corner < num_corners; corner++) {
                        glVertex3f(
                            block_width*(x + cube_coords[corner][0]),
                            block_width*(y + cube_coords[corner][1]),
                            block_width*(z + cube_coords[corner][2])
                        );
                    }
                glEnd();
            }
        }
    }
    glFlush();

    if (key_s) {
        if (t.control(DOWN) == LOSS) {
            lose();
        }
        key_s = false; // don't do again unless repressed
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
    if (event->key() == Qt::Key_Escape) {
        qApp->exit();
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    // If you need to check more keys, also add them here
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
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    float newX = event->x(), newY = event->y();
    float deltaX = newX - lastX, deltaY = newY - lastY;

    cursor.setPos(this->x() + lastX,this->y() + lastY);
    event->accept();

    float sensitivity = 0.1;

    cam_y_r += deltaX * sensitivity;
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
