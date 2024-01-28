#include <bits/stdc++.h>

struct Room {
    int capacity;
    int requirement;
};

// Function to perform binary search and find rooms that meet the requirements and have capacity greater than maxCapacity
std::vector<Room> findRooms(const std::vector<Room>& rooms, int requirement, int maxCapacity) {
    std::vector<Room> result;

    // Binary search to find the first room with capacity greater than maxCapacity
    auto it = std::lower_bound(rooms.begin(), rooms.end(), maxCapacity, [](const Room& room, int maxCap) {
        return room.capacity <= maxCap;
    });

    // Iterate from the found position and check if each room meets the requirements
    for (; it != rooms.end(); ++it) 
    {
        if (it->requirement == requirement && it->capacity > maxCapacity) 
        {
            result.push_back(*it);
        } 
    }

    return result;
}

