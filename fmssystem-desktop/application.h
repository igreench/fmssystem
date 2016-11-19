#ifndef APPLICATION_H
#define APPLICATION_H

#include "ui/mainwindow.h"

class Application
{
public:
    Application();

    void start();

private:
    MainWindow mainWindow;
};

#endif // APPLICATION_H
