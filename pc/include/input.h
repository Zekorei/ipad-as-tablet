#include<windows.h>

void initScreenMetrics();

static void normalizetoAbsolute(float x, float y, LONG &outX, LONG&outY);

void moveMouse(float x, float y);

void mouseDown();
void mouseUp();