#pragma once

class Log {
public:
    static void info(const char* module_name, const char* message_format, ...);
    static void warn(const char* module_name, const char* message_format, ...);
    static void err(const char* module_name, const char* message_format, ...);

    static void ask(const char* module_name, const char* request);
};  