/**
 * @file test_executor.cpp
 * @brief Testy jednostkowe dla klasy PythonExecutor
 */

#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QSignalSpy>
#include <QEventLoop>
#include <QTimer>
#include <QtTest>
#include "../src/pythonexecutor.h"

class PythonExecutorTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PythonExecutorTest, ExecuteSimpleCode) {
    PythonExecutor executor;
    QSignalSpy finishedSpy(&executor, &PythonExecutor::executionFinished);

    executor.executeCode("print('Hello, World!')");

    QTRY_VERIFY_WITH_TIMEOUT(finishedSpy.count() > 0, 5000);

    QString output = finishedSpy.takeFirst().at(0).toString();
    EXPECT_TRUE(output.contains("Hello, World!"));
}

TEST_F(PythonExecutorTest, ExecuteCalculation) {
    PythonExecutor executor;
    QSignalSpy finishedSpy(&executor, &PythonExecutor::executionFinished);

    executor.executeCode("result = 2 + 2\nprint(result)");

    QTRY_VERIFY_WITH_TIMEOUT(finishedSpy.count() > 0, 5000);

    QString output = finishedSpy.takeFirst().at(0).toString();
    EXPECT_TRUE(output.contains("4"));
}

TEST_F(PythonExecutorTest, SyntaxError) {
    PythonExecutor executor;
    QSignalSpy errorSpy(&executor, &PythonExecutor::executionError);

    executor.executeCode("print('Hello'");

    QTRY_VERIFY_WITH_TIMEOUT(errorSpy.count() > 0, 5000);

    QString error = errorSpy.takeFirst().at(0).toString();
    EXPECT_FALSE(error.isEmpty());
}

TEST_F(PythonExecutorTest, EmptyCode) {
    PythonExecutor executor;
    QSignalSpy errorSpy(&executor, &PythonExecutor::executionError);

    executor.executeCode("");

    QTRY_VERIFY_WITH_TIMEOUT(errorSpy.count() > 0, 2000);
    EXPECT_GT(errorSpy.count(), 0);
}

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}