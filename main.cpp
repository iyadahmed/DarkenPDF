#include "main_window.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow main_window;
    main_window.showNormal();
    return app.exec();
}
