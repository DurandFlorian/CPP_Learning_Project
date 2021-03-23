
#pragma once

#include "geometry.hpp"

#include <stdexcept>
#include <string_view>

class AircraftCrash : public std::runtime_error
{
public:
    AircraftCrash(std::string_view flight_number, const Point3D& pos, const Point3D& speed,
                  std::string_view reason) :
        std::runtime_error { build_error_msg(flight_number, pos, speed, reason) }
    {}

private:
    static std::string build_error_msg(std::string_view flight_number, const Point3D& pos,
                                       const Point3D& speed, std::string_view reason)
    {
        std::string str;
        str += flight_number;
        str += " at position " + pos.print_coordinates() + " and speed " + speed.print_coordinates() +
               " crashed into the ground ";
        str += reason;
        return str;
    }
};