#ifndef COWBOY_VS_NINJA_A_NINJA_HPP
#define COWBOY_VS_NINJA_A_NINJA_HPP

#include "Character.hpp"

namespace ariel {
    class Ninja : public Character {
    private:
        int speed;
    public:
//        Ninja();
        Ninja(std::string name, Point location);

        void move(Character *enemy);
        void slash(Character *enemy);
        std::string print() const override;

        int getSpeed() const;
        void setSpeed(int speed);
    };
}


#endif //COWBOY_VS_NINJA_A_NINJA_HPP
