#pragma once

#include "aircraft_factory.hpp"
#include "aircraft_manager.hpp"
#include "texture_pool.hpp"

#include <memory>

class Airport;
struct AircraftType;

class TowerSimulation
{
private:
    bool help = false;
    std::unique_ptr<Airport> airport;
    AircraftManager aircraft_manager;
    std::unique_ptr<AircraftFactory> aircraft_factory;
    TexturePool texture_pool;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_keystrokes();
    void display_help() const;

    void init_airport();

public:
    TowerSimulation(int argc, char** argv);

    void launch(const MediaPath& path);
};
