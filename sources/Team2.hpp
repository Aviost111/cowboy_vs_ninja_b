#ifndef COWBOY_VS_NINJA_B_TEAM2_HPP
#define COWBOY_VS_NINJA_B_TEAM2_HPP
#include "Team.hpp"
#include <cstring>
#include "YoungNinja.hpp"
#include "OldNinja.hpp"
#include "TrainedNinja.hpp"
#include "Cowboy.hpp"
#include "Point.hpp"

namespace ariel {
    class Team2 : public Team {
    public:
        Team2(Character *leader);

        void attack(Team *enemyTeam) override;

        void print() override;
    };
}

#endif //COWBOY_VS_NINJA_B_TEAM2_HPP
