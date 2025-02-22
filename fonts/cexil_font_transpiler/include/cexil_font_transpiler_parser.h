#ifndef __CEXIL_FONT_TRANSPILER_PARSER_H
#define __CEXIL_FONT_TRANSPILER_PARSER_H

#include <stdio.h>

#include "cexil_font_transpiler_intermediary.h"

enum cexil_font_transpiler_parser_mode {
  cexil_font_transpiler_parser_mode_parameters,
  cexil_font_transpiler_parser_mode_characters
};

#define CEXIL_FONT_TRANSPILER_PARSER_PREFIX_CHARACTER_SET "character_set:"
#define CEXIL_FONT_TRANSPILER_PARSER_PREFIX_SIZE_WIDTH "size_width:"
#define CEXIL_FONT_TRANSPILER_PARSER_PREFIX_SIZE_HEIGHT "size_height:"

#define CEXIL_FONT_TRANSPILER_PARSER_PARAMETER_COUNT 3

enum cexil_font_transpiler_parser_parameter {
  cexil_font_transpiler_parser_parameter_character_set,
  cexil_font_transpiler_parser_parameter_size_width,
  cexil_font_transpiler_parser_parameter_size_height
};

extern const char* cexil_font_transpiler_parser_prefixes[CEXIL_FONT_TRANSPILER_PARSER_PARAMETER_COUNT];

struct cexil_font_transpiler_intermediary* cexil_font_transpiler_parser_parse(
  FILE*,
  char*
);

#endif

