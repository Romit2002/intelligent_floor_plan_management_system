#pragma once
#include <string>
#include <ctime>

class MeetingRoom {
private:
    int id;
    std::string name;
    int capacity;
    bool occupied;
    std::time_t lastBookedTime;
    int priority; 
    std::string userRole; 

public:
    MeetingRoom(int id, const std::string& name, int capacity);
    
    int getId() const;
    const std::string& getRoomName() const;
    int getCapacity() const;
    bool isOccupied() const;
    void setOccupied(bool status);

    std::time_t getLastBookedTime() const;
    void setLastBookedTime(std::time_t time);

    int getPriority() const;
    void setPriority(int p);

    const std::string& getUserRole() const;
    void setUserRole(const std::string& role);
};
