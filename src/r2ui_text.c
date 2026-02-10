#include "r2ui.h"
#include <stdarg.h>

R2UI_API void r2ui_text(R2UI *ui, const char *fmt, ...) {
	if (!ui || !ui->can || !fmt) {
		return;
	}
	ui->widget_y = ui->layout_y;
	va_list ap;
	va_start (ap, fmt);
	char *buf = r_str_newvf (fmt, ap);
	va_end (ap);
	if (buf) {
		r_cons_canvas_gotoxy (ui->can, ui->layout_x, ui->layout_y);
		r_cons_canvas_write (ui->can, buf);
		ui->widget_w = r_str_ansi_len (buf);
		free (buf);
	}
	ui->layout_y++;
}
