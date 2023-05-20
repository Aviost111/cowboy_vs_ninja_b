#include "TrainedNinja.hpp"

using namespace std;
namespace ariel{

//    TrainedNinja::TrainedNinja() {
//
//    }

    TrainedNinja::TrainedNinja(string name, Point location) : Ninja(std::move(name), location)
    {
        this->setSpeed(12);
        this->setHitPoints(120);
    }

//    TrainedNinja::~TrainedNinja() {
//
//    }
}