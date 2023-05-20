#include "Team.hpp"
#include <iostream>


using namespace std;
namespace ariel {


    Team::Team(Character *leader) : leader(leader) {
        if(this->leader->isInTeam()){
            throw runtime_error("The character is already in a team!");
        }
        this->leader->setInTeam();
        this->leader = leader;
        this->team.push_back(leader);
    }

    Team::~Team() {
        for (Character *character: this->team) {
                delete character;
        }
    }

    bool Team::leaderDead() const{
        return (this->leader->getHitPoints()==0);
    }

    void Team::add(Character *character) {
        if(character->isInTeam()){
            throw runtime_error("The character is already in a team!");
        }
        if (team.size() >= maxSize) {
            throw std::runtime_error("Team is full");
        } else {
            team.push_back(character);
            character->setInTeam();
            this->curSize++;
        }
    }


    void Team::attack(Team *enemyTeam) {
        if(enemyTeam== nullptr){
            throw invalid_argument("You can't attack nothing fool");
        }
        if(!this->stillAlive()||!enemyTeam->stillAlive()){
            throw runtime_error("One of the teams are dead");
//            return;
        }
        if(this->leaderDead()){
            this->leader=findClosest(this->leader);
        }
        Character *sacrifice=enemyTeam->findClosest(this->leader);
        Ninja* ninja;
        Cowboy* cowboy;
        for (Character *character:team) {
            if(character->isAlive()) {
                if (dynamic_cast<Cowboy *>(character) != nullptr) {
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
                    sacrifice=enemyTeam->findClosest(this->leader);
                }
            }
        }
        for (Character *character:team) {
            if(character->isAlive()) {
                if (dynamic_cast<Ninja *>(character) != nullptr) {
                    ninja = dynamic_cast<Ninja *>(character);
                    if(ninja->distance(sacrifice)>1) {
                        ninja->move(sacrifice);
                        if(ninja== this->leader){
                            sacrifice=enemyTeam->findClosest(this->leader);
                        }
                    }else {
                        ninja->slash(sacrifice);
                    }
                }
                if(!sacrifice->isAlive()){
                    if(enemyTeam->stillAlive()==0){
                        return;
                    }
                    sacrifice=enemyTeam->findClosest(this->leader);
                }
            }
        }
        if(enemyTeam->leaderDead()){
            enemyTeam->setLeader(enemyTeam->findClosest(enemyTeam->getLeader()));
        }
    }

    int Team::stillAlive() const {
        int count = 0;
        for (Character *character: team) {
            if(character->isAlive()){
                count++;
            }
        }
        return count;
    }

    void Team::print() {
        Cowboy *cowboy;
        Ninja *ninja;
        for (Character *character:team) {
            if (dynamic_cast<Cowboy *>(character) != nullptr) {
                cowboy = dynamic_cast<Cowboy *>(character);
                cout<<cowboy->print()<<endl;
            }
        }
        for (Character *character:team) {
            if (dynamic_cast<Ninja*>(character) != nullptr) {
                ninja = dynamic_cast<Ninja *>(character);
                cout<<ninja->print()<<endl;
            }
        }
    }

    Character *Team::getLeader() {
        return this->leader;
    }

    void Team::setLeader(Character *newLeader) {
        this->leader=newLeader;
    }

    vector<Character *> Team::getArr() const{
        return this->team;
    }

    int Team::getCurSize() const {
        return curSize;
    }

    Character *Team::findClosest(Character *myLeader) {
        double minDis=0;
        bool first = true;
        Character *tmpLeader= myLeader;
        for (Character* character:team) {
            if(character->isAlive()){
                if(first){
                    minDis=myLeader->distance(character);
                    tmpLeader=character;
                    first= false;
                }
                if(myLeader->distance(character)<minDis){
                    minDis=myLeader->distance(character);
                    tmpLeader=character;
                }

            }
        }
        return tmpLeader;
    }

}