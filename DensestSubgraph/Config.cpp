#include <string>
#include "Config.h"

class Config {
public:
    static constexpr double kwFreq = 0.01; // consider all the words globally
    static constexpr int topKw = 20; // consider the keywords of each user locally

    // stem file paths
    static const std::string stemFile;
    static const std::string stopFile;

    // motif file paths
    static const std::string motifFile;

    // dataset file paths

    // query parameters
    static constexpr int k = 6; // the degree constraint

    // the # of queryId examples
    static constexpr int qIdNum = 300;

    // save parameters
    static constexpr int ccsSizeThreshold = 50; // community size

    // log path
    static const std::string logFilePath;

    // CODICIL parameter
    static constexpr int clusterK = 2500; // the number of clusters

    // public static int Motif_TYPE=1;
};

// Initialize static member variables
const std::string Config::stemFile = "./stemmer.lowercase.txt";
const std::string Config::stopFile = "./stopword.txt";
const std::string Config::motifFile = "./motif.txt";
const std::string Config::logFilePath = "./result/Efficiency.txt";
