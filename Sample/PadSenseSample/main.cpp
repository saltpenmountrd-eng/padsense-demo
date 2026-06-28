#include "widget.h"
#include <QApplication>

Widget *g_Widget;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    g_Widget = &w;
    w.setWindowState( Qt::WindowFullScreen );
    w.ShowWidget();

    return a.exec();
}
