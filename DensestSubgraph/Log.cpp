#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "Log.h"

void Log::write(std::string msg)
{
    try {
            std::time_t currentTime = std::time(nullptr);
            std::tm* localTime = std::localtime(&currentTime);
            std::stringstream timeStream;
            timeStream << std::put_time(localTime, "%d-%b-%Y %H:%M:%S");
            std::string time = timeStream.str();
            std::string fileName = "./result/Efficiency.txt";

            std::ofstream of(fileName);
            of << time << "\t" << msg << std::endl;
            of.flush();
            of.close();
        } catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
}
