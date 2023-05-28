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
    OldNinja ONinja1("Hanzo 1", Point(3, 5));
    OldNinja ONinja2("Hanzo 2", Point(1, 7));
    OldNinja ONinja3("Hanzo 3", Point(2, 7));
    YoungNinja YNinja1("mickey 1", Point(4, 4));
    YoungNinja YNinja2("mickey 2", Point(7, 4));
    YoungNinja YNinja3("mickey 3", Point(4, 4));
    TrainedNinja TNinja1("ron 1", Point(6, 2));
    TrainedNinja TNinja2("ron 2", Point(15, 2));
    TrainedNinja TNinja3("ron 3", Point(6, 99));


    // Create teams
    Team team1(&cowboy1);
    team1.addCharacter(&ONinja1);
    team1.addCharacter(&YNinja1);
    team1.addCharacter(&TNinja1);


    Team team2(&ONinja2);
    team2.addCharacter(&cowboy2);
    team1.addCharacter(&YNinja2);
    team1.addCharacter(&TNinja2);

    // Create a smart team
    SmartTeam smartTeam(&YNinja3);
    smartTeam.addCharacter(&ONinja3);
    smartTeam.addCharacter(&TNinja3);
    smartTeam.addCharacter(&cowboy3);

    cout<<YNinja1<<endl;
    YNinja2

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
    while(team1.stillAlive() > 0 && team2.stillAlive() > 0){
        team1.attack(&team2);
        if(!team2.stillAlive()){
            team2.attack(&team1);
        }
        team1.print();
        team2.print();
    }

//    cout << "Smart Team attacks Team 2:" << endl;
//    smartTeam.attack(&team2);
//    cout << endl;

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
