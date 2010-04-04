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

#ifndef PROJECTION_H
#define PROJECTION_H

#include <NestedVector.h>

#include <array>

template <unsigned N, unsigned Nnew, unsigned P> class Projection {
  
  public:
    
    Projection(const VecMath::Vector<N> viewpoint, const VecMath::Vector<N> eye, 
               double screenDistance, bool depthCue4D);
    Projection(double scrW, double camW, bool depthCue4D);
               
    VecMath::NestedVector< VecMath::Vector<Nnew>, P > Project(
            const VecMath::NestedVector< VecMath::Vector<N>, P > &values);
    
  private:
    
    std::tr1::array< VecMath::Vector<N>, N-Nnew > _viewpoint;
    std::tr1::array< VecMath::Vector<N>, N-Nnew > _eye; 
    std::tr1::array< double, N-Nnew > _screen_distance;
    std::tr1::array< bool, N-Nnew > _depth_cue_4d;
    
};

#endif // PROJECTION_H
