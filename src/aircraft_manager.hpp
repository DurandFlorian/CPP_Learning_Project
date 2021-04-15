#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    unsigned int crashed_aircrafts = 0;

public:
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);

    void move(const float dt) override;

    int aircrafts_on_airline(const std::string_view line);

    int get_required_fuel() const;

    void print_crashed_aircrafts() const;
};
