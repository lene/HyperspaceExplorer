
#include "TestRunner.h"

#include <typeinfo>
#include <algorithm>
#include <memory>
#include <iostream>

#include <QObject>
#include <QtConcurrent>

struct TestRunner::Impl {

    Impl(): executedTestSuites_(0), failedTestSuites_(), startTime_(clock()) { }

    void printFailedTestSuites() const;

    static void printFailedTestSuite(std::string suite);
    static QString getTestOutputFile(const QObject *test);
    static void printTestResults(const QObject *test);

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
    runAll();
    printSummary();
}

void TestRunner::add(QObject *test) {
    pImpl->tests_to_run_.push_back(test);
}

void TestRunner::runAll() {
    
    if (pImpl->has_run_) return;

#if 0    
    QtConcurrent::blockingMap(pImpl->tests_to_run_, [&](QObject *test) { runTest(test); });
#else    
    for (QObject *test: pImpl->tests_to_run_) {
        runTest(test);
    }
#endif    
    pImpl->has_run_ = true;
}

void TestRunner::runTest(QObject* test) {
    QStringList args;
    args << " " << "-o" << Impl::getTestOutputFile(test);
    if (QTest::qExec(test, args)) pImpl->failedTestSuites_.push_back(typeid(*test).name());
    pImpl->executedTestSuites_++;
    Impl::printTestResults(test);

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

QString TestRunner::Impl::getTestOutputFile(const QObject* test) {
    
    QString testname = typeid(*test).name();
    return "/tmp/"+testname+".out";
}

void TestRunner::Impl::printTestResults(const QObject* test) {
    QFile file(TestRunner::Impl::getTestOutputFile(test));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        qDebug() << in.readLine();
    }
}
