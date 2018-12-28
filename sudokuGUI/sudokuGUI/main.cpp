#include <QApplication>
#include "main_ui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    Widget0 *wm=new Widget0();
    wm->show();
    return app.exec();
}
