
//      project:      hyperspace explorer
//      module:       CustomFunction.C
//      contains:     classes for dynamically loadable functions
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#include <dlfcn.h>

#include <iostream>

#include <qmessagebox.h>

#include "CustomFunction.H"

#include "FunctionDialogImpl.H"
#include "PolarDialogImpl.H"
#include "ComplexDialogImpl.H"
#include "SurfaceDialogImpl.H"


QString symbolic (void *handle) {
  typedef char* STRING;
  STRING (*sym)();
  sym = (STRING (*)())dlsym(handle, "symbolic");
  char *error;
  static char *ret;
    
  if ((error = dlerror()) != NULL)  { 
    cerr << "Error finding symbolic description in " << error << endl;
    return QString ("something");
  }
  ret=(*sym)();
  return QString (ret);
}


CustomFunction::CustomFunction (double _tmin, double _tmax, double _dt,
				double _umin, double _umax, double _du,
				double _vmin, double _vmax, double _dv,
				bool final):
    Function (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv),
    func (NULL), handle (NULL) {
  if (final) {
    FunctionDialogImpl *Dlg = new FunctionDialogImpl ();

    if (Dlg->exec () == QDialog::Accepted) {
      loadFunction (Dlg->libraryName());
      Initialize ();
    }
  }
}

CustomFunction::~CustomFunction() {
  if (handle) dlclose (handle);       
}

Vector &CustomFunction::f (double x, double y, double z) {
  static Vector T;
  T = (*func) (x, y, z);
  return T;
}

QString CustomFunction::symbolic () {
  return ::symbolic (handle);
}

bool CustomFunction::loadFunction(const QString &libName) {
  static char *error;
      
  handle = dlopen (libName, RTLD_LAZY);
  if (!handle) {
    cerr << "Error opening library: " << dlerror() << endl;
    return false;
  }

  func = (Vector(*)(double, double, double))dlsym(handle, "f");
  if ((error = dlerror()) != NULL)  {
    cerr << "Error finding function: " << error << endl;
    return false;
  }

  return true;    
}


CustomPolarFunction::CustomPolarFunction (double _tmin, double _tmax, double _dt,
					  double _umin, double _umax, double _du,
					  double _vmin, double _vmax, double _dv):
    CustomFunction (_tmin, _tmax, _dt, _umin, _umax, _du, _vmin, _vmax, _dv, false) {
  PolarDialogImpl *Dlg = new PolarDialogImpl ();

  if (Dlg->exec () == QDialog::Accepted) {
    loadFunction (Dlg->libraryName());
    Initialize ();
  }
}

CustomPolarFunction::~CustomPolarFunction() {
  if (handle) dlclose (handle);       
}

Vector &CustomPolarFunction::f (double x, double y, double z) {
  static Vector T;
  T = (*CustomFunction::func) (x, y, z);
  return T;
}



CustomComplexFunction::CustomComplexFunction (double _umin, double _umax, double _du,
					      double _vmin, double _vmax, double _dv):
    ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
    gunc (NULL), handle (NULL) {
  ComplexDialogImpl *Dlg = new ComplexDialogImpl ();

  if (Dlg->exec () == QDialog::Accepted) 
    loadFunction (Dlg->libraryName());

  Initialize ();
}

CustomComplexFunction::~CustomComplexFunction() {
  if (handle) dlclose (handle);       
}

complex<double> CustomComplexFunction::g (complex<double> z) {
  static complex<double> T;
  T = (*gunc) (z);
  return T;
}

QString CustomComplexFunction::symbolic () {
  return ::symbolic (handle);
}

bool CustomComplexFunction::loadFunction(const QString &libName) {
  static char *error;
      
  handle = dlopen (libName, RTLD_LAZY);
  if (!handle) {
    cerr << "Error opening library: " << dlerror() << endl;
    return false;
  }

  gunc = (complex<double>(*)(complex<double>))dlsym(handle, "f");
  if ((error = dlerror()) != NULL)  {
    cerr << "Error finding function: " << error << endl;
    return false;
  }

  return true;    
}


CustomSurface::CustomSurface (double _umin, double _umax, double _du,
			      double _vmin, double _vmax, double _dv):
    Surface (_umin, _umax, _du, _vmin, _vmax, _dv),
    func (NULL), handle (NULL) {
  SurfaceDialogImpl *Dlg = new SurfaceDialogImpl ();

  if (Dlg->exec () == QDialog::Accepted) 
    loadFunction (Dlg->libraryName());

  Initialize ();
}

CustomSurface::~CustomSurface() {
  if (handle) dlclose (handle);       
}

Vector &CustomSurface::f (double u, double v) {
  static Vector T;
  T = (*func) (u, v);
  return T;
}

QString CustomSurface::symbolic () {
  return ::symbolic (handle);
}

bool CustomSurface::loadFunction(const QString &libName) {
  static char *error;
      
  handle = dlopen (libName, RTLD_LAZY);
  if (!handle) {
    cerr << "Error opening library: " << dlerror() << endl;
    return false;
  }

  func = (Vector(*)(double, double))dlsym(handle, "f");
  if ((error = dlerror()) != NULL)  {
    cerr << "Error finding function: " << error << endl;
    return false;
  }

  return true;    
}
