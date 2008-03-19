
//      project:      hyperspace explorer
//      module:       SteinerFunction.H
//      contains:     Steiner surfaces -- this is sort of a dead branch, haven't
//		      really implemented anything; needs to be redone to fit in
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(STEINER_FUNCTION_H)
#define STEINER_FUNCTION_H
/** Class defining a Steiner surface \n
 *  this is sort of a dead branch, I haven't really implemented anything;
 *  needs to be redone to fit in
 *  \ingroup FunctionGroup
 *  @author Helge Preuss <scout@hyperspace-travel.de>                         */
class SteinerFunction: public Function {
public:
  SteinerFunction();
  SteinerFunction (double _umin, double _umax, double _ustep,
		   double _vmin, double _vmax, double _vstep, double _a = 2.);
  virtual ~SteinerFunction();

  virtual void Draw (void);

protected:
  Vector &f (double, double);
  double **df (double, double);

  double a,
         umin, umax, du,
         vmin, vmax, dv;

  Vector F;
};

#endif // !defined(STEINER_FUNCTION_H)
