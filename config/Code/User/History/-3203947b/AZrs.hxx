#pragma once
#include <string>

class Log {
public:
    static void info(const std::string& module_name, const std::string& message_format, ...);
    static void warn(const std::string& module_name, const std::string& message_format, ...);
    static void err(const std::string& module_name, const std::string& message_format, ...);

    static void ask(const std::string& module_name, const std::string& request);
};  