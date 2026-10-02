#include "SystemInfo.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/utsname.h>

void SystemInfo::displaySystemInfo() {
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == 0) {
        std::cout << "Hostname: " << hostname << '\n';
    }

    struct utsname systemInfo;

    if (uname(&systemInfo) == 0) {
        std::cout << "Kernel: " << systemInfo.release << '\n';
    }

    std::ifstream cpuFile("/proc/cpuinfo");
    std::string line;

    while (std::getline(cpuFile, line)) {
        if (line.find("model name") != std::string::npos) {
            std::cout << "CPU: " << line.substr(line.find(':') + 2) << '\n';
            break;
        }
    }

    std::ifstream memoryFile("/proc/meminfo");

    while (std::getline(memoryFile, line)) {
        if (line.find("MemTotal:") == 0) {
            std::cout << "Memory: " << line.substr(10) << '\n';
            break;
        }
    }
}
