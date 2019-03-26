#include "qfe_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFE_Window w;
    w.show();

    return a.exec();
}
