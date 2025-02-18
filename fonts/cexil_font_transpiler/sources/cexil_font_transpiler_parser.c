#include "cexil_font_transpiler_parser.h"

#include <stdlib.h>

const char* cexil_font_transpiler_parser_prefix_character_set = "character_set:";
const char* cexil_font_transpiler_parser_prefix_size_width = "size_width:";
const char* cexil_font_transpiler_parser_prefix_size_height = "size_height:";

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

