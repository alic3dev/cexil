#include "cexil_font_transpiler_print_usage.h"

#include <stdio.h>

void cexil_font_transpiler_print_usage(
  unsigned char stream_error_use
) {
  FILE* stream_output = (
    stream_error_use == 1
    ? stderr
    : stdout
  );

  fprintf(
    stream_output,
    "USAGE: cexil_font_transpiler input.cexil_font output_directory\n"
  );
}

