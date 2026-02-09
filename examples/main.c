#include <r_core.h>
#include <stdbool.h>
#include "r2ui.h"

static bool checked = false;
static int choice = 0;
static bool selected = false;
static float progress = 0.0f;
static int tab = 0;

static void main_run(RCore *core) {
	R2UI *ui = r2ui_new (core->cons);
	ui->theme.frame_color = Color_RED;
	ui->theme.checkbox_color = Color_YELLOW;
	ui->theme.button_color = Color_BLUE;
	ui->theme.radio_button_color = Color_GREEN;
	ui->theme.selectable_color = Color_CYAN;
	ui->theme.progress_bar_color = Color_MAGENTA;
	ui->theme.tab_bar_color = Color_CYAN;
	ui->theme.menu_bar_color = Color_BLUE;
	ui->theme.box_color = Color_YELLOW;
	ui->theme.refline_color = Color_GREEN;
	if (!ui) {
		return;
	}


	while (r2ui_begin (ui)) {
		if (r2ui_menu_bar_begin (ui)) {
			if (r2ui_menu_begin (ui, "File")) {
				if (r2ui_menu_item (ui, "Open")) {
				}
				r2ui_menu_separator (ui);
				if (r2ui_menu_item (ui, "Quit")) {
					r2ui_stop (ui);
				}
				r2ui_menu_end (ui);
			}
			if (r2ui_menu_begin (ui, "Help")) {
				if (r2ui_menu_item (ui, "About")) {
				}
				r2ui_menu_end (ui);
			}
			r2ui_menu_bar_end (ui);
		}
		r2ui_text (ui, Color_GREEN "Hello from r2ui!" Color_RESET);
		r2ui_separator (ui);
		r2ui_box_begin (ui);
		r2ui_checkbox (ui, "Checkbox", &checked);
		r2ui_radio_button (ui, "Option A", &choice, 0);
		r2ui_radio_button (ui, "Option B", &choice, 1);
		r2ui_radio_button (ui, "Option C", &choice, 2);
		r2ui_box_end (ui);
		r2ui_separator (ui);
		if (r2ui_selectable (ui, "Selectable", selected)) {
			selected = !selected;
		}
		r2ui_separator (ui);
		r2ui_progress_bar (ui, progress);
		progress += 0.01f;
		if (progress > 1.0f) {
			progress = 0.0f;
		}
		r2ui_separator (ui);
		if (r2ui_tab_bar_begin (ui, &tab)) {
			if (r2ui_tab_item (ui, "Widgets", 0)) {
				r2ui_text (ui, "This is the Widgets tab");
			}
			if (r2ui_tab_item (ui, "Info", 1)) {
				r2ui_text (ui, "This is the Info tab");
			}
			if (r2ui_tab_item (ui, "About", 2)) {
				r2ui_text (ui, "r2ui demo application");
			}
			r2ui_tab_bar_end (ui);
		}
		r2ui_separator (ui);
		r2ui_refline_begin (ui, 2);
		r2ui_text (ui, "0x08048000  mov eax, 1");
		int y_jmp = r2ui_widget_y (ui);
		r2ui_text (ui, "0x08048005  cmp eax, 0");
		r2ui_text (ui, "0x08048008  je 0x08048020");
		int y_src = r2ui_widget_y (ui);
		r2ui_text (ui, "0x0804800d  call printf");
		r2ui_text (ui, "0x08048012  jmp 0x08048000");
		int y_back = r2ui_widget_y (ui);
		r2ui_text (ui, "0x08048020  xor eax, eax");
		int y_dst = r2ui_widget_y (ui);
		r2ui_refline (ui, y_src, y_dst);
		r2ui_refline (ui, y_back, y_jmp);
		r2ui_refline_end (ui);
		r2ui_separator (ui);
		if (r2ui_button (ui, "Quit")) {
			r2ui_stop (ui);
		}
		if (r2ui_key_pressed (ui, R2UI_KEY_CTRL_C) || r2ui_key_pressed (ui, R2UI_KEY_Q)) {
			r2ui_stop (ui);
		}
		r2ui_end (ui);
	}
	r2ui_free (ui);
}

static bool main_call(RCorePluginSession *cps, const char *input) {
	if (r_str_startswith (input, "r2ui")) {
		main_run (cps->core);
		return true;
	}
	return false;
}

static bool main_init(RCorePluginSession *cps) { return true; }
static bool main_fini(RCorePluginSession *cps) { return true; }

RCorePlugin r_core_plugin_main = {
	.meta = {
		.name = "r2ui",
		.desc = "r2ui demo plugin",
		.author = "nitanmarcel",
		.license = "MIT",
	},
	.call = main_call,
	.init = main_init,
	.fini = main_fini,
};

#ifndef R2_PLUGIN_INCORE
R_API RLibStruct radare_plugin = {
	.type = R_LIB_TYPE_CORE,
	.data = &r_core_plugin_main,
	.version = R2_VERSION,
	.abiversion = R2_ABIVERSION
};
#endif
