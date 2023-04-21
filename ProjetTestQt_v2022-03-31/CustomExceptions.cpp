#include "CustomExceptions.hpp"

TooManyKingsException::TooManyKingsException(const std::string& message) : m_message(message) {}

const char* TooManyKingsException::what() const noexcept {
    return m_message.c_str();
}