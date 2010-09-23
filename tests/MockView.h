#ifndef MOCKVIEW_H
#define MOCKVIEW_H 1

#include "ViewImpl.h"

/// Class for testing behavior on View objects
/** This does not have any implementation yet
 */
class MockView: public UI::ViewImpl {
  
  public:
  
    template <unsigned D>
    struct Face {
      Face(const VecMath::Vector<D> &v0, const VecMath::Vector<D> &v1, 
           const VecMath::Vector<D> &v2, const VecMath::Vector<D> &v3);
      bool operator==(const Face<D> &other) const;
      std::vector< VecMath::Vector<D> > vertex_;
    };
    
    MockView(bool verbose = false);
    virtual void ObjectHypercube() {}
    virtual void ObjectHyperpyramid() {}
    virtual void ObjectHypersponge() {}
    virtual void ObjectGasket() {}
    virtual void ObjectRotope() {}
    virtual void applyTransform(const VecMath::Rotation< 4 >& , const VecMath::Vector< 4 >& ) {}
    virtual void animate() {}
    virtual void setSize(unsigned int , unsigned int ) {}
    virtual void drawVertex(const VecMath::Vector< 4 >& x, const VecMath::Vector< 3 >& xscr);
    virtual void drawLine(const VecMath::Vector< 4 >& x0, const VecMath::Vector< 4 >& x1, 
                          const VecMath::Vector< 3 >& xscr0, const VecMath::Vector< 3 >& xscr1);
    virtual void drawQuadrangle(const VecMath::Vector< 4 >& x0, const VecMath::Vector< 4 >& x1, 
                                const VecMath::Vector< 4 >& x2, const VecMath::Vector< 4 >& x3, 
                                const VecMath::Vector< 3 >& xscr0, const VecMath::Vector< 3 >& xscr1, 
                                const VecMath::Vector< 3 >& xscr2, const VecMath::Vector< 3 >& xscr3);                              
    virtual void ApplyChanges(const ParameterMap& ) {}

    /// Tests whether a specified vertex has been drawn
    bool isVertexDrawn(const VecMath::Vector<3>& vertex) const;
    /// Tests whether a specified 4D vertex has been drawn
    bool isVertexPresent(const VecMath::Vector<4>& vertex) const;
    /// Returns the number of drawn vertices
    unsigned numVerticesDrawn() const;

    template <unsigned D> bool isFaceDrawn(const Face<D> &face) const;
    
    /// Debugging output
    void printVertices() const;

  private:

    class Impl;

    Impl *pImpl_;

};

#endif