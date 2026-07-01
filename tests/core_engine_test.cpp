#include <gtest/gtest.h>
#include "sentinel/core/CoreEngine.hpp"
#include "sentinel/logger/Logger.hpp"
#include "sentinel/config/ConfigManager.hpp"
#include <filesystem>
#include <fstream>
#include <thread>
#include <atomic>

class CoreEngineTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup logger
        log_dir = std::filesystem::temp_directory_path() / "sentinel_test_logs";
        if (std::filesystem::exists(log_dir)) {
            std::filesystem::remove_all(log_dir);
        }
        sentinel::logger::Logger::getInstance().init("debug", log_dir.string());
        
        // Setup valid config
        valid_config_path = std::filesystem::temp_directory_path() / "valid_test_config.json";
        std::ofstream out(valid_config_path);
        out << R"({
            "log_level": "debug",
            "report_directory": "reports",
            "worker_threads": 2,
            "monitors": [
                {
                    "path": "/tmp",
                    "recursive": true
                }
            ]
        })";
        out.close();

        // Setup invalid config
        invalid_config_path = std::filesystem::temp_directory_path() / "invalid_test_config.json";
        std::ofstream out2(invalid_config_path);
        out2 << R"({
            "monitors": []
        })";
        out2.close();
    }

    void TearDown() override {
        sentinel::logger::Logger::getInstance().shutdown();
        if (std::filesystem::exists(log_dir)) {
            std::filesystem::remove_all(log_dir);
        }
        if (std::filesystem::exists(valid_config_path)) {
            std::filesystem::remove(valid_config_path);
        }
        if (std::filesystem::exists(invalid_config_path)) {
            std::filesystem::remove(invalid_config_path);
        }
    }

    std::filesystem::path log_dir;
    std::filesystem::path valid_config_path;
    std::filesystem::path invalid_config_path;
};

TEST_F(CoreEngineTest, InitializationWithValidConfig) {
    auto configProvider = std::make_unique<sentinel::config::ConfigManager>();
    sentinel::core::CoreEngine engine(sentinel::logger::Logger::getInstance(), std::move(configProvider));

    auto result = engine.initialize(valid_config_path.string());
    EXPECT_TRUE(static_cast<bool>(result));
}

TEST_F(CoreEngineTest, InitializationWithInvalidConfig) {
    auto configProvider = std::make_unique<sentinel::config::ConfigManager>();
    sentinel::core::CoreEngine engine(sentinel::logger::Logger::getInstance(), std::move(configProvider));

    auto result = engine.initialize(invalid_config_path.string());
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.error(), "Configuration error: No directories to monitor.");
}

TEST_F(CoreEngineTest, InitializationWithMissingConfig) {
    auto configProvider = std::make_unique<sentinel::config::ConfigManager>();
    sentinel::core::CoreEngine engine(sentinel::logger::Logger::getInstance(), std::move(configProvider));

    auto result = engine.initialize("does_not_exist.json");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.error(), "Failed to load configuration file: does_not_exist.json");
}

TEST_F(CoreEngineTest, EngineLifecycle) {
    auto configProvider = std::make_unique<sentinel::config::ConfigManager>();
    sentinel::core::CoreEngine engine(sentinel::logger::Logger::getInstance(), std::move(configProvider));

    auto result = engine.initialize(valid_config_path.string());
    ASSERT_TRUE(static_cast<bool>(result));

    std::atomic<bool> thread_started{false};
    std::thread engine_thread([&engine, &thread_started]() {
        thread_started = true;
        engine.run();
    });

    // Wait for it to start
    while (!thread_started) {
        std::this_thread::yield();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    engine.stop();
    engine_thread.join();
    
    // If it successfully joins, the lifecycle completed gracefully.
    EXPECT_TRUE(true);
}
