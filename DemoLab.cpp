#include <iostream>
#include "Team.hpp"
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "SmartTeam.hpp"
#include "Point.hpp"

using namespace std;
using namespace ariel;

int main() {
    // Create characters
    Cowboy cowboy1("John", Point(0, 0));
    Cowboy cowboy2("Tom", Point(2, 2));
    Cowboy cowboy3("Mike", Point(5, 5));
    Cowboy cowboy4("Mikey", Point(3, 7));
    Ninja ninja1("Ryu", Point(1, 1));
    OldNinja ninja2("Hanzo", Point(4, 4));
    Ninja ninja3("Hanzo2", Point(6, 2));
    Ninja ninja3("Hanzo2", Point(6, 2));

    // Create teams
    Team team1(&cowboy1);
    team1.addCharacter(&cowboy2);
    team1.addCharacter(&ninja1);

    Team team2(&ninja2);
    team2.addCharacter(&cowboy3);

    // Create a smart team
    SmartTeam smartTeam(&ninja3);
    smartTeam.addCharacter(&ninja2);
    smartTeam.addCharacter(&cowboy4);

    // Print initial team information
    cout << "Team 1:" << endl;
    team1.print();
    cout << endl;

    cout << "Team 2:" << endl;
    team2.print();
    cout << endl;

    cout << "Smart Team:" << endl;
    smartTeam.print();
    cout << endl;

    // Perform attack
    cout << "Team 1 attacks Team 2:" << endl;
    team1.attack(&team2);
    cout << endl;

    cout << "Smart Team attacks Team 2:" << endl;
    smartTeam.attack(&team2);
    cout << endl;

    // Print updated team information
    cout << "Team 1:" << endl;
    team1.print();
    cout << endl;

    cout << "Team 2:" << endl;
    team2.print();
    cout << endl;

    cout << "Smart Team:" << endl;
    smartTeam.print();
    cout << endl;

    return 0;
}
