#ifndef MOCKVIEW_H
#define MOCKVIEW_H 1

#include "ViewImpl.h"

/// Class for testing behavior on View objects
/** This does not have any implementation yet
 */
class MockView: public UI::ViewImpl {
  public:
    MockView(bool verbose = false);
    virtual void ObjectHypercube() {}
    virtual void ObjectHyperpyramid() {}
    virtual void ObjectHypersponge() {}
    virtual void ObjectGasket() {}
    virtual void ObjectRotope() {}
    virtual void applyTransform(const VecMath::Rotation< 4 >& , const VecMath::Vector< 4 >& ) {}
    virtual void animate() {}
    virtual void setSize(unsigned int , unsigned int ) {}
    virtual void drawCube(const VecMath::Vector< 3 >& v0, const VecMath::Vector< 3 >& v1,
                          const VecMath::Vector< 3 >& v2, const VecMath::Vector< 3 >& v3,
                          const VecMath::Vector< 3 >& v4, const VecMath::Vector< 3 >& v5,
                          const VecMath::Vector< 3 >& v6, const VecMath::Vector< 3 >& v7);
    virtual void ApplyChanges(const ParameterMap& ) {}

  private:

    class Impl;

    Impl *pImpl_;

};

#endif