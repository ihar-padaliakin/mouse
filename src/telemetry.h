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
        bool compare(VectorisedTelemetry *telemetry);
};

class TelemetryService {
    private:
        Vector* calculateVector(Point *firstPoint, Point *secondPoint);
    public:
        VectorisedTelemetry* vectorize(Telemetry* telemetry);
};
#endif /* TELEMETRY_H_ */
