#define LEFTCLICK 256
#define HIT_TOP 1
#define HIT_LEFT 2
#define HIT_RIGHT 3
#define HIT_BOTTOM 4
#define MY_MAXPATH 2048


typedef struct {
	int x;
	int y;
	int state;
} mousestate;

const char *SCRIPT_NAMES[] = {
    0,
    "hit_top",
    "hit_left",
    "hit_right",
    "hit_bottom"
};


void getMousePosition(Display *dsp, XEvent *event, mousestate *cords);
void sendMouseUp(Display *dsp, Window *w);
void getScreenSize(Display *dsp,int &width, int &height);
void getFocusedWindow(Display *dsp,Window *w);
void getNetFrameExtents(Display *dpy, Window *w, int *top);
void getWindowRect(Display *dsp, Window *win, int *x, int *y, unsigned int *w, unsigned int *h);
void findParentWindow(Display *dsp, Window *w, Window *parent);
int getNumberOfScreens(Display *dsp);
int isTitlebarHit(Display *dsp, mousestate *mousepos);
void dumpInfo(Display *dsp);
