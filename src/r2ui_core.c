#include "r2ui.h"

R2UI_API R2UI *r2ui_new(RCons *cons) {
	if (!cons) {
		return NULL;
	}
	R2UI *ui = R_NEW0 (R2UI);
	if (!ui) {
		return NULL;
	}
	ui->cons = cons;
	ui->running = true;
	return ui;
}

R2UI_API void r2ui_free(R2UI *ui) {
	if (!ui) {
		return;
	}
	free (ui);
}

R2UI_API bool r2ui_begin(R2UI *ui) {
	if (!ui || !ui->cons || !ui->running) {
		return false;
	}

	ui->last_key = r_cons_readchar_timeout (ui->cons, 50);

	ui->th = 0;
	ui->tw = r_cons_get_size (ui->cons, &ui->th);
	if (ui->tw < 10) {
		ui->tw = 80;
	}
	if (ui->th < 5) {
		ui->th = 24;
	}

	ui->can = r_cons_canvas_new (ui->cons, ui->tw, ui->th, 0);
	if (!ui->can) {
		ui->running = false;
		return false;
	}
	ui->can->color = ui->cons->context->color_mode;

	r_cons_canvas_fill (ui->can, 0, 0, ui->tw, ui->th, ' ');
	r_cons_canvas_box (ui->can, 0, 0, ui->tw, ui->th, ui->theme.frame_color);

	ui->layout_x = 1;
	ui->layout_y = 1;

	return ui->running;
}

R2UI_API void r2ui_end(R2UI *ui) {
	if (!ui || !ui->can) {
		return;
	}

	r_cons_clear00 (ui->cons);
	r_cons_canvas_print (ui->can);
	r_cons_flush (ui->cons);
	r_cons_canvas_free (ui->can);
	ui->can = NULL;
}

R2UI_API bool r2ui_key_pressed(R2UI *ui, int key) {
	return ui && ui->last_key == key;
}

R2UI_API void r2ui_stop(R2UI *ui) {
	if (ui) {
		ui->running = false;
	}
}
