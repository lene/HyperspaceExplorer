///
/// C++ Implementation: destructor
///
/// Description:
///
///
/// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
///
/// Copyright: See COPYING file that comes with this distribution
///
///
#include <iostream>
class Base {
    public:
    Base() { }
    ~Base() { std::cerr << "~Base()" << std::endl; }
};

class Derived: public Base {
    public:
    Derived() { }
    ~Derived() { /*std::cerr << "~Derived()" << std::endl;*/ }
};

int main(int, char**) {
    Derived D;
    return 0;
}
