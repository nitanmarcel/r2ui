#include "r2ui.h"

R2UI_API void r2ui_spacing(R2UI *ui, int n) {
	if (ui) {
		ui->layout_y += n;
	}
}

R2UI_API void r2ui_indent(R2UI *ui, int n) {
	if (ui) {
		ui->layout_x += n;
	}
}

R2UI_API void r2ui_unindent(R2UI *ui, int n) {
	if (ui) {
		ui->layout_x -= n;
		if (ui->layout_x < 0) {
			ui->layout_x = 0;
		}
	}
}

R2UI_API void r2ui_set_cursor(R2UI *ui, int x, int y) {
	if (ui) {
		if (x >= 0) ui->layout_x = x;
		if (y >= 0) ui->layout_y = y;
	}
}

R2UI_API void r2ui_set_y_bottom(R2UI *ui, int offset) {
	if (ui) {
		ui->layout_y = ui->th - offset - 1;
	}
}

R2UI_API void r2ui_same_line(R2UI *ui) {
	if (ui) {
		ui->layout_y--;
		ui->layout_x += ui->widget_w + 1;
	}
}
