#pragma once

#include "GL/texture.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <array>

struct AircraftType
{
    const float max_ground_speed;
    const float max_air_speed;
    const float max_accel;
    const int max_fuel;
    const int consumed_fuel;
    const GL::Texture2D& texture;

    AircraftType(const float max_ground_speed_, const float max_air_speed_, const float max_accel_,
                 const int max_fuel_, const int consumed_fuel_, const GL::Texture2D& sprite) :
        max_ground_speed { max_ground_speed_ },
        max_air_speed { max_air_speed_ },
        max_accel { max_accel_ },
        max_fuel { max_fuel_ },
        consumed_fuel { consumed_fuel_ },
        texture { sprite }
    {}
};
