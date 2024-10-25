cmake_minimum_required(VERSION 3.10)
project(IntelligentFloorPlanManagement)

set(CMAKE_CXX_STANDARD 11)

add_executable(IntelligentFloorPlanManagement main.cpp 
    FloorPlanManager.cpp 
    MeetingRoom.cpp 
    OfflineManager.cpp 
    Authentication.cpp)
