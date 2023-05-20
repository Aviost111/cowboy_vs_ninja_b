#include "OldNinja.hpp"

using namespace std;
namespace ariel{

//    OldNinja::OldNinja() {
//
//    }

    OldNinja::OldNinja(string name, Point location) : Ninja(std::move(name), location) {
        this->setSpeed(8);
        this->setHitPoints(150);
    }

//    OldNinja::~OldNinja() {
//
//    }
}
