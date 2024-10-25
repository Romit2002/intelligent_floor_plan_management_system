#include "MeetingRoom.h"

MeetingRoom::MeetingRoom(int id, const std::string& roomName, int capacity)
    : id(id), name(roomName), capacity(capacity), occupied(false), lastBookedTime(0), priority(0), userRole("Guest") {}

int MeetingRoom::getId() const {
    return id;
}

const std::string& MeetingRoom::getRoomName() const {
    return name;
}

int MeetingRoom::getCapacity() const {
    return capacity;
}

bool MeetingRoom::isOccupied() const {
    return occupied;
}

void MeetingRoom::setOccupied(bool status) {
    occupied = status;
}

std::time_t MeetingRoom::getLastBookedTime() const {
    return lastBookedTime;
}

void MeetingRoom::setLastBookedTime(std::time_t time) {
    lastBookedTime = time;
}

int MeetingRoom::getPriority() const {
    return priority;
}

void MeetingRoom::setPriority(int p) {
    priority = p;
}

const std::string& MeetingRoom::getUserRole() const {
    return userRole;
}

void MeetingRoom::setUserRole(const std::string& role) {
    userRole = role;
}
