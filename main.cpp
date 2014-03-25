#include <QtGui/QApplication>
#include "HyperspaceExplorer.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    HyperspaceExplorer foo;
    foo.show();
    return app.exec();
}
