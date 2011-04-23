/*
 * Hyperspace Explorer - visualizing higher-dimensional geometry
 * Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>
 *
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

#ifndef COMPOSITE_H
#define COMPOSITE_H
#include "Displayable.h"

#include <memory>

struct CompositeComponent {
  CompositeComponent(
    std::shared_ptr< Displayable > component,
    const VecMath::Vector< 4 > &translation = VecMath::makeVector(0., 0., 0., 0.),
    const VecMath::Rotation< 4 > &rotation = VecMath::makeRotation(0., 0., 0., 0., 0., 0.),
    const VecMath::Vector< 4 > &scale = VecMath::makeVector(1., 1., 1., 1.)
  ):
    component_(component), translation_(translation), rotation_(rotation), scale_(scale) { }
  
  std::shared_ptr< Displayable > component_;
  VecMath::Vector< 4 > translation_;
  VecMath::Rotation< 4 > rotation_;
  VecMath::Vector< 4 > scale_;
};

class Composite: public Displayable {

public:

  Composite();
  Composite(ParameterMap parameters);
  virtual ~Composite();

  void addComponent(std::shared_ptr<Displayable> component,
                    const VecMath::Vector< 4 >& translation,
                    const VecMath::Rotation< 4 >& rotation);
  const CompositeComponent &getComponent(unsigned i) const;
  unsigned getNumComponents();

  virtual void Transform(const VecMath::Rotation< 4 >& R, const VecMath::Vector< 4 >& T);
  virtual void Project(double ScrW, double CamW, bool DepthCue4D);
  virtual void Draw(UI::View* view);

  virtual void for_each_vertex(Displayable::function_on_fourspace_vertex apply);
  virtual void for_each_vertex_transformed(function_on_fourspace_and_transformed_vertex apply);
  virtual void for_each_projected(Displayable::function_on_projected_vertex apply);
  virtual void for_each_vertex_transformed_projected(function_on_fourspace_transformed_and_projected_vertex apply);

  virtual unsigned int getDefinitionSpaceDimensions();
  virtual void calibrateColors() const;
  virtual void ReInit(double _tmin, double _tmax, double _dt,
                      double _umin, double _umax, double _du,
                      double _vmin, double _vmax, double _dv);


protected:

  virtual void Initialize(void );
  virtual VecMath::Vector< 4, double >& operator()(double , double , double );

private:

  class Impl;
  Impl *pImpl_;

};

#endif // COMPOSITE_H
