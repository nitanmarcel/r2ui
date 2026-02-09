#include "r2ui.h"

R2UI_API void r2ui_progress_bar(R2UI *ui, float fraction) {
	if (!ui || !ui->can) {
		return;
	}
	if (fraction < 0.0f) fraction = 0.0f;
	if (fraction > 1.0f) fraction = 1.0f;
	int x = ui->layout_x;
	int y = ui->layout_y;
	int bar_w = ui->tw - 2 - x;
	if (bar_w < 4) {
		bar_w = 4;
	}
	int filled = (int)(fraction * (bar_w - 2));
	char *buf = malloc (bar_w + 1);
	if (buf) {
		buf[0] = '[';
		int i;
		for (i = 0; i < bar_w - 2; i++) {
			buf[i + 1] = (i < filled) ? '#' : ' ';
		}
		buf[bar_w - 1] = ']';
		buf[bar_w] = '\0';
		char *colored = r_str_newf ("%s%s%s", ui->theme.progress_bar_color ? ui->theme.progress_bar_color : Color_RESET, buf, Color_RESET);
		free (buf);
		if (colored) {
			r_cons_canvas_gotoxy (ui->can, x, y);
			r_cons_canvas_write (ui->can, colored);
			free (colored);
		}
	}
	ui->layout_y++;
}
