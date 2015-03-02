/*
 * telemetry.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: ihar-padaliakin
 */

#include "telemetry.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

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

std::list<Vector*> *VectorisedTelemetry::getTelemetry() {
    return telemetry;
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
        if (std::fabs(tmpVect->x - vector->x) > EPSILON || std::fabs(tmpVect->y - vector->y) > EPSILON) {
            vector->length = length(startPoint, prev);
            vectorised->push_back(vector);
            vector = calculateVector(prev, *iterator);;
            startPoint = *iterator;
        }
        delete tmpVect;
        prev = *iterator;
    }
    vector->length = length(startPoint, prev);
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

double TelemetryService::length(Point *firstPoint, Point *secondPoint) {
    int x = secondPoint->x - firstPoint->x,
        y = secondPoint->y - firstPoint->y;
    return std::sqrt(x * x + y * y);
}

void TelemetryService::findAndExecute(VectorisedTelemetry * telemetry, Config *config) {
    for (auto *point : *telemetry->getTelemetry()) {
        std::cout << point->x << " | " << point->y << " | " << point->length << std::endl;
    }
    for (auto *action : *config->getAll()) {

//        int lhsSize = telemetry->getTelemetry()->size(),
//            rhsSize = action->telemetry->getTelemetry()->size();
//        if (lhsSize < 1 || rhsSize < 1 || lhsSize != rhsSize) {
//            return ;
//        }
        std::list<Vector*>::const_iterator lhsIterator = telemetry->getTelemetry()->begin();
        std::list<Vector*>::const_iterator rhsIterator = action->telemetry->getTelemetry()->begin();
        double error = (*lhsIterator)->length / (*rhsIterator)->length;
        bool execute = true;
        for (;lhsIterator != telemetry->getTelemetry()->end() && rhsIterator != action->telemetry->getTelemetry()->end(); lhsIterator++, rhsIterator++) {
            if (std::fabs((*lhsIterator)->x - (*rhsIterator)->x) > EPSILON
                        || std::fabs((*lhsIterator)->y - (*rhsIterator)->y) > EPSILON
                        /*|| std::fabs(error - (*lhsIterator)->length / (*rhsIterator)->length) > 16*/) {
                execute = false;
                break;
            }
        }
        if (execute) {
            std::cout << action->action;
        }
    }
}

Config::Config() {
    telemetry = new std::list<Action*>;
    std::ifstream infile("config");
    std::string line;
    while (std::getline(infile, line)) {
        std::list<Vector*> *vectorised = new std::list<Vector*>;
        std::istringstream iss(line);
        double x,y, length;
        while (!iss.eof()) {
            iss >> x >> y >> length;
            Vector *vector = new Vector;
            vector->x = x;
            vector->y = y;
            vector->length = length;
            vectorised->push_back(vector);
        }
        if (std::getline(infile, line)) {
//            throw
        }
        Action *action = new Action;
        action->telemetry = new VectorisedTelemetry(vectorised);
        action->action = std::string(line);
        telemetry->push_back(action);
    }
}

Config::~Config() {
    for (auto *item : *telemetry) {
        delete item;
    }
    delete telemetry;
}

std::list<Action*> const * Config::getAll() {
    return telemetry;
}
