#ifndef __CEXIL_FONT_TRANSPILER_PARSER_H
#define __CEXIL_FONT_TRANSPILER_PARSER_H

#include <stdio.h>

#include "cexil_font_transpiler_intermediary.h"

extern const char* cexil_font_transpiler_parser_prefix_character_set;
extern const char* cexil_font_transpiler_parser_prefix_size_width;
extern const char* cexil_font_transpiler_parser_prefix_size_height;

enum cexil_font_transpiler_parser_mode {
  cexil_font_transpiler_parser_mode_parameters,
  cexil_font_transpiler_parser_mode_characters
};

struct cexil_font_transpiler_intermediary* cexil_font_transpiler_parser_parse(
  FILE* file
);

#endif

