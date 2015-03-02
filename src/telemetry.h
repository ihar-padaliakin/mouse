/*
 * telemetry.h
 *
 *  Created on: Feb 24, 2015
 *      Author: ihar-padaliakin
 */

#ifndef TELEMETRY_H_
#define TELEMETRY_H_

#define EPSILON .3

#include <list>
#include <string>

typedef struct {
    int x, y;
} Point;

class Telemetry {
    private:
        std::list<Point*> *telemetry;
    public:
        Telemetry();
        ~Telemetry();
        void pushPoint(int x, int y);
        std::list<Point*> *getTelemetry();
};


typedef struct {
    double x, y;
    int length;
} Vector;

class VectorisedTelemetry {
    private:
        std::list<Vector*> *telemetry;
    public:
        VectorisedTelemetry(std::list<Vector*> *telemetry) : telemetry(telemetry) {};
        ~VectorisedTelemetry();
        std::list<Vector*> *getTelemetry();
};

typedef struct {
    VectorisedTelemetry* telemetry;
    std::string action;
} Action;

class Config {
    private:
    std::list<Action*> *telemetry;
    public:
        Config();
        ~Config();
        std::list<Action*> const * getAll();
};

class TelemetryService {
    private:
        double length(Point *firstPoint, Point *secondPoint);
        Vector* calculateVector(Point *firstPoint, Point *secondPoint);
    public:
        VectorisedTelemetry* vectorize(Telemetry* telemetry);
        void findAndExecute(VectorisedTelemetry * telemetry, Config *config);
};

#endif /* TELEMETRY_H_ */
