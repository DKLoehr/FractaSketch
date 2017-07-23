#include <string>

namespace logging {
    void OpenLog();
    void AddToLog(std::string msg);
    void CloseLog();
}
