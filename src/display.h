/*
 * display.h
 *
 *  Created on: Feb 24, 2015
 *      Author: ihar-padaliakin
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <X11/Xlib.h>
#include "telemetry.h"

class XManager {
    private:
        Display *display;
        Window rootWindow;
        GC gc;
        int screen;

        void drawPoint(int x, int y);
    public:
        XManager();
        ~XManager();
        void grab();
        void ungrab();
        bool waitForStart();
        Telemetry* getTelemetry();
};



#endif /* DISPLAY_H_ */
