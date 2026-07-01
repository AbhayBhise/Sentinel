#ifndef SENTINEL_CONFIG_APP_CONFIG_HPP
#define SENTINEL_CONFIG_APP_CONFIG_HPP

#include <string>
#include <vector>

namespace sentinel {
namespace config {

/**
 * @brief Represents the configuration for a directory to be monitored.
 */
struct MonitorConfig {
    std::string path;
    bool recursive{true};
    std::vector<std::string> exclude_paths;
    std::vector<std::string> allowed_extensions;
};

/**
 * @brief Holds the entire application configuration.
 */
struct AppConfig {
    std::vector<MonitorConfig> monitors;
    std::string log_level{"info"};
    std::string report_directory{"reports"};
    int worker_threads{4};
};

} // namespace config
} // namespace sentinel

#endif // SENTINEL_CONFIG_APP_CONFIG_HPP
