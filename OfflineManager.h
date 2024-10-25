#ifndef OFFLINEMANAGER_H
#define OFFLINEMANAGER_H

#include <iostream>
#include <string>

class OfflineManager {
public:
    void saveLocalChanges(const std::string& changes);
    void syncWithServer();

private:
    std::string localChanges;
};

#endif
