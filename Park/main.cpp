#include "mainwindow.h"
#include <QApplication>

#ifdef QT_NO_DEBUG_OUTPUT
#undef QT_NO_DEBUG_OUTPUT
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
