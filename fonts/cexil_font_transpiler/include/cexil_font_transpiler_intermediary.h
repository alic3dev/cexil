#ifndef __CEXIL_FONT_TRANSPILER_INTERMEDIARY_H
#define __CEXIL_FONT_TRANSPILER_INTERMEDIARY_H

enum cexil_font_transpiler_intermediary_error {
  cexil_font_transpiler_intermediary_error_none,
  cexil_font_transpiler_intermediary_error_file_io,
  cexil_font_transpiler_intermediary_error_parsing,
  cexil_font_transpiler_intermediary_error_unknown
};

struct cexil_font_transpiler_intermediary {
  char* name;
  char* character_set;
  char*** characters;
  unsigned int characters_count;
  unsigned int size_width;
  unsigned int size_height;
  enum cexil_font_transpiler_intermediary_error error;
};

void cexil_font_transpiler_intermediary_initialize(
  struct cexil_font_transpiler_intermediary*,
  char*
);

void cexil_font_transpiler_intermediary_character_add(
  struct cexil_font_transpiler_intermediary*,
  char**
);

void cexil_font_transpiler_intermediary_print_basic_info(
  struct cexil_font_transpiler_intermediary*
);

void cexil_font_transpiler_intermediary_print_characters(
  struct cexil_font_transpiler_intermediary*
);

void cexil_font_transpiler_intermediary_print_error(
  struct cexil_font_transpiler_intermediary*
);

void cexil_font_transpiler_intermediary_destroy(
  struct cexil_font_transpiler_intermediary*
);

#endif

