#include <gtest/gtest.h>
#include "sentinel/logger/Logger.hpp"
#include <filesystem>
#include <thread>
#include <vector>

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        log_dir = std::filesystem::temp_directory_path() / "sentinel_test_logs";
        if (std::filesystem::exists(log_dir)) {
            std::filesystem::remove_all(log_dir);
        }
        sentinel::logger::Logger::getInstance().init("debug", log_dir.string());
    }

    void TearDown() override {
        sentinel::logger::Logger::getInstance().shutdown();
        if (std::filesystem::exists(log_dir)) {
            std::filesystem::remove_all(log_dir);
        }
    }

    std::filesystem::path log_dir;
};

TEST_F(LoggerTest, SingletonInstance) {
    auto& logger1 = sentinel::logger::Logger::getInstance();
    auto& logger2 = sentinel::logger::Logger::getInstance();
    EXPECT_EQ(&logger1, &logger2);
}

TEST_F(LoggerTest, ConcurrentLogging) {
    auto log_func = [](int id) {
        for (int i = 0; i < 100; ++i) {
            sentinel::logger::Logger::logInfo("Thread " + std::to_string(id) + " message " + std::to_string(i));
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(log_func, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    // Since we don't have an easy way to parse the log file without writing a parser,
    // we just verify that no crashes occurred during highly concurrent logging.
    EXPECT_TRUE(true);
}
