#include "MockView.h"

struct MockView::Impl {
  Impl(bool verbose): verbose_(verbose) { }

  bool verbose_;
};

MockView::MockView(bool verbose): pImpl_(new Impl(verbose)) { }

void MockView::drawCube(const VecMath::Vector< 3 >& v0, const VecMath::Vector< 3 >& v1,
                        const VecMath::Vector< 3 >& v2, const VecMath::Vector< 3 >& v3,
                        const VecMath::Vector< 3 >& v4, const VecMath::Vector< 3 >& v5,
                        const VecMath::Vector< 3 >& v6, const VecMath::Vector< 3 >& v7) {
  if (pImpl_->verbose_) {
    std::cerr << "drawCube(" << v0 << ", " << v1 << ", " << v2 << ", " << v3 << ", "
                             << v4 << ", " << v5 << ", " << v6 << ", " << v7 << ")" << std::endl;
  }
}
