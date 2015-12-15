#include "unixvizmainwindow.h"
#include <QApplication>
#include <signal.h>
#include <string>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setStyle("fusion");

    UnixVizMainWindow w;
    w.show();

    return a.exec();

}
