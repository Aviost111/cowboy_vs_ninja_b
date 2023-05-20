#include "Team2.hpp"
#include <stdexcept>
#include <iostream>

using namespace ariel;
using namespace std;
Team2::Team2(Character *leader) : Team(leader) {
}

void Team2::attack(Team *enemyTeam) {
    if(enemyTeam== nullptr){
        throw invalid_argument("You can't attack nothing fool");
    }
    if(this->stillAlive()==0||enemyTeam->stillAlive()==0){
        throw runtime_error("One of the teams are dead");
//        return;
    }
    if(this->leaderDead()){
        this->setLeader(findClosest(this->getLeader()));
    }
    Character *sacrifice=enemyTeam->findClosest(this->getLeader());
    Ninja* ninja;
    Cowboy* cowboy;
    for (Character *character: this->getArr()) {
        if(character->isAlive()) {
            if (dynamic_cast<Ninja *>(character) != nullptr) {
                ninja = dynamic_cast<Ninja *>(character);
                if(ninja->distance(sacrifice)>1) {
                    ninja->move(sacrifice);
                    if(ninja== this->getLeader()){
                        sacrifice=enemyTeam->findClosest(this->getLeader());
                    }
                }else {
                    ninja->slash(sacrifice);
                }
            }else{
                cowboy = dynamic_cast<Cowboy*>(character);
                if(cowboy->hasboolets()){
                    cowboy->shoot(sacrifice);
                } else{
                    cowboy->reload();
                }
            }
            if(!sacrifice->isAlive()){
                if(enemyTeam->stillAlive()==0){
                    return;
                }
                sacrifice=enemyTeam->findClosest(this->getLeader());
            }
        }
    }
    if(enemyTeam->leaderDead()){
        enemyTeam->setLeader(enemyTeam->findClosest(enemyTeam->getLeader()));
    }
}

void Team2::print() {
    for (Character *character: this->getArr()) {
        cout<<character->print()<<endl;
    }
}
