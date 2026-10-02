#include "ResourceMonitor.h"
#include <fstream>
#include <sstream>
#include <string>
#include <sys/statvfs.h>
#include <unistd.h>

double ResourceMonitor::getCpuUsage() {
    std::ifstream file("/proc/stat");
    std::string line;

    if (!std::getline(file, line)) {
        return 0.0;
    }

    std::istringstream stream(line);
    std::string cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal;

    stream >> cpu >> user >> nice >> system >> idle
           >> iowait >> irq >> softirq >> steal;

    long total = user + nice + system + idle +
                 iowait + irq + softirq + steal;

    if (total == 0) {
        return 0.0;
    }

    return 100.0 * (total - idle) / total;
}

double ResourceMonitor::getMemoryUsage() {
    std::ifstream file("/proc/meminfo");

    std::string key;
    long total = 0;
    long available = 0;
    long value;
    std::string unit;

    while (file >> key >> value >> unit) {
        if (key == "MemTotal:") {
            total = value;
        }
        else if (key == "MemAvailable:") {
            available = value;
        }
    }

    if (total == 0) {
        return 0.0;
    }

    return 100.0 * (total - available) / total;
}

double ResourceMonitor::getDiskUsage() {
    struct statvfs stat;

    if (statvfs("/", &stat) != 0) {
        return 0.0;
    }

    unsigned long long total =
        static_cast<unsigned long long>(stat.f_blocks) * stat.f_frsize;

    unsigned long long available =
        static_cast<unsigned long long>(stat.f_bavail) * stat.f_frsize;

    if (total == 0) {
        return 0.0;
    }

    return 100.0 * (total - available) / total;
}
