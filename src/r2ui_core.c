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
	ui->menu_open = -1;
	r_cons_enable_mouse (cons, true);
	return ui;
}

R2UI_API void r2ui_free(R2UI *ui) {
	if (!ui) {
		return;
	}
	r_cons_enable_mouse (ui->cons, false);
	free (ui);
}

R2UI_API bool r2ui_begin(R2UI *ui) {
	if (!ui || !ui->cons || !ui->running) {
		return false;
	}

	int raw = r_cons_readchar_timeout (ui->cons, 50);
	ui->event.key = R2UI_KEY_NONE;
	ui->event.ch = 0;

	if (raw != -1) {
		if (raw == 0x1b) {
			int next = r_cons_readchar_timeout (ui->cons, 5);
			if (next == -1) {
				ui->event.key = R2UI_KEY_ESC;
			} else {
				char nb = (char)next;
				r_cons_readpush (ui->cons, &nb, 1);
				int mapped = r_cons_arrow_to_hjkl (ui->cons, raw);
				switch (mapped) {
				case 'k': ui->event.key = R2UI_KEY_UP; break;
				case 'j': ui->event.key = R2UI_KEY_DOWN; break;
				case 'h': ui->event.key = R2UI_KEY_LEFT; break;
				case 'l': ui->event.key = R2UI_KEY_RIGHT; break;
				case 27:  ui->event.key = R2UI_KEY_ESC; break;
				default:
					if (mapped >= 0xf1 && mapped <= 0xfc) {
						ui->event.key = R2UI_KEY_F1 + (mapped - 0xf1);
					} else {
						ui->event.key = mapped;
					}
				}
			}
		} else if (raw >= 32 && raw <= 126) {
			ui->event.key = raw;
			ui->event.ch = raw;
		} else {
			ui->event.key = raw;
		}
	}
	
	ui->click_x = -1;
	ui->click_y = -1;
	int cx, cy;
	if (r_cons_get_click (ui->cons, &cx, &cy)) {
		if (cx > 0) cx--;
		if (cy > 0) cy--;
		ui->click_x = cx;
		ui->click_y = cy;
	}

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

	r2ui_menu_render (ui);
	r_cons_clear00 (ui->cons);
	r_cons_canvas_print (ui->can);
	r_cons_flush (ui->cons);
	r_cons_canvas_free (ui->can);
	ui->can = NULL;
}

R2UI_API int r2ui_get_key(R2UI *ui) {
	return ui ? ui->event.key : R2UI_KEY_NONE;
}

R2UI_API int r2ui_key_char(R2UI *ui) {
	return ui ? ui->event.ch : 0;
}

R2UI_API bool r2ui_nav_up(R2UI *ui) {
	return ui && (ui->event.key == R2UI_KEY_UP || ui->event.key == R2UI_KEY_k);
}

R2UI_API bool r2ui_nav_down(R2UI *ui) {
	return ui && (ui->event.key == R2UI_KEY_DOWN || ui->event.key == R2UI_KEY_j);
}

R2UI_API bool r2ui_nav_left(R2UI *ui) {
	return ui && (ui->event.key == R2UI_KEY_LEFT || ui->event.key == R2UI_KEY_h);
}

R2UI_API bool r2ui_nav_right(R2UI *ui) {
	return ui && (ui->event.key == R2UI_KEY_RIGHT || ui->event.key == R2UI_KEY_l);
}

R2UI_API int r2ui_widget_y(R2UI *ui) {
	return ui ? ui->widget_y : 0;
}

R2UI_API void r2ui_stop(R2UI *ui) {
	if (ui) {
		ui->running = false;
	}
}
