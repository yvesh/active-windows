#include "windowlinux.h"

#ifdef __linux__
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string>

extern "C" {
    // SEE xprop
    #define MAXSTR 1000
    unsigned long window;
    unsigned char *prop;
    Display *display;

    unsigned char* get_string_property(char* property_name)
    {
        Atom actual_type, filter_atom;
        int actual_format, status;
        unsigned long nitems, bytes_after;

        filter_atom = XInternAtom(display, property_name, True);
        status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
                                    &actual_type, &actual_format, &nitems, &bytes_after, &prop);
        return prop;
    }

    unsigned long get_long_property(char* property_name)
    {
        get_string_property(property_name);
        unsigned long long_property = prop[0] + (prop[1]<<8) + (prop[2]<<16) + (prop[3]<<24);
        return long_property;
    }

    Display* getDisplay() {
        char *display_name = NULL;  // could be the value of $DISPLAY
        display = XOpenDisplay(display_name);

        return display;
    }
}

void windowlinux::getActiveWindow(Napi::Object &obj) {
    Display* display = getDisplay();
    int screen = XDefaultScreen(display);
    window = RootWindow(display, screen);
    window = get_long_property("_NET_ACTIVE_WINDOW");

    std::string wm_pid = std::to_string(get_long_property("_NET_WM_PID"));
    char* wm_name = reinterpret_cast<char*>(get_string_property("_NET_WM_NAME"));
    char* wm_class = reinterpret_cast<char*>(get_string_property("WM_CLASS"));

    obj.Set("os", "linux");
    obj.Set("windowClass", wm_class);
    obj.Set("windowName", wm_name);
    obj.Set("windowDesktop", std::to_string(get_long_property("_NET_WM_DESKTOP")));
    obj.Set("windowType", std::to_string(get_long_property("_NET_WM_WINDOW_TYPE")));
    obj.Set("windowPid", wm_pid);

    XCloseDisplay(display);
}

Napi::Object windowlinux::getActiveWindowWrapped(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();

  Napi::Object obj = Napi::Object::New(env);
  windowlinux::getActiveWindow(obj);

  return obj;
}

Napi::Object windowlinux::Init(Napi::Env env, Napi::Object exports)
{
  exports.Set(
    "getActiveWindowLinux", Napi::Function::New(env, windowlinux::getActiveWindowWrapped)
  );

  return exports;
}
