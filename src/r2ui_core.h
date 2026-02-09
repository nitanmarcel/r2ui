#ifndef R2UI_CORE_H
#define R2UI_CORE_H

#include <r_cons.h>

#define R2UI_MENU_MAX_ITEMS 32

typedef struct r2ui_theme_t {
	const char *frame_color;
	const char *button_color;
	const char *checkbox_color;
	const char *radio_button_color;
	const char *selectable_color;
	const char *progress_bar_color;
	const char *tab_bar_color;
	const char *menu_bar_color;
	const char *box_color;
	const char *refline_color;
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
	int menu_open;
	int menu_bar_y;
	int menu_header_x;
	int menu_idx;
	int menu_drop_x;
	int menu_drop_y;
	int menu_drop_count;
	int menu_drop_max_w;
	const char *menu_drop_items[R2UI_MENU_MAX_ITEMS];
	bool menu_any_interact;
	int box_x;
	int box_y;
	int widget_y;
	int line_base_x;
	int line_cols;
	int line_next_col;
	bool running;
	R2UITheme theme;
} R2UI;

#endif
