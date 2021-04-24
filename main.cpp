#include <QApplication>
#include <QWindow>
#include <QOpenGLWindow>
 #include <QDesktopWidget>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Due to personal preference, I have these lines set the window to fullscreen. If you don't want the window to be that large, feel free to comment this out.
    QDesktopWidget widget; // Gets info about the desktop. I have multiple monitors, so I need to make sure that my primary screen is the one that the game is shown on.
    w.setGeometry(widget.screenGeometry(widget.primaryScreen())); // Ignore the warnings about this being depricated, I couldn't get it to work in the way that it suggests
    w.setVisibility(QWindow::FullScreen); //Makes the window go fullscreen
    w.resize(widget.screenGeometry(widget.primaryScreen()).x(), widget.screenGeometry(widget.primaryScreen()).y()); // I really don't think this is neccessary, but its here anyway

    if (w.visibility() != 5) {
        w.resize(960, 540);
    }

    return a.exec();
}
