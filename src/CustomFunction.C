
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


/*******************************************************************************
 *  outsourced function, as it is the same in all classes
 *  @param handle	an opened DLL handle
 *  @return		custom function in symbolic notation
 */
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


/*******************************************************************************
 *  CustomFunction c'tor given a definition set in R³ (as parameter space) and a
 *  flag indicatin whether this is a test construction or a real one
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 *  @param _final	real construction or test
 */
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


/*******************************************************************************
 *  CustomFunction destructor, closes DLL if necessary
 */
CustomFunction::~CustomFunction() {
  if (handle) dlclose (handle);       
}


/*******************************************************************************
 *  CustomFunction defining function; calls loaded function
 *  @param x		x value
 *  @param y		y value
 *  @param z		z value
 *  @return		custom function of (x, y, z)
 */
Vector &CustomFunction::f (double x, double y, double z) {
  static Vector T;
  T = (*func) (x, y, z);
  return T;
}


/*******************************************************************************
 *  @return		custom function in symbolic notation
 */
QString CustomFunction::symbolic () {
  return ::symbolic (handle);
}


/*******************************************************************************
 *  try to load a DLL and the f() in it
 *  @param libName	name of the plugin DLL file
 *  @return		success
 */
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


////////////////////////////////////////////////////////////////////////////////


/*******************************************************************************
 *  CustomPolarFunction c'tor given a definition set in R³ (as parameter space) and a
 *  flag indicatin whether this is a test construction or a real one
 *  @param _tmin	minimal value in t
 *  @param _tmax	maximal value in t
 *  @param _dt		stepsize in t
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
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


/*******************************************************************************
 *  CustomPolarFunction destructor, closes DLL if necessary
 */
CustomPolarFunction::~CustomPolarFunction() {
  if (handle) dlclose (handle);       
}

/*******************************************************************************
 *  CustomPolarFunction defining function; calls loaded function
 *  @param x		x value (these would really be phi, theta, psi)
 *  @param y		y value
 *  @param z		z value
 *  @return		custom function of (x, y, z)
 */
Vector &CustomPolarFunction::f (double x, double y, double z) {
  static Vector T;
  T = (*CustomFunction::func) (x, y, z);
  return T;
}



/*******************************************************************************
 *  CustomComplexFunction c'tor given a definition set in C (as parameter space) and a
 *  flag indicatin whether this is a test construction or a real one
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
CustomComplexFunction::CustomComplexFunction (double _umin, double _umax, double _du,
					      double _vmin, double _vmax, double _dv):
    ComplexFunction (_umin, _umax, _du, _vmin, _vmax, _dv),
    gunc (NULL), handle (NULL) {
  ComplexDialogImpl *Dlg = new ComplexDialogImpl ();

  if (Dlg->exec () == QDialog::Accepted) 
    loadFunction (Dlg->libraryName());

  Initialize ();
}

/*******************************************************************************
 *  CustomComplesFunction destructor, closes DLL if necessary
 */
CustomComplexFunction::~CustomComplexFunction() {
  if (handle) dlclose (handle);       
}

/*******************************************************************************
 *  CustomFunction defining function; calls loaded function
 *  @param z		(complex) z value
 *  @return		custom function of z
 */
complex<double> CustomComplexFunction::g (complex<double> z) {
  static complex<double> T;
  T = (*gunc) (z);
  return T;
}

/*******************************************************************************
 *  @return		custom function in symbolic notation
 */
QString CustomComplexFunction::symbolic () {
  return ::symbolic (handle);
}

/*******************************************************************************
 *  try to load a DLL and the f() in it
 *  @param libName	name of the plugin DLL file
 *  @return		success
 */
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


/*******************************************************************************
 *  CustomSurface c'tor given a definition set in R² (as parameter space) and a
 *  flag indicatin whether this is a test construction or a real one
 *  @param _umin	minimal value in u
 *  @param _umax	maximal value in u
 *  @param _du		stepsize in u
 *  @param _vmin	minimal value in v
 *  @param _vmax	maximal value in v
 *  @param _dv		stepsize in v
 */
CustomSurface::CustomSurface (double _umin, double _umax, double _du,
			      double _vmin, double _vmax, double _dv):
    Surface (_umin, _umax, _du, _vmin, _vmax, _dv),
    func (NULL), handle (NULL) {
  SurfaceDialogImpl *Dlg = new SurfaceDialogImpl ();

  if (Dlg->exec () == QDialog::Accepted) 
    loadFunction (Dlg->libraryName());

  Initialize ();
}

/*******************************************************************************
 *  CustomFunction destructor, closes DLL if necessary
 */
CustomSurface::~CustomSurface() {
  if (handle) dlclose (handle);       
}

/*******************************************************************************
 *  CustomFunction defining function; calls loaded function
 *  @param x		x value
 *  @param y		y value
 *  @param z		z value
 *  @return		custom function of (u, v)
 */
Vector &CustomSurface::f (double u, double v) {
  static Vector T;
  T = (*func) (u, v);
  return T;
}

/*******************************************************************************
 *  @return		custom function in symbolic notation
 */
QString CustomSurface::symbolic () {
  return ::symbolic (handle);
}

/*******************************************************************************
 *  try to load a DLL and the f() in it
 *  @param libName	name of the plugin DLL file
 *  @return		success
 */
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
