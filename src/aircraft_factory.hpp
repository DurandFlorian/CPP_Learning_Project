#pragma once

#include "aircraft_manager.hpp"
#include "airport_type.hpp"
#include "airport.hpp"
#include <unordered_set>
#include <vector>

class AircraftFactory
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftManager& _aircraft_manager;
    Airport* _airport;
    std::vector<AircraftType*> aircraft_types;
    std::unordered_set<std::string_view> aircraft_numbers; 

public:
    AircraftFactory(AircraftManager&,Airport*,const MediaPath& path);
    void create_aircraft(const AircraftType&);
    void create_random_aircraft();
    std::vector<AircraftType*> loadTypes(const MediaPath&);
};
