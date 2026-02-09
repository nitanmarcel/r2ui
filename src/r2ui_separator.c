#include "r2ui.h"

R2UI_API void r2ui_separator(R2UI *ui) {
	if (!ui || !ui->can) {
		return;
	}
	ui->widget_y = ui->layout_y;
	r_cons_canvas_fill (ui->can, ui->layout_x, ui->layout_y, ui->tw - 2, 1, '-');
	ui->layout_y++;
}
