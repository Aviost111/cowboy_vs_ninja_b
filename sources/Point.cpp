#include <iostream>
#include "Point.hpp"
#include <cmath>

using namespace std;
using namespace ariel;

Point::Point(double pointX, double pointY) : pointX(pointX), pointY(pointY) {
}

Point::Point() : pointY(0), pointX(0) {

}

Point Point::moveTowards(Point src, Point dst, double distance) {
    if (distance < 0) {
        throw invalid_argument("No such thing as negative distance");
    }
    double dx = dst.pointX - src.pointX;
    double dy = dst.pointY - src.pointY;

    // Calculate the distance between the source and destination points
    double currentDistance = std::sqrt(dx * dx + dy * dy);

    // If the current distance is already less than or equal to the desired distance, return the destination point
    if (currentDistance <= distance) {
        return dst;
    }

    // Calculate the ratio to scale the differences in X and Y coordinates
    double ratio = distance / currentDistance;

    // Calculate the new point coordinates by scaling the differences and adding them to the source point
    double newX = src.pointX + (dx * ratio);
    double newY = src.pointY + (dy * ratio);
    // Create a new Point object with the calculated coordinates and return it
    return {newX,newY};
}

string Point::print() {
    return "(" + to_string(this->pointX) + "," + to_string(this->pointY) + ")";
}

double Point::getY() const {
    return this->pointY;
}

double Point::getX() const {
    return this->pointX;
}

double Point::distance(Point point) const {
    double dx = point.getX() - pointX;
    double dy = point.getY() - pointY;
    double dist = sqrt(dx * dx + dy * dy);
    return dist;
}

bool operator==(const Point &pointA, const Point &pointB) {
    if ((pointA.getX() == pointB.getX()) && (pointA.getY() == pointB.getY())) {
        return true;
    }
    return false;
}

