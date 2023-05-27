#ifndef COWBOY_VS_NINJA_A_CHARACTER_HPP
#define COWBOY_VS_NINJA_A_CHARACTER_HPP

#include "Point.hpp"
#include <string>


namespace ariel {
    class Character {
    private:
        Point location;
        int hitPoints;
        std::string name;
        bool inTeam;
    public:
        bool isInTeam() const;

        void setInTeam();

        Character(const std::string &name, Point location);

        virtual ~Character() = default;

        Character(const Character &) = delete;

        Character &operator=(const Character &) = delete;

        Character(Character &&) = delete;

        Character &operator=(Character &&) = delete;

        bool isAlive() const;

        double distance(Character *character) const;

        void hit(int damage);

        int getHitPoints() const;

        std::string getName() const;

        Point getLocation() const;

        virtual std::string print() const;

        void setLocation(const Point &location);

        void setHitPoints(int hitPoints);

        void setName(const std::string &name);
    };
}

#endif //COWBOY_VS_NINJA_A_CHARACTER_HPP
