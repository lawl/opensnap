#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <time.h>
#include <cstdlib>
#include <string.h>
#include <X11/extensions/Xrandr.h>
#include <X11/Xatom.h>
#include "xdo_functions.h"
#include "opensnap.h"



int main(int argc, char **argv)
{
	Display *dsp = XOpenDisplay( NULL );
	if( !dsp ){ return 1; }
	
	
	int screenWidth, screenHeight;
	getScreenSize(dsp,screenWidth,screenHeight);
	
	Window win;
	getFocusedWindow(dsp,&win);
	

	int screenNumber = DefaultScreen(dsp);
	int takeaction=0;
	mousestate mousepos;
	XEvent event;
	Window activeWindow;
	time_t now;
	char launch[1024];
	
	while(1){
		getMousePosition(dsp, &event, &mousepos);
		//printf("Mouse Coordinates: %d %d %d\n", mousepos.x, mousepos.y, mousepos.state );
		if(mousepos.y==0 && mousepos.state == LEFTCLICK){
			takeaction=1;
		}
		if(takeaction && mousepos.state==0){
				time(&now);
				getFocusedWindow(dsp,&activeWindow);
				sendMouseUp(dsp,&activeWindow);
				//moveWindowPos(dsp, &activeWindow, 200,500);
				//maximizeWindow(dsp,&activeWindow);
				//SetWindowState(dsp,activeWindow,1);
				sprintf(launch,"wmctrl -i -r %u -b add,maximized_vert,maximized_horz",activeWindow);
				system(launch);
				printf("Maximizing!\n");
			}
		if(mousepos.state==0 || mousepos.y!=0){
			takeaction=0;
		}
		usleep(10000);
	}
	XCloseDisplay(dsp);
		
	return 0;
}

void sendMouseUp(Display *dsp, Window *w){
	XEvent event;
	memset(&event, 0x00, sizeof(event));
	event.type = ButtonRelease;
	event.xbutton.button = 1;
	event.xbutton.state = 0x100;
	event.xbutton.same_screen = True;
	XSendEvent(dsp, *w, True, 0xfff, &event);
	XFlush(dsp);
	
}

void moveWindowPos(Display *dsp, Window *w, int x, int y){
	XWindowChanges xwinc;
		xwinc.x=x;
		xwinc.y=y;
	XConfigureWindow(dsp,*w,CWX+CWY,&xwinc);
}

void getMousePosition(Display *dsp, XEvent *event, mousestate *cords){
	XQueryPointer(dsp, RootWindow(dsp, DefaultScreen(dsp)),
		&event->xbutton.root, &event->xbutton.window,
		&event->xbutton.x_root, &event->xbutton.y_root,
		&event->xbutton.x, &event->xbutton.y,
		&event->xbutton.state);
	cords->x=event->xbutton.x;
	cords->y=event->xbutton.y;
	cords->state=event->xbutton.state;
}


int getScreenSize(Display *dsp, int &width, int &height){
	int num_sizes;
	Rotation original_rotation;

	Window root = RootWindow(dsp, 0);
	XRRScreenSize *xrrs = XRRSizes(dsp, 0, &num_sizes);

	XRRScreenConfiguration *conf = XRRGetScreenInfo(dsp, root);
	short original_rate          = XRRConfigCurrentRate(conf);
	SizeID original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);

	width=xrrs[original_size_id].width;
	height=xrrs[original_size_id].height;

}

void getFocusedWindow(Display *dsp,Window *w){
	Window twin;
	int revert;
	XGetInputFocus(dsp,&twin,&revert);
	xdo_window_find_client(dsp,twin,w,XDO_FIND_PARENTS);
}



