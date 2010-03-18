
#include <iostream>
#include <tr1/memory>

class A {
  public:
  virtual void f() { std::cerr << "A::f()" << std::endl; }
};

class B: public A { 
  public:
  virtual void f() { std::cerr << "B::f()" << std::endl; }
};

class A_fac {
  public:
  static A *makeA() { return new B; } 
};

int main(int, char**) {
  std::tr1::shared_ptr<A> ptrA(A_fac::makeA());
  ptrA->f();
}