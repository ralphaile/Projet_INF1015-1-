/**
 * @file CustomExceptions.hpp
 * @brief This file contains the declaration of custom exception classes used within the project. 
 * These exceptions are designed to handle specific error conditions, such as the "TooManyKingsException" when there are more than two kings on the board.
 */

#pragma once
#include <exception>
#include <string>

class TooManyKingsException : public std::exception {
public:
    explicit TooManyKingsException(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string m_message;
};