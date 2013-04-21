#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>
#include <cstdlib>
#include <string.h>
#include <X11/extensions/Xrandr.h>
#include "xdo_functions.h"
#include "opensnap.h"
#include "help.h"
#include "version.h"

int main(int argc, char **argv)
{
    Display *dsp = XOpenDisplay( NULL );
    if( !dsp ){ return 1; }


    int screenWidth, screenHeight;
    getScreenSize(dsp,screenWidth,screenHeight);

    Window parentWin;
    /*getFocusedWindow(dsp,&win);
    findParentWindow(dsp,&win,&parentWin);*///i don't think we need this? not sure why i added this.

    int action=0;
    int verbose=0;
    int isdrag=0;
    int isinitialclick=1;
    int offset=10;
    int numberOfScreens = getNumberOfScreens(dsp);
    mousestate mousepos;
    XEvent event;
    Window activeWindow;
    char launch[MY_MAXPATH];
    char configbase[MY_MAXPATH];
    strcpy(configbase,"~/.config/opensnap/");

    struct option longopts[] = {
        {"config",  1, NULL, 'c'},
        {"offset",  1, NULL, 'o'},
        {"screens", 1, NULL, 's'},
        {"daemon",  0, NULL, 'd'},
        {"info",    0, NULL, 'i'},
        {"verbose", 0, NULL, 'v'},
        {"help",    0, NULL, 'h'},
        {"version", 0, NULL, 'V'},
        {0, 0, 0, 0}};

    int opt=0;
    while((opt = getopt_long(argc,argv,"c:o:ds:ivVh",longopts,NULL)) != -1){
        switch(opt){
            case 'c':
                strncpy(configbase,optarg,MY_MAXPATH);
                configbase[MY_MAXPATH-1]='\0';
                break;
            case 'd':
                if(daemon(0,0) == -1){
                    perror("daemon");
                    exit(EXIT_FAILURE);
                }
                break;
            case 's':
                numberOfScreens=atoi(optarg);
                break;
            case 'i':
                dumpInfo(dsp);
                exit(EXIT_SUCCESS);
                break;
            case 'v':
                verbose=1;
                break;
            case 'V':
                printf("opensnap version %s\n", versionstring);
                exit(EXIT_SUCCESS);
            case 'o':
                offset=atoi(optarg);
                break;
            case 'h':
            case '?':
                printHelp();
                exit(EXIT_FAILURE);
                break;
        }
    }

    while(1){
        getMousePosition(dsp, &event, &mousepos);
        if(verbose)
            printf("Mouse Coordinates: %d %d %d\n", mousepos.x, mousepos.y, mousepos.state );
        if((LEFTCLICK & mousepos.state)==LEFTCLICK){
            if(mousepos.y<=offset)
                action=HIT_TOP;
            else if(mousepos.x<=offset)
                action=HIT_LEFT;
            else if(mousepos.x>=screenWidth-offset-1)
                action=HIT_RIGHT;
            else if(mousepos.y>=screenHeight-offset-1)
                action=HIT_BOTTOM;
            else {
                if(!isdrag && isinitialclick) {
                    if(isTitlebarHit(dsp, &mousepos)){
                        isdrag=1;
                    }
                }
                action=0;
            }
            isinitialclick=false;
        }
        if(verbose)printf("action is: %d, isdrag is: %d\n",action,isdrag);
        if((16 & mousepos.state) == mousepos.state && isdrag){
            if(action){
                getFocusedWindow(dsp,&activeWindow);
                findParentWindow(dsp,&activeWindow,&parentWin);
                sendMouseUp(dsp,&parentWin);
                if(verbose)printf("Running script: %s",SCRIPT_NAMES[action]);
                sprintf(launch,"/bin/sh %s/%s %lu %i %i %i",configbase,SCRIPT_NAMES[action],parentWin,numberOfScreens,screenWidth,screenHeight);
                system(launch);
            }
            action=0;
        }
        if((LEFTCLICK & mousepos.state) != LEFTCLICK){
            isdrag=0;
            isinitialclick=1;
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


void getScreenSize(Display *dsp, int &width, int &height){
    int num_sizes;
    Rotation original_rotation;

    Window root = RootWindow(dsp, 0);
    XRRScreenSize *xrrs = XRRSizes(dsp, 0, &num_sizes);

    XRRScreenConfiguration *conf = XRRGetScreenInfo(dsp, root);
    SizeID original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);

    width=xrrs[original_size_id].width;
    height=xrrs[original_size_id].height;

}

void getFocusedWindow(Display *dsp,Window *w){
    int revert;
    XGetInputFocus(dsp,w,&revert);
}

void findParentWindow(Display *dsp, Window *w, Window *parent){
    xdo_window_find_client(dsp,*w,parent,XDO_FIND_PARENTS);
}

void getWindowRect(Display *dsp, Window *win, int *x, int *y, unsigned int *w, unsigned int *h){
    unsigned int bw,d;
    int junkx, junky;
    Window junkroot =  RootWindow(dsp, 0);
    XGetGeometry(dsp,*win,&junkroot,&junkx,&junky,w,h,&bw,&d);
    XTranslateCoordinates(dsp, *win, junkroot, junkx, junky, x, y, &junkroot);
}

void getNetFrameExtents(Display *dpy, Window *w, int *top) {
    long *extents;
    Atom actual_type;
    int actual_format;
    unsigned long nitems, bytes_after;
    unsigned char *data = NULL;
    int result;
     
    *top = 0;
     
    result = XGetWindowProperty(
            dpy, *w, XInternAtom(dpy, "_NET_FRAME_EXTENTS", False),
            0, 4, False, AnyPropertyType,
            &actual_type, &actual_format,
            &nitems, &bytes_after, &data);
     
    if (result == Success) {
        if ((nitems == 4) && (bytes_after == 0)) {
            extents = (long *)data;
            *top = (int) *(extents + 2);
        }
        XFree(data);
    }
}

int getNumberOfScreens(Display *dsp) {
    int activeScreens=0;
    XRRScreenResources *screen;
    XRROutputInfo *info;
    screen = XRRGetScreenResources(dsp,DefaultRootWindow(dsp));
    for(int i=0; i<screen->noutput; i++){
        info=XRRGetOutputInfo(dsp,screen,screen->outputs[i]);
        if(info->connection==RR_Connected){
            activeScreens++;
        }
        XRRFreeOutputInfo(info);
    }
    XRRFreeScreenResources(screen);
    return activeScreens;
}

void dumpInfo(Display *dsp){
    int screenWidth, screenHeight;
    getScreenSize(dsp,screenWidth,screenHeight);
    printf("Detected screen size:                    %ix%i\n", screenWidth, screenHeight);
    printf("Detected number of physical screens:     %i\n", getNumberOfScreens(dsp));
}

int isTitlebarHit(Display *dsp, mousestate *mousepos){
    int titlebarHeight, x, y, junkx, junky;
    unsigned int wi,h, junkwi, junkh;
    Window activeWindow, parentWin;
    getFocusedWindow(dsp,&activeWindow);
    findParentWindow(dsp,&activeWindow,&parentWin);
    getNetFrameExtents(dsp,&parentWin,&titlebarHeight);
    getWindowRect(dsp, &parentWin, &junkx, &junky, &wi, &h);
    getWindowRect(dsp, &activeWindow, &x, &y, &junkwi, &junkh); // we need the size of the parent win, but the x/y coordinates of the child, don't ask me why, otherwise the values are off a bit
    printf("Active window: %lu, titlebarheight: %i x: %i, y: %i, w: %i, h: %i jx: %i, jy: %i, jw: %i, jh: %i\n",parentWin,titlebarHeight,x,y,wi,h,junkx,junky,junkwi,junkh);
    if(y==junky){
        y-=titlebarHeight; //Qt hack
    }
    if(mousepos->x>=x && mousepos->x <= (x+(int)wi) &&
            mousepos->y >= (y-titlebarHeight) && mousepos->y <= y){
        return 1;
    }
    return 0;
}
