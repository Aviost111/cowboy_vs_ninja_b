#include "Cowboy.hpp"
#include <stdexcept>
using namespace std;
namespace ariel{

//    Cowboy::Cowboy() {
//
//    }

    Cowboy::Cowboy(std::string name, Point location) : Character(name, location) {
        this->bulletCount=6;
        this->setHitPoints(110);
    }

//    Cowboy::~Cowboy() {
//
//    }

    void Cowboy::shoot(Character *enemy) {
        if(!enemy->isAlive()){
            throw runtime_error("The enemy is already dead");
        }
        if(!this->isAlive()){
            throw runtime_error("You are dead");
        }
        if(this==enemy){
            throw runtime_error("No self harm");
        }
        if(this->hasboolets()){
            enemy->hit(10);
            this->bulletCount--;
        }
    }

    bool Cowboy::hasboolets() {
        return (this->bulletCount>0);
    }

    void Cowboy::reload() {
        if(!this->isAlive()){
            throw runtime_error("Dead cowboy cannot reload");
        }
        this->bulletCount=6;
    }

    int Cowboy::getAmmo() const {
        return this->bulletCount;
    }

    std::string Cowboy::print() const {
        if(this->isAlive()) {
            return "C "+this->getName() + ": hp-" + to_string(this->getHitPoints()) + ", location-" +
                   this->getLocation().print();
        }
        return "C ("+this->getName()+")"+": location-" +
               this->getLocation().print();
    }
}