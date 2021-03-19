#pragma once

#include "aircraft_manager.hpp"
#include "aircraft_factory.hpp"
#include "texture_pool.hpp"
#include <memory>

class Airport;
struct AircraftType;

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;
    AircraftManager _aircraft_manager;
    std::unique_ptr<AircraftFactory> _aircraft_factory;
    TexturePool texture_pool;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    void create_keystrokes();
    void display_help() const;

    void init_airport();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch(const MediaPath& path);
};
