#include "Log.hxx"
#include <iostream>
#include <cstdarg>

void Log::info(const std::string& module_name, const std::string& message_format, ...) {
    va_list args;
    va_start(args, message_format);
    char buffer[256]; // Adjust the buffer size as needed

    // Format the message using vsnprintf
    vsnprintf(buffer, sizeof(buffer), message_format.c_str(), args);

    // Print the formatted message
    std::cout << "[" << module_name << "] [INFO]: " << buffer << std::endl;

    va_end(args);
}

void Log::warn(const std::string& module_name, const std::string& message_format, ...) {
    va_list args;
    va_start(args, message_format);
    char buffer[256]; // Adjust the buffer size as needed

    // Format the message using vsnprintf
    vsnprintf(buffer, sizeof(buffer), message_format.c_str(), args);

    // Print the formatted message
    std::cout << "[" << module_name << "] [WARN]: " << buffer << std::endl;

    va_end(args);
}

void Log::err(const std::string& module_name, const std::string& message_format, ...) {
    va_list args;
    va_start(args, message_format);
    char buffer[256]; // Adjust the buffer size as needed

    // Format the message using vsnprintf
    vsnprintf(buffer, sizeof(buffer), message_format.c_str(), args);

    // Print the formatted message
    std::cout << "[" << module_name << "] [ERR]: " << buffer << std::endl;

    va_end(args);
}

void Log::ask(const std::string& module_name, const std::string& request) {
    std::cout << "[" << module_name << "]  " << request;
}

void Log::spacing() {
    std::cout << "\n\n";
}