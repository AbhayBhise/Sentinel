#ifndef SENTINEL_INTERFACES_ICONFIGURATION_PROVIDER_HPP
#define SENTINEL_INTERFACES_ICONFIGURATION_PROVIDER_HPP

#include "sentinel/config/AppConfig.hpp"
#include <filesystem>

namespace sentinel {
namespace interfaces {

/**
 * @brief Interface for providing configuration settings to the application.
 */
class IConfigurationProvider {
public:
    virtual ~IConfigurationProvider() = default;

    /**
     * @brief Load the configuration from the specified path.
     * @param filepath Path to the configuration file.
     * @return true if loading succeeds, false otherwise.
     */
    virtual bool load(const std::filesystem::path& filepath) = 0;

    /**
     * @brief Get the loaded application configuration.
     * @return Constant reference to the configuration structure.
     */
    [[nodiscard]] virtual const config::AppConfig& getConfig() const noexcept = 0;
};

} // namespace interfaces
} // namespace sentinel

#endif // SENTINEL_INTERFACES_ICONFIGURATION_PROVIDER_HPP
