#include "Ninja.hpp"
#include <stdexcept>

using namespace std;
namespace ariel {

    Ninja::Ninja(string name, Point location) : Character(name, location) {
        //initialize speed so it's not garbage
        this->speed = 10;
    }


    void Ninja::move(Character *enemy) {
        //set location using the result of your location move towards enemys location at your speed
        this->setLocation(this->getLocation().moveTowards(this->getLocation(), enemy->getLocation(), this->speed));
    }

    void Ninja::slash(Character *enemy) {
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
        //if you're close enough hit the enemy fo 40
        if (this->distance(enemy) < 1) {
            enemy->hit(40);
        }
    }

    int Ninja::getSpeed() const {
        return this->speed;
    }

    void Ninja::setSpeed(int speed) {
        this->speed = speed;
    }

    string Ninja::print() const {
        //if the ninja is alive print N, name , hp and location
        if (this->isAlive()) {
            return "N " + this->getName() + ": hp-" + to_string(this->getHitPoints()) + ", location-" +
                   this->getLocation().print();
        }
        //else print N, name and location
        return "N (" + this->getName() + ")" + ": location-" +
               this->getLocation().print();
    }
}
