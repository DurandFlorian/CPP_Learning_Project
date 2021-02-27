#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"
#include "geometry.hpp"

#include <cassert>

class Terminal : public GL::DynamicObject
{
private:
    unsigned int service_progress    = SERVICE_CYCLES;
    const Aircraft* current_aircraft = nullptr;
    const Point3D pos;

    Terminal(const Terminal&) = delete;
    Terminal& operator=(const Terminal&) = delete;

public:
    //terminal position
    Terminal(const Point3D& pos_) : pos { pos_ } {}

    //if terminal is linked with aircraft
    bool in_use() const { return current_aircraft != nullptr; }

    //if terminal as to ended service
    bool is_servicing() const { return service_progress < SERVICE_CYCLES; }
    //assign new aircraft to terminal
    void assign_craft(const Aircraft& aircraft) { current_aircraft = &aircraft; }
    //start aircraft service
    void start_service(const Aircraft& aircraft)
    {
        assert(aircraft.distance_to(pos) < DISTANCE_THRESHOLD);
        std::cout << "now servicing " << aircraft.get_flight_num() << "...\n";
        service_progress = 0;
    }

    //end service aircraft
    void finish_service()
    {
        if (!is_servicing())
        {
            std::cout << "done servicing " << current_aircraft->get_flight_num() << '\n';
            current_aircraft = nullptr;
        }
    }

    //progress service
    void move(int64_t dt) override
    {
        dt +=0;
        if (in_use() && is_servicing())
        {
            ++service_progress;
        }
    }
};