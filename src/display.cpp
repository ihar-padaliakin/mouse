#include "display.h"

XManager::XManager() {
    display = XOpenDisplay(0);
    if (!display) {
        //throw std::throw_runtime_error("fail with display");
    }
    screen = DefaultScreen(display);
    rootWindow = DefaultRootWindow(display);

    XGCValues gcVal;

    gcVal.function = GXcopy;
    gcVal.plane_mask = AllPlanes;
    gcVal.foreground = WhitePixel(display, screen);
    gcVal.background = BlackPixel(display, screen);
    gcVal.line_width = 4;
    gcVal.line_style = LineSolid;
    gcVal.cap_style = CapButt;
    gcVal.join_style = JoinMiter;
    gcVal.fill_style = FillOpaqueStippled;
    gcVal.fill_rule = WindingRule;
    gcVal.graphics_exposures = False;
    gcVal.clip_x_origin = 0;
    gcVal.clip_y_origin = 0;
    gcVal.clip_mask = None;
    gcVal.subwindow_mode = IncludeInferiors;

    gc = XCreateGC(display, rootWindow, GCFunction | GCPlaneMask | GCForeground |
                                         GCBackground | GCLineWidth | GCLineStyle |
                                         GCCapStyle | GCJoinStyle | GCFillStyle |
                                         GCFillRule | GCGraphicsExposures |
                                         GCClipXOrigin | GCClipYOrigin | GCClipMask |
                                         GCSubwindowMode,
                                         &gcVal);
    XGrabPointer(display, rootWindow, 1,
            ButtonPressMask | ButtonReleaseMask | ButtonMotionMask | PointerMotionMask,
            GrabModeAsync,
            GrabModeAsync, 0, 0,
            CurrentTime);
    XGrabKeyboard(display, rootWindow, 1,
            GrabModeAsync,
            GrabModeAsync,
            CurrentTime);
}

XManager::~XManager() {
    XFreeGC(display, gc);
    ungrab();
    XUngrabPointer(display, CurrentTime);
}

void XManager::grab() {
    XGrabServer(display);
//    XGrabKeyboard(display, rootWindow, 1,
//        GrabModeAsync,
//        GrabModeAsync,
//        CurrentTime);
}

void XManager::ungrab() {
    XUngrabServer(display);
//    XUngrabKeyboard(display, CurrentTime);
}

void XManager::drawPoint(int x, int y) {
    XDrawArc(display, rootWindow, gc, x - 3, y - 3, 5, 5, 0, 360 * 64);
}

bool XManager::waitForStart() {
    XEvent event;
    for (;;) {
        XNextEvent(display, &event);
        switch (event.type) {
            case KeyPress:
                return false;
            case ButtonPressMask:
                if (event.xbutton.button == Button3) {

                    drawPoint(event.xbutton.x, event.xbutton.y);
                    return true;
                }
                break;
        }
    }
    // Should never happen
    return false;
}

Telemetry* XManager::getTelemetry() {
    Telemetry *telemetry = new Telemetry();
    XEvent event;
//    Time prev = NULL;
    while (true) {
        XNextEvent(display, &event);

        switch (event.type) {
            case ButtonRelease:
                return telemetry;

            case MotionNotify:
//                if (prev) {
//                    int count = 0;
//                    XTimeCoord *xcoords = XGetMotionEvents(display, rootWindow, prev, event.xmotion.time, &count);
//                    int i = 0;
//                    for (i = 0; i < count; i++) {
//                        Point point;
//                        point.x = xcoords[i].x;
//                        point.y = xcoords[i].y;
//                        drawPoint(point.x, point.y);
//                        // Add
//                    }
//                }
//                prev = prev ? event.xmotion.time : prev;

                telemetry->pushPoint(event.xbutton.x, event.xbutton.y);

                drawPoint(event.xbutton.x, event.xbutton.y);
                break;

            default:
                break;
        }
    }
}
