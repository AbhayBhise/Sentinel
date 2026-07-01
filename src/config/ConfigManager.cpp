#include "sentinel/config/ConfigManager.hpp"
#include <fstream>
#include <iostream>

namespace sentinel {
namespace config {

bool ConfigManager::load(const std::filesystem::path& filepath) {
    if (!std::filesystem::exists(filepath)) {
        std::cerr << "Config file does not exist: " << filepath << "\n";
        return false;
    }

    try {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Failed to open config file: " << filepath << "\n";
            return false;
        }

        nlohmann::json j;
        file >> j;

        if (j.contains("log_level") && j["log_level"].is_string()) {
            m_config.log_level = j["log_level"].get<std::string>();
        }

        if (j.contains("report_directory") && j["report_directory"].is_string()) {
            m_config.report_directory = j["report_directory"].get<std::string>();
        }

        if (j.contains("worker_threads") && j["worker_threads"].is_number_integer()) {
            m_config.worker_threads = j["worker_threads"].get<int>();
        }

        if (j.contains("monitors") && j["monitors"].is_array()) {
            m_config.monitors.clear();
            for (const auto& item : j["monitors"]) {
                MonitorConfig mc;
                if (item.contains("path") && item["path"].is_string()) {
                    mc.path = item["path"].get<std::string>();
                }
                if (item.contains("recursive") && item["recursive"].is_boolean()) {
                    mc.recursive = item["recursive"].get<bool>();
                }
                if (item.contains("exclude_paths") && item["exclude_paths"].is_array()) {
                    for (const auto& exclude : item["exclude_paths"]) {
                        mc.exclude_paths.push_back(exclude.get<std::string>());
                    }
                }
                if (item.contains("allowed_extensions") && item["allowed_extensions"].is_array()) {
                    for (const auto& ext : item["allowed_extensions"]) {
                        mc.allowed_extensions.push_back(ext.get<std::string>());
                    }
                }
                m_config.monitors.push_back(mc);
            }
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to parse config file: " << e.what() << "\n";
        return false;
    }
}

const AppConfig& ConfigManager::getConfig() const noexcept {
    return m_config;
}

} // namespace config
} // namespace sentinel
