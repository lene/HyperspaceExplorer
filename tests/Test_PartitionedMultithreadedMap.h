/*
    Hyperspace Explorer - visualizing higher-dimensional geometry
    Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#ifndef TEST_PARTITIONEDMULTITHREADEDMAP_H
#define	TEST_PARTITIONEDMULTITHREADEDMAP_H

#include <QtTest/QtTest>

#include <unistd.h>

class Test_PartitionedMultithreadedMap: public QObject {

  Q_OBJECT

  public:
      
      static constexpr unsigned min_size_for_multithreaded_advantage = 1 << 10;

  private slots:

    void initTestCase();

    void worksForFunctor();
    void worksForFunction();
    void isFaster();
    void mappingInPlace();
    void mappingToArgument();

  private:

    template <typename T> std::vector<T> prepareTestData();
    template <typename T, typename Method> std::vector<T> executeMap(const std::vector<T> & data, const Method &method);
    template <typename T, typename Method> void executeTestForMethod(const Method &method);
    
    template <typename T> struct Duplicate {
        
        T operator() (const T &operand) {
            return 2*operand;
        }
        
    };
    
    struct TakeYourTime {
        int operator() (int i) {
            usleep(1);
            return i;
        }
    };
};

#endif	/* TEST_PARTITIONEDMULTITHREADEDMAP_H */

