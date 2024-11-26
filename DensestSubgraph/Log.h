#include <string>

using namespace std;

#ifndef LOG_H
#define LOG_H

class Log {
public:
    static void write(string msg);
};
#endif