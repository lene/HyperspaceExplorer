
#include "TransformationFactory.h"

TransformationFactory::Method TransformationFactory::method_ = TransformationFactory::Singlethreaded;

void TransformationFactory::setTransformationMethod(const TransformationFactory::Method &method) {
    method_ = method;
}

TransformationFactory::Method TransformationFactory::getTransformationMethod() {
    return method_;
}

