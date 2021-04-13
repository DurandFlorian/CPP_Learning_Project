#include "tower_sim.hpp"
#include "point.hpp"
int main(int argc, char** argv)
{
    TowerSimulation simulation { argc, argv };
    simulation.launch(MediaPath { "aircraft_types.txt" });
    
    return 0;
}