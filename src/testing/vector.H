
#include <string>
#include <iterator>
#include <stdexcept>
#include <iostream>

template<bool condition> struct boundary_check { };
template<> struct boundary_check<true>  { static void f () { } };
template<>struct boundary_check<false> { static void f () {
  throw std::out_of_range (std::string ("index out of bounds")); }
};

template<unsigned D, typename num = double>
class vec {

public:
  template<unsigned i>
  struct Access {
    static num access (num *data_) { return data_[i]; }
    static num checked_access (num *data_) {
      boundary_check<(i < D)>::f ();
      return access (data_);
    }
    static num access (vec<D> vec) { return vec[i]; }
    static num checked_access (vec<D> vec) {  
      return checked_access (vec.data_);
    }
  };
  
public:
  static num dot (num *a, num *b) {
    return a[D-1]*b[D-1]+vec<D-1, num>::dot (a, b);
  }
  static num norm (num *a) {
    return dot (a, a);
  }
  static num abs (num *a) {
    return sqrt (norm (a));
  }  
  static void scalar (num *a, num s) {
    a[D-1] *= s;
    vec<D-1, num>::scalar (a, s);
  }
  static void normalize (num *a) {
    scalar (a, 1./abs (a));
  }
  vec (bool random = false): data_ (new num [D]) {
    for (int i = 0; i < D; i++) data_[i] = random? num (rand ())/RAND_MAX: 0;
    if (!random) data_[0] = 1;
  }
  num dot (vec<D, num> b) { return dot (data_, b.data_); }
  num norm () { return norm (data_); }
  num abs () { return abs (data_); }
  void scalar (num s) { scalar (data_, s); }
  void normalize () {return normalize (data_); }

  num &operator[] (unsigned i) { return data_[i]; }
  num  operator[] (unsigned i) const { return data_[i]; }

  num &at (unsigned i) {
    if (i >= D) throw std::out_of_range (std::string ("index out of bounds"));
    return data_[i];
  }
  template <unsigned i> num  at () const {
    if (i >= D) throw std::out_of_range (std::string ("index out of bounds"));
    return data_[i];
  }
  
  void print () {
    std::cout << "< ";
    std::copy (data_, data_+D-1, std::ostream_iterator<num>(std::cout, ", "));
    std::cout << data_[D-1] << " >" << std::endl; 
  }
  
  static bool is_vec () { return true; }
  static unsigned dimension () { return D; }
private:
  num *data_;
};

template <typename num>
class vec<0, num> {
public:
  static num dot (num *a, num *b) { return 0; }
  static void scalar (num *a, num s) { }
};

template<unsigned D, class vec1, class vec2, typename num>
struct Dot {
  num dot () {
    assert (vec1::is_vec ());
    assert (vec2::is_vec ());
    assert (vec1::dimension () == vec2::dimension ());
    
    // ...

    return 0.;
  }
};
