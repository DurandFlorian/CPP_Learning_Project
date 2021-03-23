#pragma once

#include "aircraft_manager.hpp"
#include "airport.hpp"
#include "airport_type.hpp"
#include "texture_pool.hpp"

#include <memory>
#include <unordered_set>
#include <vector>

class AircraftFactory
{
private:
    static const int airlines_size                   = 8;
    const std::string airlines[airlines_size] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftManager& _aircraft_manager;
    Airport* _airport;
    std::vector<std::unique_ptr<AircraftType>> aircraft_types;
    std::unordered_set<std::string_view> aircraft_numbers;

public:
    AircraftFactory(AircraftManager&, Airport*, const MediaPath& path, TexturePool& texture_pool);
    void create_aircraft(const AircraftType&);
    void create_random_aircraft();
    std::vector<std::unique_ptr<AircraftType>> loadTypes(const MediaPath&, TexturePool&);
    void print_aircrafts_on_airline(int x);
};
