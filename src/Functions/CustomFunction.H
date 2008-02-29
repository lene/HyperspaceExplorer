
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include "Function.H"
#include "ComplexFunction.H"
#include "Surface.H"

class QString;

class CustomFunction: public Function {
public:
  CustomFunction (double _tmin, double _tmax, double _dt,
		  double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv,
		  bool final = true);
  virtual ~CustomFunction();

  QString symbolic ();
  
protected:
    virtual Vector<4> &f (double, double, double);
  bool loadFunction (const QString &);


  Vector<4> (*func)(double, double, double);

  void *handle;
};


class CustomPolarFunction: public CustomFunction {
public:
  CustomPolarFunction (double _tmin, double _tmax, double _dt,
		       double _umin, double _umax, double _du,
		       double _vmin, double _vmax, double _dv);
  virtual ~CustomPolarFunction();

protected:
    virtual Vector<4> &f (double, double, double);
};


class CustomComplexFunction: public ComplexFunction {
public:
  CustomComplexFunction (double _umin, double _umax, double _du,
			 double _vmin, double _vmax, double _dv);
  virtual ~CustomComplexFunction();

  QString symbolic ();
  
protected:
  std::complex<double> g (std::complex<double> z);
  bool loadFunction (const QString &);


  std::complex<double> (*gunc) (std::complex<double> z);


  void *handle;
};

class CustomSurface: public Surface {
public:
  CustomSurface ( double _umin, double _umax, double _du,
		  double _vmin, double _vmax, double _dv);
  virtual ~CustomSurface();

  QString symbolic ();
  
protected:
    virtual Vector<4> &f (double, double);
  bool loadFunction (const QString &);


  Vector<4> (*func)(double, double);

  void *handle;
};
