
#include<bits/stdc++.h>

struct coordinate {
    double x;
    double y;
    double z;
};

struct Room {
    int capacity;
    coordinate location;
};

// Function to calculate the median location of participants
coordinate calculateMedianLocation(const std::vector<coordinate>& participantLocations) {
    coordinate median = {0.0, 0.0, 0.0};

    for (const auto& location : participantLocations) {
        median.x += location.x;
        median.y += location.y;
        median.z += location.z;
    }

    median.x /= participantLocations.size();
    median.y /= participantLocations.size();
    median.z /= participantLocations.size();

    return median;
}

// Custom comparator for sorting rooms based on capacity and proximity to median location
bool roomComparator(const Room& room1, const Room& room2, const coordinate& medianLocation) {
    // Sort by capacity in ascending order
    if (room1.capacity < 0.75*(room2.capacity))
        return true;
    if (0.75*(room1.capacity) > room2.capacity)
        return false;

    // If capacities are similar, sort by proximity to median location
    double distance1 = pow(room1.location.x - medianLocation.x, 2) +
                       pow(room1.location.y - medianLocation.y, 2) +
                       pow(room1.location.z - medianLocation.z, 2);

    double distance2 = pow(room2.location.x - medianLocation.x, 2) +
                       pow(room2.location.y - medianLocation.y, 2) +
                       pow(room2.location.z - medianLocation.z, 2);

    return distance1 < distance2;
}

// Function to perform the room selection process
void selectRooms(std::vector<Room>& rooms, const std::vector<coordinate>& participantLocations) {
    // Calculate the median location of participants
    coordinate medianLocation = calculateMedianLocation(participantLocations);

    // Sort rooms using the custom comparator
    std::sort(rooms.begin(), rooms.end(), [&medianLocation](const Room& room1, const Room& room2) {
        return roomComparator(room1, room2, medianLocation);
    });

    // Display the selected rooms
    std::cout << "Selected Rooms:" << std::endl;
    for (const auto& room : rooms) {
        std::cout << "Capacity: " << room.capacity << ", Distance to Median: "
                  << sqrt(pow(room.location.x - medianLocation.x, 2) +
                          pow(room.location.y - medianLocation.y, 2) +
                          pow(room.location.z - medianLocation.z, 2))
                  << std::endl;
    }
}

