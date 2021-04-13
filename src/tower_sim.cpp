#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <memory>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help" || std::string { argv[1] } == "-h") }
{

    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");
    GL::move_queue.emplace(&aircraft_manager);
    create_keystrokes();
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c',
                           [this]()
                           {
                               assert(aircraft_factory);
                               aircraft_factory.get()->create_random_aircraft();
                           });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('m', []() { GL::up_frame_rate(); });
    GL::keystrokes.emplace('l', []() { GL::down_frame_rate(); });
    GL::keystrokes.emplace('a', [this]() { aircraft_manager.print_crashed_aircrafts(); });
    GL::keystrokes.emplace('p', []() { GL::pause(); });
    for (int x = 0; x < 8; x++)
    {
        GL::keystrokes.emplace('0' + x,
                               [this, x]() { aircraft_factory.get()->print_aircrafts_on_airline(x); });
    }
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, value] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport = std::make_unique<Airport>(one_lane_airport, Point3D { 0, 0, 0 },
                                        texture_pool.get_texture(one_lane_airport_sprite_path, 1),
                                        aircraft_manager);

    GL::Displayable::display_queue.emplace_back(airport.get());
    GL::move_queue.emplace(airport.get());
}

void TowerSimulation::launch(const MediaPath& path)
{

    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    assert(airport);
    aircraft_factory =
        std::make_unique<AircraftFactory>(aircraft_manager, *airport.get(), path, texture_pool);

    GL::loop();
}
