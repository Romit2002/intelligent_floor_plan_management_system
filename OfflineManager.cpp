#include "OfflineManager.h"

void OfflineManager::saveLocalChanges(const std::string& changes) {
    localChanges = changes;
    std::cout << "Changes saved locally due to network issues." << std::endl;
}

void OfflineManager::syncWithServer() {
    if (!localChanges.empty()) {
        std::cout << "Synchronizing with server..." << std::endl;
        // Simulate syncing process
        std::cout << "Changes synchronized: " << localChanges << std::endl;
        localChanges.clear();
    } else {
        std::cout << "No local changes to sync." << std::endl;
    }
}
