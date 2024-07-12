#include <string>

#ifndef LOG_H
#define LOG_H

class Log {
public:
    static void write(std::string msg);
};
#endif