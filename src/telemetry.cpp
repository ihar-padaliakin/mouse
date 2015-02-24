/*
 * telemetry.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: ihar-padaliakin
 */

#include "telemetry.h"

void Telemetry::pushPoint(int x, int y) {
    Point *point = new Point();
    point->x = x;
    point->y = y;
    telemetry.push_back(point);
}

std::list<Point*> *Telemetry::getTelemetry() {
    return &telemetry;
}

Telemetry::~Telemetry() {
    for (auto *point : telemetry) {
        delete point;
    }
}
