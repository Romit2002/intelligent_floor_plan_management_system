#include "Authentication.h"

void Authentication::registerUser(const std::string& username, const std::string& password) {
    userCredentials[username] = password;
    std::cout << "User " << username << " registered successfully." << std::endl;
}

bool Authentication::login(const std::string& username, const std::string& password) {
    if (userCredentials.find(username) != userCredentials.end() && userCredentials[username] == password) {
        std::cout << "Login successful!" << std::endl;
        return true;
    } else {
        std::cout << "Login failed. Invalid username or password." << std::endl;
        return false;
    }
}
