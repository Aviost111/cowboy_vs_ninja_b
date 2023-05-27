#include "Character.hpp"
#include <stdexcept>

using namespace std;
namespace ariel {

    Character::Character(const string &name, Point location)
            : location(location), name(name), hitPoints(10) {
        this->location = location;
        this->hitPoints = 10;
        this->name = name;
        this->inTeam = false;

    }

    bool Character::isAlive() const {
        return (this->hitPoints > 0);
    }

    double Character::distance(Character *character) const {
        return this->location.distance(character->location);
    }

    void Character::hit(int damage) {
        if (damage < 0) {
            throw invalid_argument("Damage cant be negative");
        }
        //if hp hits zero stop
        if (this->hitPoints < damage) {
            hitPoints = 0;
        } else {
            hitPoints -= damage;
        }

    }

    std::string Character::getName() const {
        return this->name;
    }

    Point Character::getLocation() const {
        return this->location;
    }

    string Character::print() const {
        //if the character is alive print name , hp and location
        if (this->isAlive()) {
            return this->getName() + ": hp-" + to_string(this->getHitPoints()) + ", location-" +
                   this->getLocation().print();
        }
        //else just print name and location
        return "(" + this->getName() + ")" + ": location-" +
               this->getLocation().print();
    }

    int Character::getHitPoints() const {
        return this->hitPoints;
    }

    void Character::setLocation(const Point &location) {
        Character::location = location;
    }

    void Character::setHitPoints(int hitPoints) {
        Character::hitPoints = hitPoints;
    }

    void Character::setName(const string &name) {
        Character::name = name;
    }

    bool Character::isInTeam() const {
        return inTeam;
    }

    void Character::setInTeam() {
        this->inTeam = true;
    }
}