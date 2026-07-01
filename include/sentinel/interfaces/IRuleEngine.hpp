#ifndef SENTINEL_INTERFACES_IRULE_ENGINE_HPP
#define SENTINEL_INTERFACES_IRULE_ENGINE_HPP

namespace sentinel {
namespace interfaces {

/**
 * @brief Interface for evaluating rules against filesystem events.
 */
class IRuleEngine {
public:
    virtual ~IRuleEngine() = default;

    /**
     * @brief Initialize the rule engine.
     */
    virtual void initialize() = 0;
};

} // namespace interfaces
} // namespace sentinel

#endif // SENTINEL_INTERFACES_IRULE_ENGINE_HPP
