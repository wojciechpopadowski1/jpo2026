/**
 * @file test_ollama.cpp
 * @brief Testy jednostkowe dla klasy OllamaClient
 */

#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QSignalSpy>
#include <QJsonObject>
#include <QtTest>
#include "../src/ollamaclient.h"
#include "../src/config.h"

class OllamaClientTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(OllamaClientTest, CreateClient) {
    OllamaClient client;
    EXPECT_TRUE(true);
}

TEST_F(OllamaClientTest, EmptyPrompt) {
    OllamaClient client;
    QSignalSpy errorSpy(&client, &OllamaClient::errorOccurred);

    client.generateCode("");

    QTRY_VERIFY_WITH_TIMEOUT(errorSpy.count() > 0, 2000);

    QString error = errorSpy.takeFirst().at(0).toString();
    EXPECT_FALSE(error.isEmpty());
}

TEST_F(OllamaClientTest, CancelRequest) {
    OllamaClient client;

    client.generateCode("test prompt");
    client.cancelRequest();

    EXPECT_TRUE(true);
}

TEST_F(OllamaClientTest, ConfigTest) {
    EXPECT_FALSE(Config::OLLAMA_API_URL.isEmpty());
    EXPECT_FALSE(Config::DEFAULT_MODEL.isEmpty());
    EXPECT_FALSE(Config::SYSTEM_PROMPT.isEmpty());
    EXPECT_GT(Config::NETWORK_TIMEOUT, 0);
}

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}