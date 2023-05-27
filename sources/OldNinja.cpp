#include "OldNinja.hpp"

using namespace std;
namespace ariel {


    OldNinja::OldNinja(string name, Point location) : Ninja(std::move(name), location) {
        //old ninja has speed 8 and hp 150
        this->setSpeed(8);
        this->setHitPoints(150);
    }

}
