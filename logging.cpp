#include "logging.h"
#include <fstream>

std::ofstream outFile;

void logging::OpenLog() {
    outFile.open("FractaSketch_log.txt");
}

void logging::CloseLog() {
    outFile.close();
}

void logging::AddToLog(std::string msg) {
    if(!outFile.is_open())
        return;
    outFile << msg << "\n";
}
