#include "cexil_font_transpiler.h"

#include <stdio.h>
#include <stdlib.h>

#include "cexil_font_transpiler_intermediary.h"
#include "cexil_font_transpiler_options.h"
#include "cexil_font_transpiler_parser.h"
#include "cexil_font_transpiler_print_usage.h"
#include "cexil_font_transpiler_transpile.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    cexil_font_transpiler_print_usage(1);
    return 1;
  }

  FILE* file_input_font = fopen(
    argv[1],
    "r"
  );
  
  unsigned int name_starting_index = 0;
  
  for (
    unsigned int path_index = 0;
    argv[1][path_index] != '\0';
    ++path_index
  ) {
    name_starting_index = name_starting_index + 1;
  }

  for (
    signed int path_index = name_starting_index;
    path_index >= 0 && argv[1][path_index] != '/';
    --path_index
  ) {
    name_starting_index = path_index;
  }

  char* name = malloc(1);
  name[0] = '\0';

  unsigned char has_extension = 0;
  unsigned int extension_index = 0;
  
  for (
    unsigned int path_index = name_starting_index;
    argv[1][path_index] != '\0';
    ++path_index
  ) {
    unsigned int name_index = path_index - name_starting_index;

    name = realloc(
      name,
      sizeof(char) * (name_index + 2)
    );
    
    name[name_index] = argv[1][path_index];
    name[name_index + 1] = '\0';

    if (name[name_index] == '.') {
      has_extension = 1;
      extension_index = name_index;
    }
  }

  if (has_extension) {
    name = realloc(
      name,
      sizeof(char) * (extension_index + 1)
    );
    
    name[extension_index] = '\0';
  }

  struct cexil_font_transpiler_intermediary* intermediary = (
    cexil_font_transpiler_parser_parse(
      file_input_font,
      name
    )
  );

  free(name);

  fclose(file_input_font);

  int status_code_return = 0;

  if (
    intermediary->error ==
    cexil_font_transpiler_intermediary_error_none
  ) {
    unsigned char transpile_status = cexil_font_transpiler_transpile(
      intermediary,
      argv[2]
    );

    if (transpile_status == 0) {
      if (cexil_font_transpiler_option_display_basic_info != 0) {
        cexil_font_transpiler_intermediary_print_basic_info(
          intermediary
        );
      }
    
      if (cexil_font_transpiler_option_display_characters != 0) {
        cexil_font_transpiler_intermediary_print_characters(
          intermediary
        );
      }
    } else {
      fprintf(stderr, "Something went wrong while transpiling\n");
      status_code_return = 1;
    }
  } else {
    status_code_return = 1;
    cexil_font_transpiler_intermediary_print_error(
      intermediary
    );
  }

  cexil_font_transpiler_intermediary_destroy(
    intermediary
  );
  
  free(intermediary);

  return status_code_return;
}

