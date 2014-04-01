
//      project:      hyperspace explorer
//      module:       SteinerFunction.H
//      contains:     Steiner surfaces -- this is sort of a dead branch, haven't
//		      really implemented anything; needs to be redone to fit in
//      compile with: make all
//	author:	      lene preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)


#if !defined(STEINER_FUNCTION_H)
#define STEINER_FUNCTION_H
/** Class defining a Steiner surface \n
 *  this is sort of a dead branch, I haven't really implemented anything;
 *  needs to be redone to fit in
 *  \ingroup FunctionGroup
 *  \author Lene Preuss <scout@hyperspace-travel.de>
 */
class SteinerFunction: public Function {
    public:
        SteinerFunction();
        /// constructor
        SteinerFunction (double _umin, double _umax, double _ustep,
                         double _vmin, double _vmax, double _vstep, double _a = 2.);
        virtual ~SteinerFunction();

        /// draw the projected Surface (onto screen or into GL list, as it is)
        virtual void Draw (void);

    protected:
        /// The mathematical function defining the Function object
        virtual VecMath::Vector<4> &f(double, double) = 0;
        virtual VecMath::Vector<4> *df (double, double);

    private:
        double a,    ///< ?
               umin, ///< ?
               umax, ///< ?
               du,   ///< ?
               vmin, ///< ?
               vmax, ///< ?
               dv;   ///< ?

        VecMath::Vector<4> F;
};

#endif // !defined(STEINER_FUNCTION_H)
