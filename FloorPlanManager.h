#ifndef FLOORPLANMANAGER_H
#define FLOORPLANMANAGER_H
#pragma once
#include "MeetingRoom.h"
#include <vector>
#include <string>

class FloorPlanManager {
public:
    FloorPlanManager(); 
    void uploadPlan(int floorNumber, const std::vector<MeetingRoom>& rooms); 
    void modifyPlan(int floorNumber, const std::vector<MeetingRoom>& rooms); 
    void displayPlans() const;
    void resolveConflicts();
    void bookRoom(int participants);
    std::pair<int, MeetingRoom*> recommendRoom(int participants); 

private:
    std::vector<std::string> plans; 
    std::vector<std::vector<MeetingRoom>> meetingRoomsList; 
};

#endif 
