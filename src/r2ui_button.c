#include "r2ui.h"

R2UI_API bool r2ui_button(R2UI *ui, const char *label) {
	if (!ui || !ui->can || !label) {
		return false;
	}
	int x = ui->layout_x;
	int y = ui->layout_y;
	char *buf = r_str_newf ("[ %s ]", label);
	if (buf) {
		r_cons_canvas_gotoxy (ui->can, x, y);
		r_cons_canvas_write (ui->can, buf);
		int len = strlen (label) + 4;
		free (buf);
		ui->layout_y++;
		return ui->click_y == y
			&& ui->click_x >= x && ui->click_x < x + len;
	}
	ui->layout_y++;
	return false;
}
