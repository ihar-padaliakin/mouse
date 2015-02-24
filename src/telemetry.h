/*
 * telemetry.h
 *
 *  Created on: Feb 24, 2015
 *      Author: ihar-padaliakin
 */

#ifndef TELEMETRY_H_
#define TELEMETRY_H_

#include <list>

typedef struct {
    int x,y;
} Point;

class Telemetry {
    private:
        std::list<Point*> telemetry;
    public:
        ~Telemetry();
        void pushPoint(int x, int y);
        std::list<Point*> *getTelemetry();
};

#endif /* TELEMETRY_H_ */
