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
    AircraftManager& aircraft_manager;
    Airport& airport;
    std::vector<std::unique_ptr<const AircraftType>> aircraft_types;
    std::unordered_set<std::string_view> aircraft_numbers;

    void create_aircraft(const AircraftType&);
    std::vector<std::unique_ptr<const AircraftType>> load_types(const MediaPath&, TexturePool&);

public:
    AircraftFactory(AircraftManager&, Airport&, const MediaPath& path,TexturePool& texture_pool);
    
    void create_random_aircraft();
    
    void print_aircrafts_on_airline(int x);
};
