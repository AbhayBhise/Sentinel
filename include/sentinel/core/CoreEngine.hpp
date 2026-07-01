#ifndef SENTINEL_CORE_CORE_ENGINE_HPP
#define SENTINEL_CORE_CORE_ENGINE_HPP

#include "sentinel/interfaces/IConfigurationProvider.hpp"
#include "sentinel/interfaces/ILogger.hpp"
#include "sentinel/core/Result.hpp"
#include <memory>
#include <string>

namespace sentinel {
namespace core {

/**
 * @brief The Core Engine of the Sentinel application.
 * Manages the application lifecycle and coordinates between subsystems.
 */
class CoreEngine {
public:
    /**
     * @brief Construct a new Core Engine object
     * 
     * @param logger Reference to the logger interface.
     * @param configProvider Unique pointer to the configuration provider.
     */
    CoreEngine(interfaces::ILogger& logger, 
               std::unique_ptr<interfaces::IConfigurationProvider> configProvider);

    ~CoreEngine();

    /**
     * @brief Initializes the core engine and its subsystems.
     * 
     * @param config_path Path to the JSON configuration file.
     * @return Result<void> Success or error message.
     */
    Result<void> initialize(const std::string& config_path);

    /**
     * @brief Runs the main application loop.
     */
    void run();

    /**
     * @brief Stops the application and initiates graceful shutdown.
     */
    void stop();

private:
    void printBanner();
    void printEnvironmentInfo();

    interfaces::ILogger& m_logger;
    std::unique_ptr<interfaces::IConfigurationProvider> m_configProvider;
    bool m_running;
};

} // namespace core
} // namespace sentinel

#endif // SENTINEL_CORE_CORE_ENGINE_HPP
