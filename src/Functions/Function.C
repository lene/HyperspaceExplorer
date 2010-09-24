
//      project:      hyperspace explorer
//      module:
//      contains:
//      compile with: make all
//	author:	      helge preuss (lene.preuss@gmail.com)
//	license:      GPL (see License.txt)

#include "Function.h"
#include "Log.h"
#include "ColorManager.h"
#include "ParameterMap.h"

using std::cerr;
using std::endl;

using VecMath::Vector;


struct Function::Impl {

  Impl() {}
  Impl(ParameterMap parameters): _parameters(parameters) { }
        
      /// Declare a new parameter for the Function
        void insertParameter(const std::string &name, FunctionParameter::parameter_ptr_type defaultValue) {
          _parameters.insert(std::make_pair(name, defaultValue));
        }

        /// counter for assessing how much RAM is used
        unsigned _numVertices;

        /// list of the parameters to the function
        ParameterMap _parameters;
 
};
//////////////////////////////////////////////////////////////////////
// construction / destruction
//////////////////////////////////////////////////////////////////////


/** Zeroes everything       */
Function::Function (): pImpl_(new Impl) { }


/** \param parameters Parameters for the Function.
 */
Function::Function (ParameterMap parameters): pImpl_(new Impl(parameters)) {
# if 0
    if (MemRequired() > Globals::Instance().getMaxMemory()) {
    }
# endif
}

Function::~Function() { }

void Function::resetTransform()  { Transform (VecMath::Rotation<4>(),  VecMath::Vector<4>()); }

FunctionParameter::parameter_ptr_type Function::getParameter(const std::string& name) {
  return pImpl_->_parameters.getParameter(name);
}

unsigned int Function::getNumParameters() { return pImpl_->_parameters.size(); }

FunctionParameter::value_ptr_type Function::getParameterValue(const std::string& name) {
  return pImpl_->_parameters.getValue(name);
}

/** \todo This function is only there to provide an interface, and it's
*  not abstract so that Function s which don't have Parameters don't
*  need to reimplement an unneeded method. But the present implementation
*  does not make sense.
*/
void Function::SetParameters(const ParameterMap& ) {
    std::cerr << "Function::SetParameters()" << std::endl;
}
ParameterMap Function::getParameters() { return pImpl_->_parameters; }

void Function::for_each(Function::function_on_fourspace_and_transformed_vertex apply) {
  throw NotYetImplementedException("for_each(function_on_fourspace_and_transformed_vertex)");
}

void Function::for_each(Function::function_on_fourspace_transformed_and_projected_vertex apply) {
  throw NotYetImplementedException("for_each(function_on_fourspace_transformed_and_projected_vertex)");
}

/** \todo uses hardcoded and experimentally found value for memory per cell
*  \return approx. mem required                                              */
unsigned long Function::MemRequired (void) {
    return 0;
}

/** \f[
        \frac{df}{dt} = \lim_{h \rightarrow 0}
            \frac{f(t+h, u, v) - f(t, u, v)}{h},
        \frac{df}{du},\frac{df}{dv}\mbox{analogously}
    \f]
 *  \todo The h value is fixed and hardcoded. better approach, please!
 *  \todo I don't think calling operator() is right. Call f()!
 *  \param tt t value
 *  \param uu u value
 *  \param vv v value
 *  \return gradient in t, u and v as array                                   */
Function::vec4vec1D Function::df (double tt, double uu, double vv) {

    static Vector<4> F;                //  f (u, v)
    static Vector<4> F0;                //  f (u, v)
    static double h = 1e-5;
    static Function::vec4vec1D DF(3);

    F0 = operator () (tt, uu, vv);

    F = operator () (tt+h, uu, vv);     //  derive after t
    DF[0] = (F-F0)/h;

    F = operator () (tt, uu+h, vv);     //  derive after u
    DF[1] = (F-F0)/h;

    F = operator () (tt, uu, vv+h);     //  derive after v
    DF[2] = (F-F0)/h;

    return DF;
}

/// Add a parameter with a name and a default value to the parameter list
template <typename T> inline
    void Function::declareParameter(const std::string &name,
                                    const T &defaultValue) {
      if (pImpl_->_parameters.find(name) != pImpl_->_parameters.end()) return;

      pImpl_->insertParameter(
          name,
          TheFunctionParameterFactory::Instance().createParameterWithDefault(name, defaultValue));
    }


/// Add a parameter with a name and a default value to the parameter list
template <typename T> inline
    void Function::declareParameter(const std::string &name,
                                    const T &defaultValue, const T &value) {
      if (pImpl_->_parameters.find(name) != pImpl_->_parameters.end()) return;

      pImpl_->insertParameter(
          name,
          TheFunctionParameterFactory::Instance().createParameterWithDefault(name, defaultValue));
      pImpl_->_parameters[name]->setValue(
          FunctionParameter::value_ptr_type(
              new FunctionParameterValue<T>(value)));
    }

template <typename T> inline
    void Function::setParameter(const ParameterMap &parms,
                                T &parm,
                                const std::string &key) {
        for (ParameterMap::const_iterator i = pImpl_->_parameters.begin();
        i != parms.end(); ++i) {
            if (i->second->getName() == key) parm = T(*(i->second));
        }
}

// explicit instantiations
template void Function::declareParameter(const std::string &name,
                                         const int &defaultValue); 
template void Function::declareParameter(const std::string &name,
                                         const unsigned &defaultValue); 
template void Function::declareParameter(const std::string &name,
                                         const double &defaultValue);                                         
template void Function::declareParameter(const std::string &name,
                                         const std::string &defaultValue);                                         
template void Function::declareParameter(const std::string &name,
                                         const VecMath::Rotation<5> &defaultValue);                                         
template void Function::declareParameter(const std::string &name,
                                         const VecMath::Rotation<6> &defaultValue);                                         
template void Function::declareParameter(const std::string &name,
                                         const VecMath::Rotation<7> &defaultValue);                                         
template void Function::declareParameter(const std::string &name,
                                         const VecMath::Rotation<8> &defaultValue);                                         
template void Function::declareParameter(const std::string &name,
                                         const VecMath::Rotation<9> &defaultValue);                                         
template void Function::declareParameter(const std::string &name,
                                         const VecMath::Rotation<10> &defaultValue);                                         
                                         
template void Function::declareParameter(const std::string &name,
                                         const unsigned &defaultValue, 
                                         const unsigned &value);
template void Function::declareParameter(const std::string &name,
                                         const double &defaultValue, 
                                         const double &value);
                                         