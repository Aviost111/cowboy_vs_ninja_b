#ifndef COWBOY_VS_NINJA_A_TEAM_HPP
#define COWBOY_VS_NINJA_A_TEAM_HPP

#include <cstring>
#include "YoungNinja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "Cowboy.hpp"
#include "Point.hpp"
#include <vector>

namespace ariel {
    class Team {
    private:
        static const int maxSize=10;
        std::vector<Character*> team;
        Character* leader;
        int curSize;
    public:
        int getCurSize() const;

        Team(Character* leader);
        virtual ~Team();

        void add(Character* character);

        virtual void attack(Team* enemyTeam);

        int stillAlive() const;

        virtual void print();

        bool leaderDead() const;

        Character* findClosest(Character *myLeader);

        std::vector<Character*>getArr() const;

        void setLeader(Character* leader);

        Character* getLeader();

        Team(const Team&) = delete;
        Team& operator=(const Team&) = delete;
        Team(Team&&) = delete;
        Team& operator=(Team&&) = delete;
        std::vector<Character*> sortCowboyFirst() const;

        void restart();
    };

}


#endif //COWBOY_VS_NINJA_A_TEAM_HPP
