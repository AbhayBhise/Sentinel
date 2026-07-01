#include "sentinel/core/CoreEngine.hpp"
#include <iostream>
#include <thread>
#include <chrono>

namespace sentinel {
namespace core {

CoreEngine::CoreEngine(interfaces::ILogger& logger, 
                       std::unique_ptr<interfaces::IConfigurationProvider> configProvider)
    : m_logger(logger), 
      m_configProvider(std::move(configProvider)),
      m_running(false) 
{
}

CoreEngine::~CoreEngine() {
    stop();
}

Result<void> CoreEngine::initialize(const std::string& config_path) {
    printBanner();

    m_logger.info("Loading configuration from: " + config_path);
    if (!m_configProvider->load(config_path)) {
        return Result<void>::make_error("Failed to load configuration file: " + config_path);
    }

    const auto& config = m_configProvider->getConfig();
    if (config.monitors.empty()) {
        return Result<void>::make_error("Configuration error: No directories to monitor.");
    }

    m_logger.info("Configuration validated successfully.");
    
    // Initialize other services here in the future
    
    printEnvironmentInfo();
    
    m_logger.info("Sentinel Engine initialized successfully");
    
    return Result<void>();
}

void CoreEngine::run() {
    m_running = true;
    m_logger.info("Entering application loop...");

    while (m_running) {
        // Placeholder for the main event loop
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void CoreEngine::stop() {
    if (m_running) {
        m_logger.info("Initiating graceful shutdown...");
        m_running = false;
        
        // Stop worker threads and release resources here in the future
        
        m_logger.info("Shutdown complete.");
    }
}

void CoreEngine::printBanner() {
    m_logger.info("==========================================");
    m_logger.info("           SENTINEL ENGINE v0.1           ");
    m_logger.info("==========================================");
}

void CoreEngine::printEnvironmentInfo() {
    const auto& config = m_configProvider->getConfig();
    m_logger.info("Environment Info:");
    m_logger.info(" - Worker Threads: " + std::to_string(config.worker_threads));
    m_logger.info(" - Directories Monitored: " + std::to_string(config.monitors.size()));
}

} // namespace core
} // namespace sentinel
