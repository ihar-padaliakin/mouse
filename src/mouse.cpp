#include <iostream>
#include <X11/Xlib.h>
#include <unistd.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "display.h"

using namespace std;

int main() {
    XManager manager;
    for (;;) {
        if (!manager.waitForStart()) {
            return 0;
        }
        manager.grab();
        Telemetry *telemtery = manager.getTelemetry();
        for (auto *point : *telemtery->getTelemetry()) {
            cout << point->x << " | " << point->y << endl;
        }
        delete telemtery;
        manager.ungrab();
    }
    return 0;
}
