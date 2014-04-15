
#include "TestRunner.h"

#include <typeinfo>
#include <algorithm>
#include <memory>
#include <qt5/QtCore/qobject.h>

struct TestRunner::Impl {

    Impl(): executedTestSuites_(0), failedTestSuites_(), startTime_(clock()) { }

    void printFailedTestSuites() const;

    static void printFailedTestSuite(std::string suite);


    unsigned executedTestSuites_;
    std::vector<QObject *> tests_to_run_;
    std::vector<std::string> failedTestSuites_;

    clock_t startTime_;
    bool has_run_ = false;
    
};

TestRunner::TestRunner():
    pImpl(new Impl) {
}

TestRunner::~TestRunner() {
    if (pImpl->has_run_) return;
    run();
    printSummary();
}

void TestRunner::add(QObject *test) {
    pImpl->tests_to_run_.push_back(test);
}

void TestRunner::run() {
    QStringList args;
    args.append("-o /tmp/out");
//    args.append("");
    for (QObject *test: pImpl->tests_to_run_) {
        if (QTest::qExec(test, QStringList(args))) pImpl->failedTestSuites_.push_back(typeid(*test).name());
        pImpl->executedTestSuites_++;
    }
    pImpl->has_run_ = true;
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
