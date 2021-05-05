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

    //GObject::context = context;
    //GObject::window = this;

    //// Instead of sending the camera location to the objects everytime, I just set up some static pointers that get us the same thing
    //GObject::cam_x = &cam_x;     // This could probably be simplified,
    //GObject::cam_y = &cam_y;     // but for now I am going to focus on
    //GObject::cam_z = &cam_z;     // getting the critical functions working
    //GObject::cam_x_r = &cam_x_r;
    //GObject::cam_y_r = &cam_y_r;
    //GObject::cam_z_r = &cam_z_r;


//    objects = new std::vector<GObject*>();
//    objects -> push_back(new ExampleGround(0.0f, -1.0f, 0.0f));
//    objects -> push_back(new ExampleBrick(0.0f, 9.0f, -9.0f, (ExampleGround*)objects->front()));
//
    t.spawn_piece();

}


MainWindow::~MainWindow() {
    // Frees the memory from this
    //while (objects->size() != 0) {
    //    free(objects->back());
    //    objects->pop_back();
    //}


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
    glFrustum(-2, +2, -2, +2, 4.0, 10.0);

    //initialize modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    lastX = w/2;
    lastY = h/2;
    cursor.setPos(this->x() + lastX,this->y() + lastY);
}


void MainWindow::paintGL() {
    //removing previous frame
    glClearColor(0.5f,0.5f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -17.0);
    glRotatef(cam_x_r, 1.0, 0.0, 0.0);
    glRotatef(cam_y_r, 0.0, 1.0, 0.0);
    glRotatef(cam_z_r, 0.0, 0.0, 1.0);

    int x, y, z;
    float r, g, b;
    float block_width = 1;
    for (int i = 0; i < t.w*t.l*t.h; i++) {
        t.ind2sub(i, x, y, z);
        if (t.state[x][y][z] != NULL) {
            r = ((float) t.state[x][y][z]->r) / 255;
            g = ((float) t.state[x][y][z]->g) / 255;
            b = ((float) t.state[x][y][z]->b) / 255;
            glBegin(GL_QUADS); // bottom
                glColor3f(r, g, b);
                glVertex3f(block_width*x, block_width*y, block_width*z);
                glVertex3f(block_width*(x+1), block_width*y, block_width*z);
                glVertex3f(block_width*x, block_width*(y+1), block_width*z);
                glVertex3f(block_width*(x+1), block_width*(y+1), block_width*z);
            glEnd();
        }
    }
    glFlush();

    if (key_w) {
        qDebug("w");
    }
    if (key_a) {
        qDebug("a");
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
    if (event->key() == Qt::Key_Escape) {
        qApp->exit();
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    // If you need to check more keys, also add them here
    if (event->key() == Qt::Key_W){
        key_w = false;
    }
    if (event->key() == Qt::Key_A){
        key_a = false;
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
    printf("%f %f\n", this->x() + lastX, this->y() + lastY);

}

void MainWindow::UpdateAnimation() {
    this->update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    paintGL();
}


void MainWindow::resizeEvent(QResizeEvent *event) {
    resizeGL(this->width(),this->height());
    this->update();
}
