#include "Log.hxx"
#include <iostream>

static void info(const char* module_name, const char* msg) {
    std::cout << module_name << "[INFO]: " << msg << "\n";
}

static void warn(const char* module_name, const char* msg) {

}

static void err(const char* module_name, const char* msg) {

}