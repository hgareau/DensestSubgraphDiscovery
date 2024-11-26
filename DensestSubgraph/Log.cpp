#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "Log.h"

using namespace std;

void Log::write(string msg)
{
    try {
     /*       std::time_t currentTime = std::time(nullptr);
            std::tm* localTime = std::localtime(&currentTime);
            std::stringstream timeStream;
            timeStream << std::put_time(localTime, "%d-%b-%Y %H:%M:%S");
            std::string time = timeStream.str();*/
            string time = "test";
            string fileName = "./result/Efficiency.txt";

            ofstream of(fileName);
            of << time << "\t" << msg << endl;
            of.flush();
            of.close();
        } catch (exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
}
