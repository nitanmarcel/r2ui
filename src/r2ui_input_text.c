#include "r2ui.h"
#include <string.h>

#define INPUT_FIELD_W 20

R2UI_API bool r2ui_input_text(R2UI *ui, const char *label, char *buf, int buf_size) {
	if (!ui || !ui->can || !label || !buf || buf_size < 2) {
		return false;
	}

	int x = ui->layout_x;
	int y = ui->layout_y;
	ui->widget_y = y;

	int label_len = strlen (label);
	int field_w = INPUT_FIELD_W;
	int field_x = x + label_len + 2;
	bool is_active = (ui->input_active == buf);
	bool changed = false;

	if (ui->click_y == y && ui->click_x >= field_x && ui->click_x < field_x + field_w + 2) {
		ui->input_active = buf;
		int click_off = ui->click_x - field_x - 1 + ui->input_scroll;
		int len = strlen (buf);
		ui->input_cursor = click_off < 0 ? 0 : (click_off > len ? len : click_off);
		is_active = true;
	}

	if (is_active) {
		int len = strlen (buf);
		int key = ui->event.key;
		int ch = ui->event.ch;

		if (key == R2UI_KEY_ENTER || key == R2UI_KEY_ESC) {
			ui->input_active = NULL;
			is_active = false;
		} else if (key == R2UI_KEY_BACKSPACE || key == R2UI_KEY_BACKSPACE2) {
			if (ui->input_cursor > 0) {
				memmove (buf + ui->input_cursor - 1, buf + ui->input_cursor, len - ui->input_cursor + 1);
				ui->input_cursor--;
				changed = true;
			}
		} else if (key == R2UI_KEY_DELETE) {
			if (ui->input_cursor < len) {
				memmove (buf + ui->input_cursor, buf + ui->input_cursor + 1, len - ui->input_cursor);
				changed = true;
			}
		} else if (key == R2UI_KEY_LEFT) {
			if (ui->input_cursor > 0) {
				ui->input_cursor--;
			}
		} else if (key == R2UI_KEY_RIGHT) {
			if (ui->input_cursor < len) {
				ui->input_cursor++;
			}
		} else if (key == R2UI_KEY_HOME || key == R2UI_KEY_CTRL_A) {
			ui->input_cursor = 0;
		} else if (key == R2UI_KEY_END || key == R2UI_KEY_CTRL_E) {
			ui->input_cursor = len;
		} else if (ch && len < buf_size - 1) {
			memmove (buf + ui->input_cursor + 1, buf + ui->input_cursor, len - ui->input_cursor + 1);
			buf[ui->input_cursor] = ch;
			ui->input_cursor++;
			changed = true;
		}
	}

	if (ui->input_cursor < ui->input_scroll) {
		ui->input_scroll = ui->input_cursor;
	}
	if (ui->input_cursor >= ui->input_scroll + field_w) {
		ui->input_scroll = ui->input_cursor - field_w + 1;
	}

	r_cons_canvas_gotoxy (ui->can, x, y);
	char *lbl = r_str_newf ("%s%s: ", ui->theme.input_text_color ? ui->theme.input_text_color : Color_RESET, label);
	if (lbl) {
		r_cons_canvas_write (ui->can, lbl);
		free (lbl);
	}

	r_cons_canvas_gotoxy (ui->can, field_x, y);
	r_cons_canvas_write (ui->can, "[");

	int len = strlen (buf);
	int scroll = ui->input_scroll;
	int cursor_vis = ui->input_cursor - scroll;
	int i;
	for (i = 0; i < field_w; i++) {
		int bi = scroll + i;
		char tmp[2] = { bi < len ? buf[bi] : ' ', 0 };
		r_cons_canvas_gotoxy (ui->can, field_x + 1 + i, y);
		if (is_active && i == cursor_vis) {
			ui->can->attr = Color_INVERT;
			r_cons_canvas_write (ui->can, tmp);
			ui->can->attr = Color_RESET;
		} else {
			r_cons_canvas_write (ui->can, tmp);
		}
	}

	r_cons_canvas_gotoxy (ui->can, field_x + 1 + field_w, y);
	char *end = r_str_newf ("]%s", Color_RESET);
	if (end) {
		r_cons_canvas_write (ui->can, end);
		free (end);
	}

	ui->layout_y++;
	return changed;
}
