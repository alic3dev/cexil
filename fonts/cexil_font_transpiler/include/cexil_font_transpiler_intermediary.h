#ifndef __CEXIL_FONT_TRANSPILER_INTERMEDIARY_H
#define __CEXIL_FONT_TRANSPILER_INTERMEDIARY_H

struct cexil_font_transpiler_intermediary_error {
  char* message;
  int status_code;
};

struct cexil_font_transpiler_intermediary {
  char* character_set;
  char*** characters;
  unsigned int characters_count;
  unsigned int size_width;
  unsigned int size_height;
  struct cexil_font_transpiler_intermediary_error* error;
};

void cexil_font_transpiler_intermediary_initialize(
  struct cexil_font_transpiler_intermediary*
);

void cexil_font_transpiler_intermediary_destroy(
  struct cexil_font_transpiler_intermediary*
);

#endif

