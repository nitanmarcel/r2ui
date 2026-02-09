#ifndef R2UI_H
#define R2UI_H

#if defined(__GNUC__) && __GNUC__ >= 4
  #define R2UI_API __attribute__((visibility("default")))
#elif defined(_MSC_VER)
  #define R2UI_API __declspec(dllexport)
#else
  #define R2UI_API
#endif

#include "r2ui_keys.h"
#include "r2ui_core.h"

R2UI_API R2UI *r2ui_new(RCons *cons);
R2UI_API void r2ui_free(R2UI *ui);
R2UI_API bool r2ui_begin(R2UI *ui);
R2UI_API void r2ui_end(R2UI *ui);
R2UI_API bool r2ui_key_pressed(R2UI *ui, int key);
R2UI_API void r2ui_text(R2UI *ui, const char *fmt, ...);
R2UI_API void r2ui_stop(R2UI *ui);

#endif
