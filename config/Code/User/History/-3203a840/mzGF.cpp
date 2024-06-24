#include "Log.hxx"
#include <iostream>
#include <cstdarg>

void Log::info(const char* module_name, const char* message_format, ...) {
    va_list args;
    va_start(args, message_format);
    char buffer[256]; // Adjust the buffer size as needed

    // Format the message using vsnprintf
    vsnprintf(buffer, sizeof(buffer), message_format, args);

    // Print the formatted message
    std::cout << "[" << module_name << "] [INFO]: " << buffer << std::endl;

    va_end(args);
}

void Log::warn(const char* module_name, const char* message_format, ...); {
    std::cout << "[" << module_name << "]" << "[WARN]: " << msg << "\n";
}

void Log::err(const char* module_name, const char* message_format, ...); {
    std::cout << "[" << module_name << "]" << "[ERR]: " << msg << "\n";
}

void Log::ask(const char* module_name, const char* request) {
    std::cout << "[" << module_name << "]  " << request << " : ";
}