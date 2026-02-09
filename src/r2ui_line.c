#include "r2ui.h"

R2UI_API void r2ui_refline_begin(R2UI *ui, int cols) {
	if (!ui) {
		return;
	}
	ui->line_base_x = ui->layout_x;
	ui->line_cols = cols;
	ui->line_next_col = 0;
	ui->layout_x += cols + 3;
}

static void draw_horiz(R2UI *ui, int x_start, int x_end, int y, const char *arrow) {
	bool use_utf8 = ui->cons->use_utf8;
	const char *hline = use_utf8 ? RUNECODESTR_LINE_HORIZ : "-";
	for (int x = x_start; x < x_end; x++) {
		if (r_cons_canvas_gotoxy (ui->can, x, y)) {
			r_cons_canvas_write (ui->can, hline);
		}
	}
	if (arrow && r_cons_canvas_gotoxy (ui->can, x_end, y)) {
		r_cons_canvas_write (ui->can, arrow);
	}
}

R2UI_API void r2ui_refline(R2UI *ui, int y1, int y2) {
	if (!ui || !ui->can || y1 == y2) {
		return;
	}
	int col = ui->line_base_x + ui->line_next_col;
	int right = ui->layout_x - 2;
	ui->line_next_col++;
	if (ui->line_next_col >= ui->line_cols) {
		ui->line_next_col = 0;
	}
	ui->can->attr = ui->theme.refline_color ? ui->theme.refline_color : Color_RESET;
	bool use_utf8 = ui->cons->use_utf8;
	int top = y1 < y2 ? y1 : y2;
	int bot = y1 < y2 ? y2 : y1;
	const char *vline = use_utf8 ? RUNECODESTR_LINE_VERT : "|";
	const char *corner_top = use_utf8
		? (ui->cons->use_utf8_curvy ? RUNECODESTR_CURVE_CORNER_TL : RUNECODESTR_CORNER_TL)
		: ".";
	const char *corner_bot = use_utf8
		? (ui->cons->use_utf8_curvy ? RUNECODESTR_CURVE_CORNER_BL : RUNECODESTR_CORNER_BL)
		: "`";
	if (r_cons_canvas_gotoxy (ui->can, col, y1)) {
		r_cons_canvas_write (ui->can, y1 < y2 ? corner_top : corner_bot);
	}
	draw_horiz (ui, col + 1, right, y1, "<");
	for (int y = top + 1; y < bot; y++) {
		if (r_cons_canvas_gotoxy (ui->can, col, y)) {
			r_cons_canvas_write (ui->can, vline);
		}
	}
	if (r_cons_canvas_gotoxy (ui->can, col, y2)) {
		r_cons_canvas_write (ui->can, y2 > y1 ? corner_bot : corner_top);
	}
	draw_horiz (ui, col + 1, right, y2, ">");
	ui->can->attr = Color_RESET;
}

R2UI_API void r2ui_refline_end(R2UI *ui) {
	if (!ui) {
		return;
	}
	ui->layout_x = ui->line_base_x;
}
