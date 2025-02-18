#include "cexil_font_transpiler_parser.h"

#include <stdlib.h>

const char* cexil_font_transpiler_parser_prefix_character_set = "character_set:";
const char* cexil_font_transpiler_parser_prefix_size_width = "size_width:";
const char* cexil_font_transpiler_parser_prefix_size_height = "size_height:";

const char* cexil_font_transpiler_parser_prefixes[CEXIL_FONT_TRANSPILER_PARSER_PARAMETER_COUNT] = {
  CEXIL_FONT_TRANSPILER_PARSER_PREFIX_CHARACTER_SET,
  CEXIL_FONT_TRANSPILER_PARSER_PREFIX_SIZE_WIDTH,
  CEXIL_FONT_TRANSPILER_PARSER_PREFIX_SIZE_HEIGHT
};

struct cexil_font_transpiler_intermediary* cexil_font_transpiler_parser_parse(
  FILE* file_cexil_font
) {
  static struct cexil_font_transpiler_intermediary* intermediary;

  intermediary = malloc(
    sizeof(
      struct cexil_font_transpiler_intermediary
    )
  );

  cexil_font_transpiler_intermediary_initialize(
    intermediary
  );

  char* buffer_line;
  unsigned int buffer_line_length = 0;
  buffer_line = malloc(
    sizeof(char) * buffer_line_length
  );

  char buffer_char;
  char buffer_char_last;

  enum cexil_font_transpiler_parser_mode mode = (
    cexil_font_transpiler_parser_mode_parameters
  );

  unsigned char parameter_validation[CEXIL_FONT_TRANSPILER_PARSER_PARAMETER_COUNT];
  
  for (
    unsigned int parameter_index = 0;
    parameter_index < CEXIL_FONT_TRANSPILER_PARSER_PARAMETER_COUNT;
    ++parameter_index
  ) {
    parameter_validation[parameter_index] = 1;
  }

  while (feof(file_cexil_font) == 0) {
    buffer_char_last = buffer_char;
    buffer_char = fgetc(file_cexil_font);

    buffer_line_length = buffer_line_length + 1;
    buffer_line = realloc(
      buffer_line,
      sizeof(char) * buffer_line_length
    );

    if (
      buffer_char == '\n' || buffer_char == EOF
    ) {
      buffer_line[buffer_line_length - 1] = '\0';

      switch (mode) {
        case cexil_font_transpiler_parser_mode_parameters:
          for (
            unsigned int buffer_line_index = 0;
            buffer_line_index < buffer_line_length;
            ++buffer_line_index
          ) {
            
          }

          break;
        case cexil_font_transpiler_parser_mode_characters:
          break;
        default:
          return intermediary;
      }

      buffer_line_length = 0;
      buffer_line = realloc(
        buffer_line,
        sizeof(char) * buffer_line_length
      );
    } else {
      buffer_line[buffer_line_length - 1] = (
        buffer_char
      );
    }
  }

  free(buffer_line);

  return intermediary;
}

