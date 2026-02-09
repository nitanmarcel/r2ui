#include "r2ui.h"

R2UI_API bool r2ui_tab_bar_begin(R2UI *ui, int *active) {
	if (!ui || !ui->can || !active) {
		return false;
	}
	ui->tab_bar_y = ui->layout_y;
	ui->tab_header_x = ui->layout_x;
	ui->tab_active = active;
	ui->layout_y = ui->tab_bar_y + 1;
	return true;
}

R2UI_API bool r2ui_tab_item(R2UI *ui, const char *label, int index) {
	if (!ui || !ui->can || !label || !ui->tab_active) {
		return false;
	}
	int x = ui->tab_header_x;
	int y = ui->tab_bar_y;
	bool active = *ui->tab_active == index;
	char *buf = r_str_newf ("%s[ %s ]%s", active ? (ui->theme.tab_bar_color ? ui->theme.tab_bar_color : Color_INVERT) : Color_RESET, label, Color_RESET);
	if (buf) {
		r_cons_canvas_gotoxy (ui->can, x, y);
		r_cons_canvas_write (ui->can, buf);
		int len = strlen (label) + 4;
		free (buf);
		ui->tab_header_x += len;
		if (ui->click_y == y && ui->click_x >= x && ui->click_x < x + len) {
			*ui->tab_active = index;
			active = true;
		}
	}
	return active;
}

R2UI_API void r2ui_tab_bar_end(R2UI *ui) {
	if (!ui) {
		return;
	}
	ui->tab_active = NULL;
	ui->layout_x = 1;
}
