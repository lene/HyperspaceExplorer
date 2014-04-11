
#include "TestRunner.h"

#include <typeinfo>
#include <algorithm>
#include <memory>

struct TestRunner::Impl {

    Impl(): executedTestSuites_(0), failedTestSuites_(), startTime_(clock()) { }

    void printFailedTestSuites() const;

    static void printFailedTestSuite(std::string suite);


    unsigned executedTestSuites_;
    std::vector<std::string> failedTestSuites_;

    clock_t startTime_;

};

TestRunner::TestRunner():
    pImpl(new Impl) { }

void TestRunner::add(QObject *test) {
    if (QTest::qExec(test)) pImpl->failedTestSuites_.push_back(typeid(*test).name());
    pImpl->executedTestSuites_++;
}

void TestRunner::printSummary() const {
    double timeElapsed = double(clock()-pImpl->startTime_)/CLOCKS_PER_SEC;
    if (!pImpl->failedTestSuites_.empty()) qDebug() << QString(80, '*');
    qDebug() << "Tests finished in " << timeElapsed << " seconds.";
    qDebug() << pImpl->failedTestSuites_.size() << " Test suites out of " << pImpl->executedTestSuites_ << " failed.";
    if (!pImpl->failedTestSuites_.empty()) pImpl->printFailedTestSuites();
    if (!pImpl->failedTestSuites_.empty()) qDebug() << QString(80, '*');
}

unsigned TestRunner::exitValue() const {
    return pImpl->failedTestSuites_.size();
}

void TestRunner::Impl::printFailedTestSuites() const {
    std::for_each(failedTestSuites_.begin(), failedTestSuites_.end(), printFailedTestSuite);
}

void TestRunner::Impl::printFailedTestSuite(std::string suite) {
    qDebug() << "    " << suite.c_str();
}
