#ifndef R2UI_CORE_H
#define R2UI_CORE_H

#include <r_cons.h>

typedef struct r2ui_theme_t {
	const char *frame_color;
	const char *button_color;
	const char *checkbox_color;
	const char *radio_button_color;
	const char *selectable_color;
	const char *progress_bar_color;
	const char *tab_bar_color;
} R2UITheme;

typedef struct r2ui_t {
	RCons *cons;
	RConsCanvas *can;
	int tw;
	int th;
	int last_key;
	int layout_x;
	int layout_y;
	int click_x;
	int click_y;
	int tab_bar_y;
	int tab_header_x;
	int *tab_active;
	bool running;
	R2UITheme theme;
} R2UI;

#endif
