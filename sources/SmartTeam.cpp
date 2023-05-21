#include "SmartTeam.hpp"
#include <cmath>
#include <iostream>

using namespace ariel;
using namespace std;

SmartTeam::SmartTeam(Character *leader) : Team(leader) {

}

void SmartTeam::attack(Team *enemyTeam) {
    bool cStart = false;
    if (enemyTeam == nullptr) {
        throw invalid_argument("You can't attack nothing fool");
    }
    if (!this->stillAlive() || !enemyTeam->stillAlive()) {
        throw runtime_error("One of the teams are dead");
//            return;
    }
    if (this->leaderDead()) {
        this->setLeader(findClosest(this->getLeader()));
    }
    Character *sacrifice = enemyTeam->findClosest(this->getLeader());
    Cowboy *cowboy;
    if ((numOfCowboys() * 10) >= sacrifice->getHitPoints()) {
        cStart= true;
        for (Character *character: this->getArr()) {
            if (character->isAlive()) {
                if (dynamic_cast<Cowboy *>(character) != nullptr) {
                    cowboy = dynamic_cast<Cowboy *>(character);
                    if (cowboy->hasboolets()) {
                        cowboy->shoot(sacrifice);
                    } else {
                        cowboy->reload();
                    }
                }
                if (!sacrifice->isAlive()) {
                    if (enemyTeam->stillAlive() == 0) {
                        return;
                    }
                    sacrifice = enemyTeam->findClosest(this->getLeader());
                }
            }
        }
    }
    vector<Ninja *> ninjas = closestNinjaOrder(sacrifice);
    for (Ninja *ninja: ninjas) {
        if (ninja->isAlive()) {
            if (ninja->distance(sacrifice) > 1) {
                ninja->move(sacrifice);
                if (ninja == this->getLeader()) {
                    sacrifice = enemyTeam->findClosest(this->getLeader());
                }
            } else {
                ninja->slash(sacrifice);
            }
            if (!sacrifice->isAlive()) {
                if (enemyTeam->stillAlive() == 0) {
                    return;
                }
                sacrifice = enemyTeam->findClosest(this->getLeader());
            }
        }
    }
    if(!cStart){
        for (Character *character: this->getArr()) {
            if (character->isAlive()) {
                if (dynamic_cast<Cowboy *>(character) != nullptr) {
                    cowboy = dynamic_cast<Cowboy *>(character);
                    if (cowboy->hasboolets()) {
                        cowboy->shoot(sacrifice);
                    } else {
                        cowboy->reload();
                    }
                }
                if (!sacrifice->isAlive()) {
                    if (enemyTeam->stillAlive() == 0) {
                        return;
                    }
                    sacrifice = enemyTeam->findClosest(this->getLeader());
                }
            }
        }
    }
    if(enemyTeam->leaderDead()){
        enemyTeam->setLeader(enemyTeam->findClosest(enemyTeam->getLeader()));
    }

}

void SmartTeam::print() {
    for (Character *character: this->getArr()) {
        cout<<character->print()<<endl;
    }
}

std::vector<Ninja *> SmartTeam::closestNinjaOrder(Character *enemy) const {
    Ninja *ninja;
    vector<Ninja *> ninjas;
    vector<Ninja *> ninjasEnd;
    for (Character *character: this->getArr()) {
        if ((dynamic_cast<Ninja *>(character) != nullptr) && (character->isAlive())) {
            ninja = dynamic_cast<Ninja *>(character);
            if (ninja->distance(enemy) < 1) {
                ninjas.push_back(ninja);
            } else {
                ninjasEnd.push_back(ninja);
            }
        }
    }
    for (Ninja *newNinja: ninjasEnd) {
        ninjas.push_back(newNinja);
    }
    return ninjas;
}

int SmartTeam::numOfCowboys() const {
    int count = 0;
    Cowboy *cowboy;
    for (Character *character: this->getArr()) {
        if (dynamic_cast<Cowboy *>(character) != nullptr) {
            cowboy = dynamic_cast<Cowboy *>(character);
            if ((cowboy->isAlive()) && (cowboy->hasboolets())) {
                count++;
            }
        }
    }
    return count;
}

//Character *SmartTeam::closestToNinjas(Team *enemyTeam) {
//    int max = 0,count;
//    Character* closest = nullptr;
//    Ninja* ninja;
//    for (Character* Echaracter:enemyTeam->getArr()) {
//        count = 0;
//        if (!Echaracter->isAlive()){
//            continue;
//        }
//        for (Character *character: this->getArr()) {
//            if (dynamic_cast<Ninja *>(character) != nullptr) {
//                ninja = dynamic_cast<Ninja *>(character);
//                if(ninja->distance(Echaracter)<=ninja->getSpeed()){
//                    count++;
//                }
//            }
//        }
//        if(max<count){
//            max = count;
//            closest = Echaracter;
//        }
//    }
//    return closest;
//}
