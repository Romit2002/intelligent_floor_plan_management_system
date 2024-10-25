#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <iostream>
#include <string>
#include <unordered_map>

class Authentication {
public:
    void registerUser(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);

private:
    std::unordered_map<std::string, std::string> userCredentials;
};

#endif
