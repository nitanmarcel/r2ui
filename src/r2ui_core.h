#ifndef R2UI_CORE_H
#define R2UI_CORE_H

#include <r_cons.h>

typedef struct r2ui_t {
	RCons *cons;
	RConsCanvas *can;
	int tw;
	int th;
	int last_key;
	int layout_x;
	int layout_y;
	bool running;
} R2UI;

#endif
