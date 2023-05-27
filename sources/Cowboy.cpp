#include "Cowboy.hpp"
#include <stdexcept>

using namespace std;
namespace ariel {

    Cowboy::Cowboy(std::string name, Point location) : Character(name, location) {
        this->bulletCount = 6;
        this->setHitPoints(110);
    }

    void Cowboy::shoot(Character *enemy) {
        //check that you and the enemy are alive and that you arent attacking yourself
        if (!enemy->isAlive()) {
            throw runtime_error("The enemy is already dead");
        }
        if (!this->isAlive()) {
            throw runtime_error("You are dead");
        }
        if (this == enemy) {
            throw runtime_error("No self harm");
        }
        //if you have bullets shoot the enemy for ten damage
        if (this->hasboolets()) {
            enemy->hit(10);
            //use a bullet
            this->bulletCount--;
        }
    }

    bool Cowboy::hasboolets() {
        return (this->bulletCount > 0);
    }

    void Cowboy::reload() {
        //check that you are alive
        if (!this->isAlive()) {
            throw runtime_error("Dead cowboy cannot reload");
        }
        this->bulletCount = 6;
    }

    int Cowboy::getAmmo() const {
        return this->bulletCount;
    }

    std::string Cowboy::print() const {
        //if the cowboy is alive print C, name , hp and location
        if (this->isAlive()) {
            return "C " + this->getName() + ": hp-" + to_string(this->getHitPoints()) + ", location-" +
                   this->getLocation().print();
        }
        //else print C, name and location
        return "C (" + this->getName() + ")" + ": location-" +
               this->getLocation().print();
    }
}