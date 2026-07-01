#include <gtest/gtest.h>
#include "sentinel/config/ConfigManager.hpp"
#include <fstream>
#include <filesystem>

class ConfigManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_config_path = std::filesystem::temp_directory_path() / "test_config.json";
        std::ofstream out(test_config_path);
        out << R"({
            "log_level": "debug",
            "report_directory": "/tmp/reports",
            "worker_threads": 8,
            "monitors": [
                {
                    "path": "/var/www",
                    "recursive": false,
                    "exclude_paths": ["/var/www/tmp"],
                    "allowed_extensions": [".php", ".html"]
                }
            ]
        })";
        out.close();
    }

    void TearDown() override {
        if (std::filesystem::exists(test_config_path)) {
            std::filesystem::remove(test_config_path);
        }
    }

    std::filesystem::path test_config_path;
};

TEST_F(ConfigManagerTest, LoadValidConfig) {
    sentinel::config::ConfigManager manager;
    ASSERT_TRUE(manager.load(test_config_path));
    
    const auto& config = manager.getConfig();
    EXPECT_EQ(config.log_level, "debug");
    EXPECT_EQ(config.report_directory, "/tmp/reports");
    EXPECT_EQ(config.worker_threads, 8);
    
    ASSERT_EQ(config.monitors.size(), 1);
    EXPECT_EQ(config.monitors[0].path, "/var/www");
    EXPECT_FALSE(config.monitors[0].recursive);
    
    ASSERT_EQ(config.monitors[0].exclude_paths.size(), 1);
    EXPECT_EQ(config.monitors[0].exclude_paths[0], "/var/www/tmp");
    
    ASSERT_EQ(config.monitors[0].allowed_extensions.size(), 2);
    EXPECT_EQ(config.monitors[0].allowed_extensions[0], ".php");
}

TEST_F(ConfigManagerTest, LoadNonExistentConfig) {
    sentinel::config::ConfigManager manager;
    EXPECT_FALSE(manager.load("non_existent_path_xyz123.json"));
}
