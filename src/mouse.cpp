#include <iostream>
#include <X11/Xlib.h>
#include <unistd.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include "display.h"
#include "telemetry.h"

int main() {
    Config config;
    XManager manager;
    TelemetryService service;
    for (;;) {
        if (!manager.waitForStart()) {
            return 0;
        }
        manager.grab();
        Telemetry *telemtery = manager.getTelemetry();
//        for (auto *point : *telemtery->getTelemetry()) {
//            cout << point->x << " | " << point->y << endl;
//        }
        VectorisedTelemetry* vects = service.vectorize(telemtery);
        if (vects != nullptr) {
            service.findAndExecute(vects, &config);
        }
        std::cout << std::endl << std::endl;
        delete vects;
        delete telemtery;
        manager.ungrab();
    }
    return 0;
}
