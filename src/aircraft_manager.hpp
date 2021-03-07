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
        for(auto it = aircrafts.begin();it!=aircrafts.end();){
            it->get()->move(dt);
            if (it->get()->is_dead())
            {
                it = aircrafts.erase(it);
            }else{
                it++;
            }
        }
    }

private:
    std::unordered_set<std::unique_ptr<Aircraft>> aircrafts;
};
