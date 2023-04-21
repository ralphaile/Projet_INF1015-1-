#pragma once
#include <exception>
#include <string>

// English suffix
class TooManyKingsException : public std::exception {
public:
    explicit TooManyKingsException(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string m_message;
};