#include <r_core.h>
#include "r2ui.h"

static bool checked = false;

static void main_run(RCore *core) {
	R2UI *ui = r2ui_new (core->cons);
	ui->theme.frame_color = Color_RED;
	ui->theme.checkbox_color = Color_YELLOW;
	ui->theme.button_color = Color_BLUE;
	if (!ui) {
		return;
	}


	while (r2ui_begin (ui)) {
		r2ui_text (ui, Color_GREEN "Hello from r2ui!" Color_RESET);
		r2ui_separator (ui);
		r2ui_checkbox (ui, "Checkbox", &checked);
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
