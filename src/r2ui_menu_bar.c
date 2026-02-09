#include "r2ui.h"

R2UI_API bool r2ui_menu_bar_begin(R2UI *ui) {
	if (!ui || !ui->can) {
		return false;
	}
	ui->menu_bar_y = ui->layout_y;
	ui->menu_header_x = ui->layout_x;
	ui->menu_idx = 0;
	ui->menu_drop_count = 0;
	ui->menu_drop_max_w = 0;
	ui->menu_any_interact = false;
	ui->layout_y++;
	return true;
}

R2UI_API bool r2ui_menu_begin(R2UI *ui, const char *label) {
	if (!ui || !ui->can || !label) {
		return false;
	}
	int my_idx = ui->menu_idx++;
	int x = ui->menu_header_x;
	int y = ui->menu_bar_y;
	bool is_open = (ui->menu_open == my_idx);
	char *buf;
	if (is_open) {
		const char *color = ui->theme.menu_bar_color ? ui->theme.menu_bar_color : Color_INVERT;
		buf = r_str_newf ("%s[%s]%s", color, label, Color_RESET);
	} else {
		buf = r_str_newf (" %s ", label);
	}
	int len = strlen (label) + 2;
	if (buf) {
		r_cons_canvas_gotoxy (ui->can, x, y);
		r_cons_canvas_write (ui->can, buf);
		free (buf);
	}
	if (ui->click_y == y && ui->click_x >= x && ui->click_x < x + len) {
		if (is_open) {
			ui->menu_open = -1;
		} else {
			ui->menu_open = my_idx;
		}
		ui->menu_any_interact = true;
		is_open = (ui->menu_open == my_idx);
	}
	ui->menu_header_x += len;
	if (is_open) {
		ui->menu_drop_x = x;
		ui->menu_drop_y = y + 1;
		ui->menu_drop_count = 0;
		ui->menu_drop_max_w = 0;
	}
	return is_open;
}

R2UI_API bool r2ui_menu_item(R2UI *ui, const char *label) {
	if (!ui || !ui->can || !label) {
		return false;
	}
	if (ui->menu_drop_count >= R2UI_MENU_MAX_ITEMS) {
		return false;
	}
	int idx = ui->menu_drop_count;
	int item_y = ui->menu_drop_y + idx;
	int item_x = ui->menu_drop_x;
	int len = strlen (label);
	if (len > ui->menu_drop_max_w) {
		ui->menu_drop_max_w = len;
	}
	ui->menu_drop_items[idx] = label;
	ui->menu_drop_count++;
	if (ui->click_y == item_y && ui->click_x >= item_x && ui->click_x < item_x + len + 4) {
		ui->menu_open = -1;
		ui->menu_any_interact = true;
		return true;
	}
	return false;
}

R2UI_API void r2ui_menu_separator(R2UI *ui) {
	if (!ui || ui->menu_drop_count >= R2UI_MENU_MAX_ITEMS) {
		return;
	}
	ui->menu_drop_items[ui->menu_drop_count] = NULL;
	ui->menu_drop_count++;
}

R2UI_API void r2ui_menu_end(R2UI *ui) {
	(void)ui;
}

R2UI_API void r2ui_menu_bar_end(R2UI *ui) {
	if (!ui) {
		return;
	}
	if (ui->click_x >= 0 && ui->click_y >= 0 && !ui->menu_any_interact) {
		ui->menu_open = -1;
	}
}

R2UI_API void r2ui_menu_render(R2UI *ui) {
	if (!ui || !ui->can || ui->menu_open < 0 || ui->menu_drop_count == 0) {
		return;
	}
	int pad_w = ui->menu_drop_max_w + 4;
	char *pad = malloc (pad_w + 1);
	if (!pad) {
		return;
	}

	int i;
	for (i = 0; i < ui->menu_drop_count; i++) {
		const char *label = ui->menu_drop_items[i];
		if (!label) {
			memset (pad, '-', pad_w);
			pad[pad_w] = '\0';
		} else {
			int len = snprintf (pad, pad_w + 1, "  %s", label);
			if (len < pad_w) {
				memset (pad + len, ' ', pad_w - len);
			}
			pad[pad_w] = '\0';
		}
		char *buf = r_str_newf ("%s%s%s", ui->theme.menu_bar_color ? ui->theme.menu_bar_color : Color_INVERT, pad, Color_RESET);
		if (buf) {
			r_cons_canvas_gotoxy (ui->can, ui->menu_drop_x, ui->menu_drop_y + i);
			r_cons_canvas_write (ui->can, buf);
			free (buf);
		}
	}
	free (pad);
}
