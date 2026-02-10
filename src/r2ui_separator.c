#include "r2ui.h"

R2UI_API void r2ui_separator(R2UI *ui) {
	if (!ui || !ui->can) {
		return;
	}
	ui->widget_y = ui->layout_y;
	int w = ui->tw - 2;
	r_cons_canvas_fill (ui->can, ui->layout_x, ui->layout_y, w, 1, '-');
	ui->widget_w = w;
	ui->layout_y++;
}
