#pragma once

class Log {
public:
    static void info(const char* module_name, const char* msg);
    static void warn(const char* module_name, const char* msg);
    static void err(const char* module_name, const char* msg);
};  