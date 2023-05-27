#include "SmartTeam.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

SmartTeam::SmartTeam(Character *leader) : Team(leader) {

}

void SmartTeam::attack(Team *enemyTeam) {
    bool cStart = false;
    //check that you are attacking another team and that both your team and their team are alive.
    if (enemyTeam == nullptr) {
        throw invalid_argument("You can't attack nothing fool");
    }
    if (!this->stillAlive() || !enemyTeam->stillAlive()) {
        throw runtime_error("One of the teams are dead");
    }
    //if your leader is dead choose a new one
    if (this->leaderDead()) {
        this->setLeader(findClosest(this->getLeader()));
    }
    //find the sacrifice
    Character *sacrifice = enemyTeam->findClosest(this->getLeader());
    Cowboy *cowboy;
    //if you have enough ready cowboys,they start
    if ((numOfCowboys() * 10) >= sacrifice->getHitPoints()) {
        cStart= true;
        for (Character *character: this->getArr()) {
            if (character->isAlive()) {
                //if it's a live cowboy
                if (dynamic_cast<Cowboy *>(character) != nullptr) {
                    cowboy = dynamic_cast<Cowboy *>(character);
                    //if it has bullets attack else reload
                    if (cowboy->hasboolets()) {
                        cowboy->shoot(sacrifice);
                    } else {
                        cowboy->reload();
                    }
                }
                //if the sacrifice died choose a new one
                if (!sacrifice->isAlive()) {
                    //if the enemy team died stop attacking
                    if (enemyTeam->stillAlive() == 0) {
                        return;
                    }
                    sacrifice = enemyTeam->findClosest(this->getLeader());
                }
            }
        }
    }
    //sort the ninjas to start with all ninjas close enough to attack
    vector<Ninja *> ninjas = closestNinjaOrder(sacrifice);

    for (Ninja *ninja: ninjas) {
        //if the ninja is alive
        if (ninja->isAlive()) {
            //and close enough attack else move closer
            if (ninja->distance(sacrifice) > 1) {
                ninja->move(sacrifice);
                //if you're the team leader choose new sacrifice after you move
                if (ninja == this->getLeader()) {
                    sacrifice = enemyTeam->findClosest(this->getLeader());
                }
            } else {
                ninja->slash(sacrifice);
            }
            //if the sacrifice died choose a new one
            if(!sacrifice->isAlive()){
                //if the team died stop attacking
                if(enemyTeam->stillAlive()==0){
                    return;
                }
                sacrifice = enemyTeam->findClosest(this->getLeader());
            }
        }
    }
    //if we started with cowboys they need to attack
    if(!cStart){
        for (Character *character: this->getArr()) {
            //if alive
            if (character->isAlive()) {
                if (dynamic_cast<Cowboy *>(character) != nullptr) {
                    cowboy = dynamic_cast<Cowboy *>(character);
                    //if you have bullets shoot otherwise reload
                    if (cowboy->hasboolets()) {
                        cowboy->shoot(sacrifice);
                    } else {
                        cowboy->reload();
                    }
                }
                //if the sacrifice died choose a new one
                if(!sacrifice->isAlive()){
                    //if the team died stop attacking
                    if(enemyTeam->stillAlive()==0){
                        return;
                    }
                    sacrifice = enemyTeam->findClosest(this->getLeader());
                }
            }
        }
    }

}

void SmartTeam::print() {
    Cowboy *cowboy;
    Ninja *ninja;
    //print them all
    for (Character *character: this->getArr()) {
        if (dynamic_cast<Cowboy *>(character) != nullptr) {
            cowboy = dynamic_cast<Cowboy *>(character);
            cout<<cowboy->print()<<endl;
        }else{
            ninja = dynamic_cast<Ninja *>(character);
            cout<<ninja->print()<<endl;
        }
    }
}
//sort the ninjas so that the ones closest the enemy start first
std::vector<Ninja *> SmartTeam::closestNinjaOrder(Character *enemy) const {
    Ninja *ninja;
    vector<Ninja *> ninjas;
    vector<Ninja *> ninjasEnd;
    for (Character *character: this->getArr()) {
        //if ninja
        if ((dynamic_cast<Ninja *>(character) != nullptr) && (character->isAlive())) {
            ninja = dynamic_cast<Ninja *>(character);
            //if its close enough add to the vector
            if (ninja->distance(enemy) < 1) {
                ninjas.push_back(ninja);
            } else {
                //else add to separate vector so we can add to the end of the other
                ninjasEnd.push_back(ninja);
            }
        }
    }
    //add the far away ninjas to the vector
    for (Ninja *newNinja: ninjasEnd) {
        ninjas.push_back(newNinja);
    }
    return ninjas;
}
//count ready cowboys
int SmartTeam::numOfCowboys() const {
    int count = 0;
    Cowboy *cowboy;
    for (Character *character: this->getArr()) {
        //if it's a live cowboy that has bullets count him
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
