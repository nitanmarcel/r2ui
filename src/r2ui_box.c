#include "r2ui.h"

R2UI_API void r2ui_box_begin(R2UI *ui) {
	if (!ui || !ui->can) {
		return;
	}
	ui->box_x = ui->layout_x;
	ui->box_y = ui->layout_y;
	ui->layout_x++;
	ui->layout_y++;
}

R2UI_API void r2ui_box_end(R2UI *ui) {
	if (!ui || !ui->can) {
		return;
	}
	int w = ui->tw - ui->box_x - 1;
	int h = ui->layout_y - ui->box_y + 1;
	if (w > 0 && h > 2) {
		r_cons_canvas_box (ui->can, ui->box_x, ui->box_y, w, h, ui->theme.box_color);
	}
	ui->layout_x = ui->box_x;
	ui->layout_y = ui->box_y + h;
}
