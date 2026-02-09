#include "r2ui.h"

R2UI_API bool r2ui_checkbox(R2UI *ui, const char *label, bool *checked) {
	if (!ui || !ui->can || !label || !checked) {
		return false;
	}
	int x = ui->layout_x;
	int y = ui->layout_y;
	ui->widget_y = y;
	char *buf = r_str_newf ("%s[%c] %s%s",ui->theme.checkbox_color ? ui->theme.checkbox_color : Color_RESET, *checked ? 'x' : ' ', label, Color_RESET);
	if (buf) {
		r_cons_canvas_gotoxy (ui->can, x, y);
		r_cons_canvas_write (ui->can, buf);
		int len = strlen (label) + 4;
		free (buf);
		ui->layout_y++;
		if (ui->click_y == y && ui->click_x >= x && ui->click_x < x + len) {
			*checked = !*checked;
			return true;
		}
		return false;
	}
	ui->layout_y++;
	return false;
}
