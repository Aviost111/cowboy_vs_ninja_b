#include "YoungNinja.hpp"

using namespace std;
namespace ariel{

//    YoungNinja::YoungNinja() {
//
//    }

    YoungNinja::YoungNinja(string name, Point location) : Ninja(std::move(name), location) {
        this->setHitPoints(100);
        this->setSpeed(14);
    }

//    YoungNinja::~YoungNinja() {
//
//    }
}