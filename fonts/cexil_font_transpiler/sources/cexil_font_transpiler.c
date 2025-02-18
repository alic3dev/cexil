#include "cexil_font_transpiler.h"

#include <stdio.h>

#include "cexil_font_transpiler_intermediary.h"
#include "cexil_font_transpiler_parser.h"
#include "cexil_font_transpiler_print_usage.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    cexil_font_transpiler_print_usage(1);
    return 1;
  }

  FILE* file_input_font = fopen(
    argv[1],
    "r"
  );

  struct cexil_font_transpiler_intermediary* intermediary = (
    cexil_font_transpiler_parser_parse(
      file_input_font
    )
  );

  fclose(file_input_font);

  printf(
    "character_set: %s\n"
    "characters_count: %u\n"
    "size_width: %u\n"
    "size_height: %u\n",
    intermediary->character_set,
    intermediary->characters_count,
    intermediary->size_width,
    intermediary->size_height
  );

  cexil_font_transpiler_intermediary_destroy(
    intermediary
  );

  return 0;
}

