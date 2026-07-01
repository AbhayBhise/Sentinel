#ifndef SENTINEL_INTERFACES_IFILE_WATCHER_HPP
#define SENTINEL_INTERFACES_IFILE_WATCHER_HPP

namespace sentinel {
namespace interfaces {

/**
 * @brief Interface for filesystem monitoring capabilities.
 */
class IFileWatcher {
public:
    virtual ~IFileWatcher() = default;

    /**
     * @brief Start watching the configured directories.
     */
    virtual void start() = 0;

    /**
     * @brief Stop watching directories.
     */
    virtual void stop() = 0;
};

} // namespace interfaces
} // namespace sentinel

#endif // SENTINEL_INTERFACES_IFILE_WATCHER_HPP
