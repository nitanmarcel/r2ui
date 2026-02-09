#include "r2ui.h"

R2UI_API bool r2ui_radio_button(R2UI *ui, const char *label, int *value, int option) {
	if (!ui || !ui->can || !label || !value) {
		return false;
	}
	int x = ui->layout_x;
	int y = ui->layout_y;
	ui->widget_y = y;
	char *buf = r_str_newf ("%s(%c) %s%s", ui->theme.radio_button_color ? ui->theme.radio_button_color : Color_RESET, *value == option ? '*' : ' ', label, Color_RESET);
	if (buf) {
		r_cons_canvas_gotoxy (ui->can, x, y);
		r_cons_canvas_write (ui->can, buf);
		int len = strlen (label) + 4;
		free (buf);
		ui->layout_y++;
		if (ui->click_y == y && ui->click_x >= x && ui->click_x < x + len) {
			*value = option;
			return true;
		}
		return false;
	}
	ui->layout_y++;
	return false;
}
