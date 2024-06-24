#pragma once

class Log {
public:
    static void info(const char* module_name, const char* msg);
    static void info(const char* module_name, const char* message_format, ...);
    static void warn(const char* module_name, const char* msg);
    static void err(const char* module_name, const char* msg);

    static void ask(const char* module_name, const char* request);
};  