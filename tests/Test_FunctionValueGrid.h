#ifndef TEST_FUNCTIONVALUEGRID_H_
#define TEST_FUNCTIONVALUEGRID_H_

#include "FunctionValueGrid.h"

#include <QtTest/QtTest>

#include <tr1/memory>

class Test_FunctionValueGrid: public QObject {

  Q_OBJECT

private slots:
  
  void initializeGrid();

private:
  
  std::tr1::shared_ptr< FunctionValueGrid<4, 3> > _grid;
  
};


#endif /* MATRIXTEST_H_ */
