#include "sentinel/core/CoreEngine.hpp"
#include "sentinel/logger/Logger.hpp"
#include "sentinel/config/ConfigManager.hpp"
#include <iostream>
#include <memory>
#include <cstdlib>

int main(int argc, char** argv) {
    // 1. Initialize Logger
    auto& logger = sentinel::logger::Logger::getInstance();
    
    // For now, hardcode initial log level and dir. In a real app, this might come from CLI args
    // before the config is fully loaded.
    logger.init("info", "logs");

    std::string config_path = "configs/default_config.json";
    if (argc > 1) {
        config_path = argv[1];
    }

    // 2. Instantiate DI dependencies
    auto configProvider = std::make_unique<sentinel::config::ConfigManager>();

    // 3. Create Core Engine
    sentinel::core::CoreEngine engine(logger, std::move(configProvider));

    // 4. Initialize Core Engine (Loads config, validates, initializes services)
    auto result = engine.initialize(config_path);
    if (!result) {
        logger.error("Initialization failed: " + result.error());
        logger.shutdown();
        return EXIT_FAILURE;
    }

    // 5. Enter application loop
    engine.run();

    // 6. Graceful shutdown
    logger.shutdown();
    return EXIT_SUCCESS;
}
