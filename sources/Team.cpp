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
        //check if the character is in the team already
        if(character->isInTeam()){
            throw runtime_error("The character is already in a team!");
        }
        //check if the team is full
        if (team.size() >= maxSize) {
            throw std::runtime_error("Team is full");
        } else {
            //if its not add the character
            team.push_back(character);
            character->setInTeam();
            this->curSize++;
        }
    }
    vector<Character*> Team::sortCowboyFirst() const {
        vector<Character*> newTeam;
        //first add cowboys
        for (Character *character:this->team) {
            if (dynamic_cast<Cowboy *>(character) != nullptr) {
                newTeam.push_back(character);
            }
        }
        //then add ninjas
        for (Character *character:this->team) {
            if (dynamic_cast<Ninja *>(character) != nullptr) {
                newTeam.push_back(character);
            }
        }
        return newTeam;
    }
    void Team::attack(Team *enemyTeam) {
        //check that you are attacking another team and that both your team and their team are alive.
        if(enemyTeam== nullptr){
            throw invalid_argument("You can't attack nothing fool");
        }
        if(!this->stillAlive()||!enemyTeam->stillAlive()){
            throw runtime_error("One of the teams are dead");
        }
        //if your leader is dead choose a new one
        if(this->leaderDead()){
            this->leader=findClosest(this->leader);
        }
        //find the sacrifice
        Character *sacrifice=enemyTeam->findClosest(this->leader);
        Ninja* ninja;
        Cowboy* cowboy;
        //sort cowboy first
        vector<Character*> sorted= this->sortCowboyFirst();
        //attack
        for (Character *character:sorted) {
            //only attack with live characters
            if(character->isAlive()) {
                //if cowboy
                if (dynamic_cast<Cowboy *>(character) != nullptr) {
                    cowboy = dynamic_cast<Cowboy*>(character);
                    //if you have bullets shoot otherwise reload
                    if(cowboy->hasboolets()){
                        cowboy->shoot(sacrifice);
                    } else{
                        cowboy->reload();
                    }
                }else{
                    //if ninja
                    ninja = dynamic_cast<Ninja *>(character);
                    //if you're close enough slash otherwise move closer
                    if(ninja->distance(sacrifice)>1) {
                        ninja->move(sacrifice);
                        //if you're the team leader choose new sacrifice after you move
                        if(ninja== this->leader){
                            sacrifice=enemyTeam->findClosest(this->leader);
                        }
                    }else {
                        ninja->slash(sacrifice);
                    }
                }
                //if the sacrifice died choose a new one
                if(!sacrifice->isAlive()){
                    //if the team died stop attacking
                    if(enemyTeam->stillAlive()==0){
                        return;
                    }
                    sacrifice=enemyTeam->findClosest(this->leader);
                }
            }
        }
    }

    int Team::stillAlive() const {
        int count = 0;
        //count how many are alive
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
        //sort by cowboys
        vector<Character*> sorted= this->sortCowboyFirst();
        //print them all
        for (Character *character:sorted) {
            if (dynamic_cast<Cowboy *>(character) != nullptr) {
                cowboy = dynamic_cast<Cowboy *>(character);
                cout<<cowboy->print()<<endl;
            }else{
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
        //make tmp leader so if you don't find a new one he won't change
        Character *tmpLeader= myLeader;
        for (Character* character:team) {
            //if the character is dead they are irrelevant
            if(character->isAlive()){
                //if it's the first new character that's alive make them the closest
                if(first){
                    minDis=myLeader->distance(character);
                    tmpLeader=character;
                    first= false;
                }
                //if the distance between the leader and this character is smaller than the closest then make
                //him the closest
                if(myLeader->distance(character)<minDis){
                    minDis=myLeader->distance(character);
                    tmpLeader=character;
                }

            }
        }
        return tmpLeader;
    }
    //restart the team to be alive
    void Team::restart() {
        Cowboy *cowboy;
        OldNinja * ON;
        TrainedNinja* TN;
        YoungNinja *YN;
        //go over the whole team and set hp and bullets to initial values
        for(Character* character: this->team){
            if (dynamic_cast<Cowboy *>(character) != nullptr) {
                cowboy=dynamic_cast<Cowboy *>(character);
                cowboy->setHitPoints(110);
                cowboy->reload();
            }
            if (dynamic_cast<OldNinja *>(character) != nullptr) {
                ON = dynamic_cast<OldNinja *>(character);
                ON->setHitPoints(150);
            }
            if (dynamic_cast<YoungNinja *>(character) != nullptr) {
                YN =dynamic_cast<YoungNinja *>(character);
                YN->setHitPoints(100)
            }
            if (dynamic_cast<TrainedNinja *>(character) != nullptr) {
                TN = dynamic_cast<TrainedNinja *>(character);
                TN->setHitPoints(120);
            }
        }
    }
}