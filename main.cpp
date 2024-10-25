#include "FloorPlanManager.h"
#include "Authentication.h"
#include <iostream>
#include <string>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

void showMenu() {
    std::cout << "\n" << GREEN
              << "--- Admin Floor Plan Management ---\n"
              << RESET;
    std::cout << "1. Upload a new floor plan\n";
    std::cout << "2. Modify floor plan\n";
    std::cout << "3. Display all floor plans\n";
    std::cout << "4. Resolve conflicts\n";
    std::cout << "5. Book a meeting room\n";
    std::cout << "6. Recommend a meeting room\n";
    std::cout << "7. Exit\n";
    std::cout << "Select an option: ";
}

void showWelcomeMessage() {
    std::cout << BLUE
              << "╔══════════════════════════════════════════════════════════╗\n"
              << "║                                                          ║\n"
              << "║      Welcome to the Floor Plan Management System         ║\n"
              << "║                                                          ║\n"
              << "╚══════════════════════════════════════════════════════════╝\n"
              << RESET;
}

int main() {
    showWelcomeMessage();

    Authentication auth;
    auth.registerUser("admin", "password123");

    
    std::string username, password;
    std::cout << YELLOW << "Enter username: " << RESET;
    std::cin >> username;
    std::cout << YELLOW << "Enter password: " << RESET;
    std::cin >> password;

    if (!auth.login(username, password)) {
        std::cout << RED << "Authentication failed. Exiting.\n" << RESET;
        return 1;
    }

    FloorPlanManager floorManager;
    int option = 0;

    while (option != 7) {
        showMenu();
        std::cin >> option;

        switch (option) {
            case 1: {
                std::cin.ignore();
                int floorNumber;
                std::cout << YELLOW << "Enter the floor number: " << RESET;
                std::cin >> floorNumber;

                int numRooms;
                std::cout << YELLOW << "Enter the number of meeting rooms on this floor: " << RESET;
                std::cin >> numRooms;

                std::vector<MeetingRoom> rooms;
                for (int i = 0; i < numRooms; ++i) {
                    std::cin.ignore();
                    std::string roomName;
                    int capacity;
                    std::cout << YELLOW << "Enter details for room " << (i + 1) << ":\n";
                    std::cout << "Room name: " << RESET;
                    std::getline(std::cin, roomName);
                    std::cout << YELLOW << "Room capacity: " << RESET;
                    std::cin >> capacity;

                    rooms.emplace_back(i + 1, roomName, capacity);
                }

                floorManager.uploadPlan(floorNumber, rooms);
                break;
            }
            case 2: {
                int floorNumber;
                std::cout << YELLOW << "Enter the floor number to modify: " << RESET;
                std::cin >> floorNumber;
                std::cin.ignore();

                int numRooms;
                std::cout << YELLOW << "Enter the new number of meeting rooms: " << RESET;
                std::cin >> numRooms;

                std::vector<MeetingRoom> rooms;
                for (int i = 0; i < numRooms; ++i) {
                    std::cin.ignore();
                    std::string roomName;
                    int capacity;
                    std::cout << YELLOW << "Enter details for room " << (i + 1) << ":\n";
                    std::cout << "Room name: " << RESET;
                    std::getline(std::cin, roomName);
                    std::cout << YELLOW << "Room capacity: " << RESET;
                    std::cin >> capacity;

                    rooms.emplace_back(i + 1, roomName, capacity);
                }

                floorManager.modifyPlan(floorNumber, rooms);
                break;
            }
            case 3: {
                floorManager.displayPlans();
                break;
            }
            case 4: {
                floorManager.resolveConflicts();
                break;
            }
            case 5: {
                int participants;
                std::cout << YELLOW << "Enter the number of participants: " << RESET;
                std::cin >> participants;
                floorManager.bookRoom(participants);
                break;
            }
            case 6: {
                int participants;
                std::cout << YELLOW << "Enter the number of participants: " << RESET;
                std::cin >> participants;
                auto recommended = floorManager.recommendRoom(participants);
                auto floorNumber = recommended.first;
                auto recommendedRoom = recommended.second;

                if (floorNumber != -1) {
                    std::cout << GREEN << "Recommended Room: " << recommendedRoom->getRoomName()
                              << " on Floor " << floorNumber << ", Capacity: " 
                              << recommendedRoom->getCapacity() << RESET << std::endl;
                } else {
                    std::cout << RED << "No available room found for " << participants << " participants." << RESET << std::endl;
                }
                break;
            }
            case 7:
                std::cout << GREEN << "Exiting the program." << RESET << std::endl;
                break;
            default:
                std::cout << RED << "Invalid option. Please try again." << RESET << std::endl;
        }
    }

    return 0;
}
