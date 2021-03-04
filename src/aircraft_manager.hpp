#pragma once

#include "aircraft.hpp"
#include "GL/dynamic_object.hpp"

#include <memory>
#include <unordered_set>

class AircraftManager : public GL::DynamicObject
{
public:
    void add_aircraft(std::unique_ptr<Aircraft> aircraft) { aircrafts.emplace(std::move(aircraft)); }

    void move(int64_t dt) override
    {
        for (auto& aircraft : aircrafts)
        {
            aircraft.get()->move(dt);
            if (aircraft.get()->is_dead())
            {
                aircrafts.erase(aircraft);
            }
        }
    }

private:
    std::unordered_set<std::unique_ptr<Aircraft>> aircrafts;
};
