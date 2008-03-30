//
// C++ Implementation: TestFactory
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <QMainWindow>
#include <QApplication>
#include <QMenuBar>
#include <QMouseEvent>

#include "TestFactory.h"

void SlotHelper::slot() {
          //   tests galore...
    mw->addBase(class_maker->make_base());
          //   some more tests...
}

void MyWidget::mousePressEvent (QMouseEvent *E) {
    menu->exec ();
}

void MyWidget::generateMenu() {
    if (!menu) menu = new QMenu;

    menu->addAction("slot1-title",
                    new SlotHelper(this,
                                   new TemplatedClassMaker<Derived1>),
                    SLOT(slot()));
    menu->addAction("slot2-title",
                    new SlotHelper(this,
                                   new TemplatedClassMaker<Derived2>),
                    SLOT(slot()));
    menu->addAction("slot3-title",
                    new SlotHelper(this,
                                   new TemplatedClassMaker<Derived3> ),
                    SLOT(slot()));
}

int main (int argc, char *argv[]) {
    QApplication app (argc, argv);
    QMainWindow *mainWindow = new QMainWindow;

    MyWidget mw;
    mw.generateMenu();
    mainWindow->setCentralWidget(&mw);
    mainWindow->menuBar()->addMenu(mw.menu);
    mainWindow->show();

    int ret = app.exec ();
    return ret;
}
