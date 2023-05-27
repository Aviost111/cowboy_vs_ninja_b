#include "YoungNinja.hpp"

using namespace std;
namespace ariel {


    YoungNinja::YoungNinja(string name, Point location) : Ninja(std::move(name), location) {
        //young ninja has hp 100 and speed 14
        this->setHitPoints(100);
        this->setSpeed(14);
    }

}