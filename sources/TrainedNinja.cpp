#include "TrainedNinja.hpp"

using namespace std;
namespace ariel {


    TrainedNinja::TrainedNinja(string name, Point location) : Ninja(std::move(name), location) {
        //trained ninja has speed 12 and hp 120
        this->setSpeed(12);
        this->setHitPoints(120);
    }

}