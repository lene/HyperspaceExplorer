
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(FUNCTION_H)
#define FUNCTION_H

class SteinerFunction  
{
public:
	SteinerFunction();
	SteinerFunction (double _umin, double _umax, double _ustep,
			  double _vmin, double _vmax, double _vstep, double _a = 2.);
	virtual ~SteinerFunction();

	virtual void Draw (void);

protected:
	double *f (double, double);
	double **df (double, double);
	
	double a,
		   umin, umax, du,
		   vmin, vmax, dv;

	double  *F,
		   **DF;
};

#endif // !defined(FUNCTION_H)
