#include "r2ui.h"

R2UI_API bool r2ui_selectable(R2UI *ui, const char *label, bool selected) {
	if (!ui || !ui->can || !label) {
		return false;
	}
	int x = ui->layout_x;
	int y = ui->layout_y;
	char *buf = r_str_newf ("%s%s%s", selected ? (ui->theme.selectable_color ? ui->theme.selectable_color : Color_INVERT) : Color_RESET, label, Color_RESET);
	if (buf) {
		r_cons_canvas_gotoxy (ui->can, x, y);
		r_cons_canvas_write (ui->can, buf);
		int len = strlen (label);
		free (buf);
		ui->layout_y++;
		return ui->click_y == y
			&& ui->click_x >= x && ui->click_x < x + len;
	}
	ui->layout_y++;
	return false;
}
