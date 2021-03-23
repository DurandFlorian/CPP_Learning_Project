#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
public:
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);

    void move(int64_t dt) override;

    int aircrafts_on_airline(const std::string& line);

    int get_required_fuel() const;

    void print_crashed_aircrafts() const;

private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int crashed_aircrafts = 0;
};
