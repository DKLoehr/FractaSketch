#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#endif

#include "utils.h"

std::string GetProperPath(std::string filename) {
    // This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        return "";
    }
    CFRelease(resourcesURL);

    std::string cwd(path);
    cwd = cwd.substr(0, cwd.find_last_of('/'));
    cwd = cwd.substr(0, cwd.find_last_of('/'));
    cwd = cwd.substr(0, cwd.find_last_of('/'));
    filename = cwd + "/" + filename;

#endif
    return filename;
}
