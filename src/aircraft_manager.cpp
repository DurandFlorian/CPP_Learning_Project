#include "aircraft_manager.hpp"

#include "aircraft_crash.hpp"

#include <algorithm>

void AircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    assert(aircraft);
    aircrafts.emplace_back(std::move(aircraft));
}

void AircraftManager::move(const float dt)
{
    assert(dt > 0.);
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](const auto& a1, const auto& a2) { return a1.get() < a2.get(); });
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(),
                                   [dt, this](const auto& aircraft)
                                   {
                                       try
                                       {
                                           aircraft.get()->move(dt);
                                       } catch (const AircraftCrash& err)
                                       {
                                           std::cout << err.what() << std::endl;
                                           crashed_aircrafts++;
                                           return true;
                                       }
                                       return aircraft.get()->is_dead();
                                   }),
                    aircrafts.end());
}

int AircraftManager::aircrafts_on_airline(const std::string_view line)
{
    assert(!line.empty());
    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [line](const std::unique_ptr<Aircraft>& aircraft)
                         { return aircraft.get()->get_flight_num().substr(0, 2) == line; });
}

int AircraftManager::get_required_fuel() const
{
    return std::transform_reduce(
        aircrafts.begin(), aircrafts.end(), 0, [](int i1, int i2) { return i1 + i2; },
        [](const auto& aircraft) { return aircraft.get()->get_required_fuel(); });
}

void AircraftManager::print_crashed_aircrafts() const
{
    std::cout << crashed_aircrafts << std::endl;
}