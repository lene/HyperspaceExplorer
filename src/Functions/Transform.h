/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Matrix.h"
#include "Rotation.h"

#include <QtConcurrentMap>

template <typename Type, unsigned N> class transform {
  public: 

    void operator() (VecMath::Matrix<N> &Rot,
                     const VecMath::Vector<N> &T,
                     const Type &X, Type &Xtrans);
};

template <typename Type, unsigned N> class transform< std::vector<Type>, N > {
  public: 
    static void xform(VecMath::Matrix<N> &Rot,
					  const VecMath::Vector<N> &T,
					  const std::vector<Type> &X, std::vector<Type> &Xtrans) {
    	static transform<std::vector<Type>, N> trans;
    	trans(Rot, T, X, Xtrans);
    }

    void operator() (VecMath::Matrix<N> &Rot,
                     const VecMath::Vector<N> &T,
                     const std::vector<Type> &X, std::vector<Type> &Xtrans) {


    	typename std::vector<Type>::const_iterator i = X.begin();
    	typename std::vector<Type>::iterator j = Xtrans.begin();
    	while(i != X.end() && j != Xtrans.end()) {
    		transform<Type, N>::xform(Rot, T, *i, *j);
    		++i; ++j;
    	}
      }

   // 	QtConcurrent::map(X, transform<Type, N>::xform);
};

template <unsigned D, unsigned N> class transform< VecMath::Vector<D>, N > {
  public: 

    static void xform(VecMath::Matrix<N> &Rot,
					  const VecMath::Vector<N> &T,
					  const VecMath::Vector<D> &X, VecMath::Vector<D> &Xtrans) {
    	static transform<VecMath::Vector<D>, N> trans;
    	trans(Rot, T, X, Xtrans);
    }

    void operator() (VecMath::Matrix<N> &Rot, const VecMath::Vector<N> &T,
                     const VecMath::Vector<D> &X, VecMath::Vector<D> &Xtrans) {
        Xtrans = (Rot*X)+T;
    }
};


#endif // TRANSFORM_H
