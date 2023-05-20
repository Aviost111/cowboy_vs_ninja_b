#ifndef COWBOY_VS_NINJA_B_SMARTTEAM_HPP
#define COWBOY_VS_NINJA_B_SMARTTEAM_HPP
#include "Team.hpp"
#include <vector>

namespace ariel {
    class SmartTeam : public Team {
    public:
        SmartTeam(Character* leader);

        void attack(Team* enemyTeam) override;

        void print() override;

        std::vector<Ninja*> closestNinjaOrder(Character* enemy) const;

        int numOfCowboys() const;

//        Character* closestToNinjas(Team* enemyTeam) ;
    };
}

#endif //COWBOY_VS_NINJA_B_SMARTTEAM_HPP
