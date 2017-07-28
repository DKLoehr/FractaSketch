#include "logging.h"
#include "utils.h"
#include <fstream>

std::ofstream outFile;

void logging::OpenLog() {
    std::string filename = GetProperPath("FractaSketch_log.txt");
    outFile.open(filename);
}

void logging::CloseLog() {
    outFile.close();
}

void logging::AddToLog(std::string msg) {
    if(!outFile.is_open())
        return;
    outFile << msg << "\n";
}
