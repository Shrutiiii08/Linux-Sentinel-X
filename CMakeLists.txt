cmake_minimum_required(VERSION 3.10)

project(LinuxSentinelX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(linux-sentinel-x
    src/main.cpp
    src/SystemInfo.cpp
    src/ResourceMonitor.cpp
    src/ProcessMonitor.cpp
    src/FailureDetector.cpp
    src/RecoveryManager.cpp
    src/Logger.cpp
    src/ConfigManager.cpp
)
