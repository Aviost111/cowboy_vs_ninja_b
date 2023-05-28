#include <iostream>
#include "sources/Team.hpp"
#include "sources/Character.hpp"
#include "sources/Cowboy.hpp"
#include "sources/Ninja.hpp"
#include "sources/SmartTeam.hpp"
#include "sources/Point.hpp"
#include "sources/Team2.hpp"

using namespace std;
using namespace ariel;

int main() {
    // Create characters
    Point a(0,0),b(2,2),c(4,4);
    cout << "Creating characters..." << endl;
    cout << "Point c: " << c.print() << endl;

    Cowboy *cowboy1 = new Cowboy("John", a);
    Cowboy *cowboy2 = new Cowboy("Tom", b);
    Cowboy *cowboy3 = new Cowboy("Mike", Point(5, 5));
    OldNinja *ONinja1 = new OldNinja("Hanzo 1", Point(3, 5));
    OldNinja *ONinja2 = new OldNinja("Hanzo 2", Point(1, 7));
    OldNinja *ONinja3 = new OldNinja("Hanzo 3", Point(2, 7));
    YoungNinja *YNinja1 = new YoungNinja("Mickey 1", Point::moveTowards(b, c, b.distance(c)));
    YoungNinja *YNinja2 = new YoungNinja("Mickey 2", Point(7, 4));
    YoungNinja *YNinja3 = new YoungNinja("Mickey 3", c);
    TrainedNinja *TNinja1 = new TrainedNinja("Ron 1", Point(6, 2));
    TrainedNinja *TNinja2 = new TrainedNinja("Ron 2", Point(15, 2));
    TrainedNinja *TNinja3 = new TrainedNinja("Ron 3", Point(6, 99));

    // Create teams
    Team *team1 = new Team(cowboy1);
    team1->add(ONinja1);
    team1->add(YNinja1);
    team1->add(TNinja1);

    Team2 *team2 = new Team2(ONinja2);
    team2->add(cowboy2);
    team2->add(YNinja2);
    team2->add(TNinja2);

    // Create a smart team
    SmartTeam *smartTeam = new SmartTeam(YNinja3);
    smartTeam->add(ONinja3);
    smartTeam->add(TNinja3);
    smartTeam->add(cowboy3);

    cout << "Printing initial character information..." << endl;
    cout << YNinja1->print() << endl;

    cout << "Moving YNinja1 towards YNinja2..." << endl;
    YNinja1->move(YNinja2);
    cout << YNinja1->print() << endl;

    cout << "YNinja1 slashing YNinja2..." << endl;
    YNinja1->slash(YNinja2);
    cout << YNinja2->print() << endl;

    cout << "Cowboy1 shooting YNinja2..." << endl;
    cowboy1->shoot(YNinja2);
    cout << YNinja2->print() << endl;

    while (YNinja2->isAlive()) {
        if (!cowboy1->hasboolets()) {
            cowboy1->reload();
        }
        cowboy1->shoot(YNinja2);
    }

    cout << "Restarting teams..." << endl;
    team1->restart();
    team2->restart();
    smartTeam->restart();

    // Print initial team information
    cout << "Printing initial team information..." << endl;
    cout << "Team 1:" << endl;
    team1->print();
    cout << endl;

    cout << "Team 2:" << endl;
    team2->print();
    cout << endl;

    cout << "Smart Team:" << endl;
    smartTeam->print();
    cout << endl;

    // Perform attack
    cout << "Performing attacks..." << endl;
    while (team1->stillAlive() > 0 && team2->stillAlive() > 0) {
        team1->attack(team2);
        if (team2->stillAlive()) {
            team2->attack(team1);
        }
        cout << "Team 1:" << endl;
        team1->print();
        cout << "Team 2:" << endl;
        team2->print();
    }

    // Print updated team information
    cout << "Printing updated team information..." << endl;
    cout << "Team 1:" << endl;
    team1->print();
    cout << endl;

    cout << "Team 2:" << endl;
    team2->print();
    cout << endl;

    team2->restart();

    cout << "Performing attacks between Smart Team and Team 2..." << endl;
    while (smartTeam->stillAlive() > 0 && team2->stillAlive() > 0) {
        smartTeam->attack(team2);
        if (team2->stillAlive()) {
            team2->attack(smartTeam);
        }
        cout << "Smart Team:" << endl;
        smartTeam->print();
        cout << "Team 2:" << endl;
        team2->print();
    }

    cout << "Printing final team information..." << endl;
    cout << "Smart Team:" << endl;
    smartTeam->print();
    cout << endl;

    cout << "Team 2:" << endl;
    team2->print();
    cout << endl;

//    // Clean up memory
//    delete cowboy1;
//    delete cowboy2;
//    delete cowboy3;
//    delete ONinja1;
//    delete ONinja2;
//    delete ONinja3;
//    delete YNinja1;
//    delete YNinja2;
//    delete YNinja3;
//    delete TNinja1;
//    delete TNinja2;
//    delete TNinja3;
    delete team1;
    delete team2;
    delete smartTeam;

    return 0;
}

