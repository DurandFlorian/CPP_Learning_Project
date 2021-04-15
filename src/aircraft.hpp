#pragma once

#include "GL/displayable.hpp"
#include "aircraft_types.hpp"
#include "config.hpp"
#include "geometry.hpp"
#include "tower.hpp"
#include "waypoint.hpp"

#include <experimental/random>
#include <string>
#include <string_view>

class Aircraft : public GL::Displayable
{
private:
    const AircraftType& type;
    const std::string flight_number;
    Point3D pos, speed; // note: the speed should always be normalized to length 'speed'
    WaypointQueue waypoints = {};
    Tower& control;
    bool landing_gear_deployed = false; // is the landing gear deployed?
    bool is_at_terminal        = false;
    bool dead                  = false;
    int fuel                   = std::experimental::randint(150, type.max_fuel);

    // turn the aircraft to arrive at the next waypoint
    // try to facilitate reaching the waypoint after the next by facing the
    // right way to this end, we try to face the point Z on the line spanned by
    // the next two waypoints such that Z's distance to the next waypoint is
    // half our distance so: |w1 - pos| = d and [w1 - w2].normalize() = W and Z
    // = w1 + W*d/2
    void turn_to_waypoint();
    void turn(Point3D direction);

    // select the correct tile in the plane texture (series of 8 sprites facing
    // [North, NW, W, SW, S, SE, E, NE])
    unsigned int get_speed_octant() const;
    // when we arrive at a terminal, signal the tower
    void arrive_at_terminal();
    // deploy and retract landing gear depending on next waypoints
    void operate_landing_gear();
    template <bool front> void add_waypoint(const Waypoint& wp);
    bool is_on_ground() const { return pos.z() < DISTANCE_THRESHOLD; }
    void crash(const std::string_view&);
    float max_speed() const { return is_on_ground() ? type.max_ground_speed : type.max_air_speed; }

    Aircraft(const Aircraft&) = delete;
    Aircraft& operator=(const Aircraft&) = delete;

public:
    // aircraft with type, id number,actual pos,speed and control tower
    Aircraft(const AircraftType& type_, const std::string_view& flight_number_, const Point3D& pos_,
             const Point3D& speed_, Tower& control_) :
        GL::Displayable { pos_.x() + pos_.y() },
        type { type_ },
        flight_number { flight_number_ },
        pos { pos_ },
        speed { speed_ },
        control { control_ }
    {
        speed.cap_length(max_speed());
    }

    ~Aircraft() {}

    const std::string& get_flight_num() const { return flight_number; }

    float distance_to(const Point3D& p) const { return pos.distance_to(p); }

    void display() const override;

    void move(const float dt);

    bool is_dead() const;

    bool is_circling() const;

    bool has_terminal() const;

    bool is_low_on_fuel() const;

    int get_required_fuel() const;

    void refill(int& fuel_stock);

    void print_refilled_fuel(int refilled_fuel);

    friend bool operator<(const Aircraft& a1, const Aircraft& a2) { return a1.fuel < a2.fuel; }

    friend class Tower;
};
