#ifndef SENTINEL_CONFIG_MANAGER_HPP
#define SENTINEL_CONFIG_MANAGER_HPP

#include <string>
#include <vector>
#include <filesystem>
#include "sentinel/config/AppConfig.hpp"
#include "sentinel/interfaces/IConfigurationProvider.hpp"

namespace sentinel {
namespace config {

/**
 * @brief Manages loading and validating configuration.
 */
class ConfigManager : public interfaces::IConfigurationProvider {
public:
    ~ConfigManager() override = default;

    /**
     * @brief Loads configuration from a JSON file.
     * @param filepath Path to the JSON configuration file.
     * @return true if successful, false otherwise.
     */
    bool load(const std::filesystem::path& filepath) override;

    /**
     * @brief Gets the current configuration.
     * @return The loaded configuration.
     */
    [[nodiscard]] const AppConfig& getConfig() const noexcept override;

private:
    AppConfig m_config;
};

} // namespace config
} // namespace sentinel

#endif // SENTINEL_CONFIG_MANAGER_HPP
