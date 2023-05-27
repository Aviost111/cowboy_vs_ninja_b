#include "Team2.hpp"
#include <stdexcept>
#include <iostream>

using namespace ariel;
using namespace std;
Team2::Team2(Character *leader) : Team(leader) {
}

void Team2::attack(Team *enemyTeam) {
    //check that you are attacking another team and that both your team and their team are alive.
    if(enemyTeam== nullptr){
        throw invalid_argument("You can't attack nothing fool");
    }
    if(this->stillAlive()==0||enemyTeam->stillAlive()==0){
        throw runtime_error("One of the teams are dead");
    }
    //if your leader is dead choose a new one
    if(this->leaderDead()){
        this->setLeader(findClosest(this->getLeader()));
    }
    //find the sacrifice
    Character *sacrifice=enemyTeam->findClosest(this->getLeader());
    Ninja* ninja;
    Cowboy* cowboy;
    //attack
    for (Character *character: this->getArr()) {
        //only attack with live characters
        if(character->isAlive()) {
            //if ninja
            if (dynamic_cast<Ninja *>(character) != nullptr) {
                ninja = dynamic_cast<Ninja *>(character);
                //if you're close enough slash otherwise move closer
                if(ninja->distance(sacrifice)>1) {
                    ninja->move(sacrifice);
                    //if you're the team leader choose new sacrifice after you move
                    if(ninja== this->getLeader()){
                        sacrifice=enemyTeam->findClosest(this->getLeader());
                    }
                }else {
                    ninja->slash(sacrifice);
                }
            }else{
                //if cowboy
                cowboy = dynamic_cast<Cowboy*>(character);
                //if you have bullets shoot otherwise reload
                if(cowboy->hasboolets()){
                    cowboy->shoot(sacrifice);
                } else{
                    cowboy->reload();
                }
            }
            //if the sacrifice died choose a new one
            if(!sacrifice->isAlive()){
                //if the team died stop attacking
                if(enemyTeam->stillAlive()==0){
                    return;
                }
                sacrifice=enemyTeam->findClosest(this->getLeader());
            }
        }
    }
}

void Team2::print() {
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
