#include <bits/stdc++.h>
using namespace std;

/*
   ParkingSlot represents ONE physical parking slot.
*/
class ParkingSlot {
private:
    int slotNumber;
    string vehicleNumber;

public:
    ParkingSlot(int number) : slotNumber(number), vehicleNumber("") {}

    bool isEmpty() const {
        return vehicleNumber.empty();
    }

    void parkVehicle(const string& vehicle) {
        vehicleNumber = vehicle;
    }

    void removeVehicle() {
        vehicleNumber.clear();
    }

    int getSlotNumber() const {
        return slotNumber;
    }

    string getVehicleNumber() const {
        return vehicleNumber;
    }
};

/*
   ParkingLevel represents one level in multi-level parking.
*/
class ParkingLevel {
private:
    int levelNumber;
    vector<ParkingSlot> slots;
    int totalSlots;

public:
    ParkingLevel(int level, int numSlots)
        : levelNumber(level), totalSlots(numSlots) {
        for (int i = 1; i <= totalSlots; i++) {
            slots.emplace_back(i);
        }
    }

    bool isVehicleInLevel(const string& vehicle) const {
        for (const auto& slot : slots) {
            if (!slot.isEmpty() && slot.getVehicleNumber() == vehicle) {
                return true;
            }
        }
        return false;
    }

    bool parkVehicle(const string& vehicle) {
        for (auto& slot : slots) {
            if (slot.isEmpty()) {
                slot.parkVehicle(vehicle);
                cout << "Vehicle parked at Level "
                     << levelNumber << ", Slot "
                     << slot.getSlotNumber() << "\n";
                return true;
            }
        }
        return false;
    }

    bool removeVehicle(int slotNum) {
        if (slotNum < 1 || slotNum > totalSlots) {
            cout << "Invalid slot number.\n";
            return false;
        }

        if (slots[slotNum - 1].isEmpty()) {
            cout << "Slot is already empty.\n";
            return false;
        }

        slots[slotNum - 1].removeVehicle();
        cout << "Vehicle removed from Level "
             << levelNumber << ", Slot "
             << slotNum << "\n";
        return true;
    }

    int getLevelNumber() const {
        return levelNumber;
    }

    int getOccupiedCount() const {
        int count = 0;
        for (const auto& slot : slots) {
            if (!slot.isEmpty()) count++;
        }
        return count;
    }

    int getEmptyCount() const {
        return totalSlots - getOccupiedCount();
    }

    bool isFull() const {
        return getEmptyCount() == 0;
    }

    void displayLevelStatus() const {
        cout << "\n========== LEVEL " << levelNumber << " ==========\n";
        for (const auto& slot : slots) {
            if (slot.isEmpty()) {
                cout << "  Slot " << slot.getSlotNumber()
                     << " : [Empty]\n";
            } else {
                cout << "  Slot " << slot.getSlotNumber()
                     << " : [" << slot.getVehicleNumber() << "]\n";
            }
        }
        cout << "  Occupied: " << getOccupiedCount()
             << " | Empty: " << getEmptyCount()
             << " | Total: " << totalSlots << "\n";
    }
};

/*
   ParkingLot manages the entire parking system
*/
class ParkingLot {
private:
    vector<ParkingLevel> levels;
    int totalLevels;
    int slotsPerLevel;

public:
    ParkingLot(int numLevels, int slotsPerLvl)
        : totalLevels(numLevels), slotsPerLevel(slotsPerLvl) {
        for (int i = 1; i <= totalLevels; i++) {
            levels.emplace_back(i, slotsPerLevel);
        }
    }

    bool isVehicleAlreadyParked(const string& vehicle) const {
        for (const auto& level : levels) {
            if (level.isVehicleInLevel(vehicle)) {
                return true;
            }
        }
        return false;
    }

    void parkVehicle() {
        string vehicle;
        cout << "Enter vehicle number: ";
        cin >> vehicle;

        if (isVehicleAlreadyParked(vehicle)) {
            cout << "Vehicle already parked.\n";
            return;
        }

        for (auto& level : levels) {
            if (level.parkVehicle(vehicle)) {
                return;
            }
        }

        cout << "Parking lot is FULL.\n";
    }

    void leaveSlot() {
        int levelNum, slotNum;

        cout << "Enter level number (1-" << totalLevels << "): ";
        cin >> levelNum;

        cout << "Enter slot number (1-" << slotsPerLevel << "): ";
        cin >> slotNum;

        if (levelNum < 1 || levelNum > totalLevels) {
            cout << "Invalid level number.\n";
            return;
        }

        levels[levelNum - 1].removeVehicle(slotNum);
    }

    void displayStatus() const {
        cout << "\n===== PARKING LOT STATUS =====\n";
        cout << "Levels: " << totalLevels
             << " | Slots per Level: " << slotsPerLevel << "\n";

        int totalOccupied = 0;
        int totalEmpty = 0;

        for (const auto& level : levels) {
            level.displayLevelStatus();
            totalOccupied += level.getOccupiedCount();
            totalEmpty += level.getEmptyCount();
        }

        int totalSlots = totalOccupied + totalEmpty;
        cout << "\n========== SUMMARY ==========\n";
        cout << "Total Occupied: " << totalOccupied << "\n";
        cout << "Total Empty   : " << totalEmpty << "\n";
        cout << "Total Slots   : " << totalSlots << "\n";

        if (totalSlots > 0) {
            cout << "Occupancy Rate: "
                 << (totalOccupied * 100) / totalSlots << "%\n";
        }
    }

    void displayMenu() const {
        cout << "\n===== PARKING MANAGEMENT SYSTEM =====\n";
        cout << "P - Park Vehicle\n";
        cout << "L - Leave Parking Slot\n";
        cout << "S - View Parking Status\n";
        cout << "Q - Quit System\n";
        cout << "Enter command: ";
    }
};

int main() {
    int numLevels, slotsPerLevel;

    cout << "MULTI-LEVEL PARKING LOT SYSTEM\n";
    cout << "Enter number of parking levels: ";
    cin >> numLevels;

    cout << "Enter number of slots per level: ";
    cin >> slotsPerLevel;

    if (numLevels <= 0 || slotsPerLevel <= 0) {
        cout << "Invalid input.\n";
        return 0;
    }

    ParkingLot parkingLot(numLevels, slotsPerLevel);

    char command;
    while (true) {
        parkingLot.displayMenu();
        cin >> command;
        command = toupper(command);

        if (command == 'P')
            parkingLot.parkVehicle();
        else if (command == 'L')
            parkingLot.leaveSlot();
        else if (command == 'S')
            parkingLot.displayStatus();
        else if (command == 'Q') {
            cout << "Exiting system. Thank you!\n";
            break;
        }
        else
            cout << "Invalid command.\n";
    }

    return 0;
}
