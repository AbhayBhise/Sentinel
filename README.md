# Sentinel
Enterprise-grade File Integrity Monitoring and Threat Detection Engine built with Modern C++20, Linux, STL, OpenSSL, and CMake.

**Real-Time File Integrity Monitoring & Threat Detection Engine**

Sentinel is a lightweight, high-performance File Integrity Monitoring (FIM) and threat detection engine built in modern C++20. It continuously monitors target directories for changes, calculates secure SHA-256 hashes, applies configurable rules, and detects suspicious behavioral patterns to protect enterprise systems.

## Features

- **Real-time Directory Monitoring**: Efficiently monitors files for modifications, creations, deletions, and metadata changes using native Linux `inotify`.
- **Integrity Verification**: Secure SHA-256 hashing to verify file integrity.
- **Rule Engine**: Define robust monitoring rules, paths, and severity thresholds using JSON.
- **Threat Detection**: Automatically identifies suspicious behaviors like rapid modifications or mass deletions.
- **High Performance**: Built with C++20 taking advantage of multithreading, move semantics, and efficient I/O operations.
- **Reporting & Logging**: Structured JSON logging and HTML report generation.

## Requirements

- **Platform**: Ubuntu 22.04+ (Linux native)
- **Compiler**: GCC 11+ or Clang 14+ (C++20 support required)
- **Build System**: CMake 3.20+
- **Dependencies**: OpenSSL

## Build Instructions

```bash
# Clone the repository
git clone https://github.com/AbhayBhise/Sentinel.git
cd Sentinel

# Configure and build
cmake -B build
cmake --build build

# Run tests
ctest --test-dir build
```

## Usage

```bash
# Start monitoring
sentinel monitor --config configs/default_config.json
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
