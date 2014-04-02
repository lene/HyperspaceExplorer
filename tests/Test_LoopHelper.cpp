/* 
 * File:   Test_LoopHelper.cpp
 * Author: lene
 * 
 * Created on April 1, 2014, 10:28 PM
 */

#include "Test_LoopHelper.h"

#include "ParametricFunction.h"

#include "GlobalFunctions.h"
#include "LoopHelper.h"

#include "MultiDimensionalVector.impl.h"
#include "LSystems/LSystem_old.h"

using namespace UnitTests;
using namespace VecMath;

const double CONSTANT_FUNCTION_VALUE = 2.0;
const unsigned GRID_SIZE = 10;

struct Function1D: public ParametricFunction<3, 1> {
    virtual return_type f(const argument_type &){
        return Vector<3>(CONSTANT_FUNCTION_VALUE, 0., 0.);
    }
};

struct Function2D: public ParametricFunction<3, 2> {
    virtual return_type f(const argument_type &){
        return Vector<3>(CONSTANT_FUNCTION_VALUE, 0., 0.);
    }
};

void Test_LoopHelper::test_1D() {
    MultiDimensionalVector<Vector<3>, 1> storage;
    test(storage.size() != GRID_SIZE, std::string("storage not sized to fit grid initially"));
    std::shared_ptr< ParametricFunction<3, 1>> f(new Function1D());
    LoopHelper<3, 1, 1, double> loop(Vector<1>(-1), Vector<1>(1), Vector<1, unsigned>(GRID_SIZE), f);
    Vector<1> current_x;
    
    loop.recalculateOneDimensionOfGrid(storage, current_x);
    
    test(storage.size() == GRID_SIZE, std::string("storage has been resized to fit grid"));
    for (auto v: storage) {
        test(v == Vector<3>(CONSTANT_FUNCTION_VALUE, 0., 0.), std::string("storage contains predefined value"));
    }
}

void Test_LoopHelper::test_2D() {
    MultiDimensionalVector<Vector<3>, 2> storage;
    test(storage.size() != GRID_SIZE, std::string("storage not sized to fit grid initially"));
    std::shared_ptr< ParametricFunction<3, 2>> f(new Function2D());
    LoopHelper<3, 2, 2, double> loop(Vector<2>(-1., -1.), Vector<2>(1., 1.), Vector<2, unsigned>(GRID_SIZE), f);
    Vector<2> current_x;
    
    loop.recalculateOneDimensionOfGrid(storage, current_x);
    
    test(storage.size() == GRID_SIZE, std::string("storage has been resized to fit grid"));
    for (auto column: storage) {
        for (auto v: column) {
            test(v == Vector<3>(CONSTANT_FUNCTION_VALUE, 0., 0.), std::string("storage contains predefined value"));
        }
    }
}
