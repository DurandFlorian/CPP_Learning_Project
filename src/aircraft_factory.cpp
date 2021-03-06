#include "aircraft_factory.hpp"

#include <fstream>
#include <iostream>

AircraftFactory::AircraftFactory(AircraftManager& aircraft_manager_, Airport& airport_, const MediaPath& path,
                                 TexturePool& texture_pool) :
    aircraft_manager { aircraft_manager_ },
    airport { airport_ },
    aircraft_types { load_types(path, texture_pool) }
{}
void AircraftFactory::create_aircraft(const AircraftType& type)
{
    std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    while (aircraft_numbers.find(flight_number) != aircraft_numbers.end())
    {
        flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    }
    aircraft_numbers.emplace(flight_number);
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();
    aircraft_manager.add_aircraft(
        std::make_unique<Aircraft>(type, flight_number, start, direction, airport.get_tower()));
}

void AircraftFactory::create_random_aircraft()
{
    create_aircraft(*(aircraft_types[rand() % aircraft_types.size()]));
}

std::vector<std::unique_ptr<const AircraftType>> AircraftFactory::load_types(const MediaPath& path,
                                                                             TexturePool& texture_pool)
{
    std::vector<std::unique_ptr<const AircraftType>> types;
    std::string line;
    std::ifstream file { path.get_full_path() };
    std::array<std::string, 6> parameters;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            uint8_t pos      = 0;
            uint8_t next_pos = 0;
            for (uint8_t i = 0; i < 6; i++)
            {
                next_pos      = line.find(" ", pos);
                parameters[i] = line.substr(pos, next_pos - pos);
                pos           = next_pos + 1;
            }
            types.emplace_back(std::make_unique<AircraftType>(
                std::stof(parameters[0]), std::stof(parameters[1]), std::stof(parameters[2]),
                std::stoi(parameters[3]), std::stoi(parameters[4]),
                texture_pool.get_texture(MediaPath { parameters[5] }, NUM_AIRCRAFT_TILES)));
        }
    }
    return types;
}

void AircraftFactory::print_aircrafts_on_airline(int x)
{
    assert(x < airlines_size);
    std::cout << airlines[x] << " : " << aircraft_manager.aircrafts_on_airline(airlines[x]) << std::endl;
}