#include <QApplication>
#include "application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Application *app = new Application();
    app->start();

    return a.exec();
}
