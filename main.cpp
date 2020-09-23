#include "dialog.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>

int main(int argc, char *argv[])
{
    int WIDTH = 250;
    int HEIGHT = 250;

    int screenWidth;
    int screenHeight;

    int x, y;

    QApplication app(argc, argv);
    app.setApplicationDisplayName("Signal");

    Dialog dialog;
    dialog.setWindowTitle("Signal");
    QDesktopWidget *desktop = QApplication::desktop();

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - WIDTH) / 2;
    y = (screenHeight - HEIGHT) / 2;

    dialog.resize(WIDTH, HEIGHT);
    dialog.move( x, y );
    dialog.show();
    return app.exec();
}
