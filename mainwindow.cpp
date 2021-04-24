#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QOpenGLWindow() {
    setSurfaceType(QWindow::OpenGLSurface);

    // Setup opengl format
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(4,3); // For some reason the labs use 2.2
    setFormat(format);

    // Setup opengl context (the thing that is drawn on)
    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);

    // Not entirely sure what this does, besides setting up a timer. Might be important for refresh rate, which seemed to be done manually.
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(UpdateAnimation()));
    timer->start(20);

    GObject::context = context;
    GObject::window = this;

    // Instead of sending the camera location to the objects everytime, I just set up some static pointers that get us the same thing
    GObject::cam_x = &cam_x;
    GObject::cam_y = &cam_y;
    GObject::cam_z = &cam_z;
    GObject::cam_x_r = &cam_x_r;
    GObject::cam_y_r = &cam_y_r;
    GObject::cam_z_r = &cam_z_r;


    objects = new std::vector<GObject*>();
    objects -> push_back(new ExampleGround(0.0f, -1.0f, 0.0f));
}


MainWindow::~MainWindow() {
    // Frees the memory from this
    while (objects->size() != 0) {
        objects->pop_back();
    }


    delete context; // For some reason the context wasn't being deleted before.
}


void MainWindow::initializeGL() {
    //glEnable — enable or disable server-side GL capabilities
    glEnable(GL_DEPTH_TEST);
    resizeGL(this->width(),this->height());
}


void MainWindow::resizeGL(int w, int h) {
    //set viewport
    glViewport(0,0,w,h);
    //qreal aspectratio = qreal(w)/qreal(h);

    //initialize projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Sets up a perspective projection matrix
    float fov = 1.39f; // Field of View
    float tanfov = tanf(fov/2);
    float aspect = ((float)w)/h;
    float zFar = 1000.0f;
    float zNear = 0.01f;
    float mat[16] = {1/(aspect*tanfov),0.0f,0.0f,0.0f,
                     0.0f,(1/tanfov),0.0f,0.0f,
                     0.0f,0.0f,-((zFar + zNear)/(zFar-zNear)),-1.0f,
                     0.0f,0.0f,-((2.0f*zFar*zNear)/(zFar-zNear)),0.0f};
    glLoadMatrixf(mat);

    //initialize modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


void MainWindow::paintGL() {
    //removing previous frame
    glClearColor(0.5f,0.5f,0.5f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < objects -> size(); i++) {
        objects -> at(i) -> draw();
    }






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
