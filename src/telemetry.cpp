/*
 * telemetry.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: ihar-padaliakin
 */

#include "telemetry.h"
#include <cmath>
#include <iostream>

void Telemetry::pushPoint(int x, int y) {
    Point *point = new Point();
    point->x = x;
    point->y = y;
    telemetry->push_back(point);
}

std::list<Point*> *Telemetry::getTelemetry() {
    return telemetry;
}

Telemetry::Telemetry() {
    telemetry = new std::list<Point*>;
}

Telemetry::~Telemetry() {
    for (auto *point : *telemetry) {
        delete point;
    }
    delete telemetry;
}

VectorisedTelemetry::~VectorisedTelemetry() {
    for (auto *point : *telemetry) {
        delete point;
    }
    delete telemetry;
}

bool VectorisedTelemetry::compare(VectorisedTelemetry * rhsTelemetry) {
//    if (std::fabs(telemetry.front()->x - rhsTelemetry->telemetry.front()->x) < .1
//            && std::fabs(telemetry.front()->y - rhsTelemetry->telemetry.front()->y) < .1) {
//        return true;
//    }
    for (auto *point : *telemetry) {
                std::cout << point->x << " | " << point->y << std::endl;
            }
    if (std::fabs(telemetry->front()->x + 1) < EPSILON
            && std::fabs(telemetry->front()->y - 0) < EPSILON) {
        if (std::fabs(telemetry->back()->x - 0) < EPSILON
                && std::fabs(telemetry->back()->y - 1) < EPSILON)
            return true;
    }
    return false;
}

VectorisedTelemetry *TelemetryService::vectorize(Telemetry * const telemetry) {
    if (telemetry->getTelemetry()->size() < 2) {
        return nullptr;
    }
    std::list<Vector*> *vectorised = new std::list<Vector*>;
    std::list<Point*>::const_iterator iterator = telemetry->getTelemetry()->begin();
    Point *startPoint = *iterator++;
    Point *prev = *iterator++;
    Vector *vector = calculateVector(startPoint, prev);
    for (;iterator != telemetry->getTelemetry()->end(); iterator++) {
        Vector *tmpVect = calculateVector(startPoint, *iterator);
        if (std::fabs(tmpVect->x - vector->x) < EPSILON && std::fabs(tmpVect->y - vector->y) < EPSILON) {
            delete tmpVect;
        } else {
            vectorised->push_back(vector);
            delete tmpVect;
            vector = calculateVector(prev, *iterator);;
            startPoint = *iterator;
        }
        prev = *iterator;
    }
    vectorised->push_back(vector);
    return new VectorisedTelemetry(vectorised);
}

Vector* TelemetryService::calculateVector(Point *firstPoint, Point *secondPoint) {
    Vector *vector = new Vector();
    int x = secondPoint->x - firstPoint->x,
        y = secondPoint->y - firstPoint->y;
    double length = std::sqrt(x * x + y * y);
    vector->x = x / length;
    vector->y = -y / length;
    return vector;
}
