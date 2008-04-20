//
// C++ Implementation: FunctionParameter
//
// Description:
//
//
// Author: Helge Preuss <scout@hyperspace-travel.de>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "FunctionParameter.H"

/// Specialization for type double
template<> FunctionParameterValue<double>::operator double() {
    return (double)value;
}
/// Specialization for type unsigned
template<> FunctionParameterValue<unsigned>::operator unsigned() {
    return (unsigned)value;
}
/// Specialization for type int
template<> FunctionParameterValue<int>::operator int() {
    return (int)value;
}
/// Specialization for type std::string
template<> FunctionParameterValue<std::string>::operator std::string() {
    return (std::string)value;
}
