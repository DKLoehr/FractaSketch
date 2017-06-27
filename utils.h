#include <string>

// On Macs, converts relative paths to absolute paths that
// are siblings of the app. Returns its input on Windows
// or if the input is already absolute
std::string GetProperPath(std::string filename);