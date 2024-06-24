#include "Log.hxx"
#include <iostream>

void Log::info(const char* module_name, const char* msg) {
    std::cout << module_name << "[INFO]: " << msg << "\n";
}

void Log::warn(const char* module_name, const char* msg) {
    std::cout << module_name << "[WARN]: " << msg << "\n";
}

void Log::err(const char* module_name, const char* msg) {
    std::cout << module_name << "[ERR]: " << msg << "\n";
}