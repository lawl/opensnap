#define LEFTCLICK 256
#define _NET_WM_STATE_ADD 1

typedef struct {
	int x;
	int y;
	int state;
} mousestate;


void getMousePosition(Display *dsp, XEvent *event, mousestate *cords);
void sendMouseUp(Display *dsp, Window *w);
int getScreenSize(Display *dsp,int &width, int &height);
void getFocusedWindow(Display *dsp,Window *w);
