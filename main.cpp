#include <QApplication>
#include "window.h"
#include <QDesktopWidget>
#include <QWidget>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    int WIDTH = 250;
    int HEIGHT = 250;

    int screenWidth;
    int screenHeight;

    int x, y;
    QApplication app(argc, argv);



    MainWindow w;
    w.setWindowTitle("Signal");
    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;

    w.resize(WIDTH, HEIGHT);
    w.move( x, y );
    w.show();
    return app.exec();
}

