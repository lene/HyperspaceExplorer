#ifndef TEST_FUNCTIONVALUEGRID_H_
#define TEST_FUNCTIONVALUEGRID_H_

#include "FunctionValueGrid.h"

#include <QtTest/QtTest>

#include <tr1/memory>

class Test_FunctionValueGrid: public QObject {

  Q_OBJECT

private slots:
  
  void initTestCase();
  
  void initializeGrid();
  void functionValues();

private:
  
  std::tr1::shared_ptr< FunctionValueGrid<4, 3> > _grid;
  
  const static double DEFAULT_X_MIN = -1.;
  const static double DEFAULT_X_MAX =  1.;
  const static unsigned DEFAULT_GRID_SIZE = 10;
  
};


#endif /* MATRIXTEST_H_ */
