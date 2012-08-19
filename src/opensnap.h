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


void getMousePosition(Display *dsp, XEvent *event, mousestate *cords);
void sendMouseUp(Display *dsp, Window *w);
void getScreenSize(Display *dsp,int &width, int &height);
void getFocusedWindow(Display *dsp,Window *w);
