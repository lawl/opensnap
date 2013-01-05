/*
gcc `pkg-config --cflags --libs x11` track-window-movements.c -o track-window-movements
 */

#include <X11/Xlib.h>
#include <stdio.h>

int main()
{
  Display *display = XOpenDisplay(NULL);

  XSelectInput(display,
	       DefaultRootWindow(display),
	       SubstructureNotifyMask);

  while (1) {
    XEvent event;

    XNextEvent(display, &event);

    if (event.type==ConfigureNotify) {
      XConfigureEvent *configure = (XConfigureEvent *)&event;

      printf("Window %07lx is at (%d,%d) %dx%d\n",
	     (long int) configure->window,
	     configure->x, configure->y,
	     configure->width, configure->height);
    }
  }

  return 0;
}