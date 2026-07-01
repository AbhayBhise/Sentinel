#ifndef SENTINEL_CORE_RESULT_HPP
#define SENTINEL_CORE_RESULT_HPP

#include <string>
#include <variant>

namespace sentinel {
namespace core {

/**
 * @brief A lightweight expected-like type for error handling.
 * 
 * @tparam T The success type.
 * @tparam E The error type (defaults to std::string).
 */
template <typename T, typename E = std::string>
class Result {
public:
    /**
     * @brief Construct a successful result.
     * @param value The success value.
     */
    Result(T value) : m_data(std::move(value)), m_is_success(true) {}

    /**
     * @brief Construct an error result.
     * @param error The error value.
     * @param is_success Dummy boolean to differentiate from T if T and E are the same type.
     */
    Result(E error, bool /*is_success*/) : m_data(std::move(error)), m_is_success(false) {}

    /**
     * @brief Check if the result is a success.
     * @return true if successful.
     */
    explicit operator bool() const noexcept { return m_is_success; }

    /**
     * @brief Get the success value.
     * @return Reference to the success value.
     * @throws std::bad_variant_access if not successful.
     */
    const T& value() const { return std::get<T>(m_data); }
    T& value() { return std::get<T>(m_data); }

    /**
     * @brief Get the error value.
     * @return Reference to the error value.
     * @throws std::bad_variant_access if successful.
     */
    const E& error() const { return std::get<E>(m_data); }
    E& error() { return std::get<E>(m_data); }

    /**
     * @brief Helper to create an error result safely.
     * @param err The error value.
     * @return A Result containing the error.
     */
    static Result make_error(E err) {
        return Result(std::move(err), false);
    }

private:
    std::variant<T, E> m_data;
    bool m_is_success;
};

/**
 * @brief Specialization of Result for void success types.
 */
template <typename E>
class Result<void, E> {
public:
    Result() : m_is_success(true) {}
    Result(E error, bool /*is_success*/) : m_error(std::move(error)), m_is_success(false) {}

    explicit operator bool() const noexcept { return m_is_success; }

    const E& error() const { return m_error; }
    E& error() { return m_error; }

    static Result make_error(E err) {
        return Result(std::move(err), false);
    }

private:
    E m_error{};
    bool m_is_success;
};

} // namespace core
} // namespace sentinel

#endif // SENTINEL_CORE_RESULT_HPP
