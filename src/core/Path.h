#ifndef HEXPIP_PATH_H
#define HEXPIP_PATH_H

#include <string>

#ifdef __APPLE__
#include <mach-o/dyld.h>
#include <limits.h>
#elif defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#ifndef PATH_MAX
#define PATH_MAX MAX_PATH
#endif
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#endif

namespace Path {

inline std::string GetExecutablePath() {
    char buffer[PATH_MAX];

#ifdef __APPLE__
    uint32_t size = sizeof(buffer);
    if (_NSGetExecutablePath(buffer, &size) == 0) {
        return std::string(buffer);
    }
#elif defined(_WIN32)
    DWORD size = GetModuleFileNameA(NULL, buffer, sizeof(buffer));
    if (size > 0 && size < sizeof(buffer)) {
        return std::string(buffer);
    }
#elif defined(__linux__)
    ssize_t size = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (size != -1) {
        buffer[size] = '\0';
        return std::string(buffer);
    }
#endif

    return "";
}

inline std::string GetExecutableDir() {
    std::string exePath = GetExecutablePath();
    if (exePath.empty()) {
        return "";
    }

    size_t pos = exePath.find_last_of("/\\");
    if (pos != std::string::npos) {
        return exePath.substr(0, pos);
    }

    return "";
}

inline std::string GetAssetPath(const std::string& relPath) {
    std::string exeDir = GetExecutableDir();
    if (exeDir.empty()) {
        return relPath;
    }
    return exeDir + "/" + relPath;
}

}

#endif // HEXPIP_PATH_H
