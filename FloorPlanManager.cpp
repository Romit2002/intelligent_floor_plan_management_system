#include "FloorPlanManager.h"
#include <iostream>
#include <algorithm>
#include <ctime>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

FloorPlanManager::FloorPlanManager() {}


void FloorPlanManager::uploadPlan(int floorNumber, const std::vector<MeetingRoom>& rooms) {
    if (floorNumber - 1 >= meetingRoomsList.size()) {
        meetingRoomsList.resize(floorNumber); 
    }
    meetingRoomsList[floorNumber - 1] = rooms;
    std::cout << "Floor plan uploaded successfully for floor " << floorNumber << "!" << std::endl;
}


void FloorPlanManager::modifyPlan(int floorNumber, const std::vector<MeetingRoom>& rooms) {
    if (floorNumber - 1 < meetingRoomsList.size()) {
        meetingRoomsList[floorNumber - 1] = rooms; // Update the rooms
        std::cout << "Floor plan modified successfully for floor " << floorNumber << "!" << std::endl;
    } else {
        std::cout << "No floor plan found for floor " << floorNumber << "." << std::endl;
    }
}

std::pair<int, MeetingRoom*> FloorPlanManager::recommendRoom(int participants) {
    MeetingRoom* bestRoom = nullptr;
    int bestFloor = -1;
    std::time_t latestBookingTime = std::time(nullptr); 

    for (size_t floorIndex = 0; floorIndex < meetingRoomsList.size(); ++floorIndex) {
        auto& floor = meetingRoomsList[floorIndex]; 
        for (auto& room : floor) { 
            if (!room.isOccupied() && room.getCapacity() >= participants) {
                // Select room based on the least recently booked time
                if (room.getLastBookedTime() < latestBookingTime) {
                    bestRoom = &room;
                    bestFloor = static_cast<int>(floorIndex) + 1;
                    latestBookingTime = room.getLastBookedTime(); 
                }
            }
        }
    }

    if (bestRoom) {
        return {bestFloor, bestRoom}; 
    }
    return {-1, nullptr}; 
}

void FloorPlanManager::bookRoom(int participants) {
    auto f = recommendRoom(participants);
    auto floorNumber = f.first;
    auto recommendedRoom = f.second;
    
    if (floorNumber != -1) {
        std::cout<<GREEN << "Booking Room: " << recommendedRoom->getRoomName() << " (Floor " << floorNumber << ")\n"<<RESET;
        recommendedRoom->setOccupied(true);
        recommendedRoom->setLastBookedTime(std::time(nullptr)); 
    } else {
        std::cout <<RED<< "No available room found for " << participants << " participants.\n"<<RESET;
    }
}


void FloorPlanManager::displayPlans() const {
    if(meetingRoomsList.size()==0){
        std::cout<<RED<<"No floor plans to display!\n"<<RESET;
        return;
    }
    std::cout << "Displaying all floor plans:\n";
    for (size_t floorIndex = 0; floorIndex < meetingRoomsList.size(); ++floorIndex) {
        std::cout << "Floor " << floorIndex + 1 << ":\n";
        for (const auto& room : meetingRoomsList[floorIndex]) {
            std::cout << " - Room " << room.getRoomName() << " (Capacity: " << room.getCapacity() << ", "
                      << (room.isOccupied() ? "Occupied" : "Available") << ")\n";
        }
    }
}


void FloorPlanManager::resolveConflicts() {
    for (auto& floor : meetingRoomsList) {
        std::sort(floor.begin(), floor.end(), [](const MeetingRoom& a, const MeetingRoom& b) {
            
            
            if (a.getPriority() != b.getPriority()) {
                return a.getPriority() > b.getPriority();
            }
            if (a.getLastBookedTime() != b.getLastBookedTime()) {
                return a.getLastBookedTime() < b.getLastBookedTime();
            }
            if (a.getUserRole() != b.getUserRole()) {
                
                std::string rolePrecedence[] = {"Manager", "Lead", "Guest"};
                auto aRole = std::find(std::begin(rolePrecedence), std::end(rolePrecedence), a.getUserRole());
                auto bRole = std::find(std::begin(rolePrecedence), std::end(rolePrecedence), b.getUserRole());
                return aRole < bRole;
            }
            return false; 
        });

        if (!floor.empty()) {
            floor.front().setOccupied(true);
            std::cout << "Room " << floor.front().getRoomName() << " has been allocated based on conflicts resolved.\n";
        }
    }
}

