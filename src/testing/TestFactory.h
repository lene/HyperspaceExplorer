///
/// C++ Interface: TestFactory
///
/// Description:
///
///
/// @author Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
/// \ingroup
///

#include <iostream>

#include <QMenu>

using std::cerr;
using std::endl;

class QMouseEvent;

namespace Testing {
    struct Base {
        Base() { cerr << "Base()" << endl; }
    };

    struct Derived1: public Base {
        Derived1() { cerr << "Derived1()" << endl; }
    };

    struct Derived2: public Base {
        Derived2() { cerr << "Derived2()" << endl; }
    };

    struct Derived3: public Base {
        Derived3() { cerr << "Derived3()" << endl; }
    };



    class MyWidget: public QWidget {
        Q_OBJECT
        public:

            class ClassMaker {
                public:
                    virtual Base* make_base()=0;
            };

            template <typename T>
                    class TemplatedClassMaker: public ClassMaker {
                        public:
                            virtual Base* make_base() { return new T; }
                    };

            void addBase(Base* b) {  myObject=b; }
            void generateMenu();

            Base *myObject;
            QMenu *menu;

        protected:
            void mousePressEvent (QMouseEvent *);
    };

    class SlotHelper: public QObject {
        Q_OBJECT
        public:
            SlotHelper(MyWidget* w, MyWidget::ClassMaker *cm):
                mw(w),class_maker(cm) {}
            ~SlotHelper() { delete class_maker;}
        public slots:
            void slot();
        private:
            MyWidget* mw;
            MyWidget::ClassMaker *class_maker;
    };
}
