#include "cexil_font_transpiler_intermediary.h"

#include <stdlib.h>
#include <stdio.h>

#include "cexil_font_transpiler_options.h"

void cexil_font_transpiler_intermediary_initialize(
  struct cexil_font_transpiler_intermediary* intermediary,
  char* name
) {
  intermediary->name = malloc(1);
  intermediary->name[0] = '\0';
  
  for (
    unsigned int name_index = 0;
    name[name_index] != '\0';
    ++name_index
  ) {
    intermediary->name = realloc(
      intermediary->name,
      sizeof(char) * (name_index + 2)
    );
    
    intermediary->name[name_index] = name[name_index];
    intermediary->name[name_index + 1] = '\0';
  }

  intermediary->character_set = malloc(0);
  intermediary->characters = malloc(0);
  intermediary->characters_count = 0;
  intermediary->size_width = 0;
  intermediary->size_height = 0;
  intermediary->error = cexil_font_transpiler_intermediary_error_none;
}

void cexil_font_transpiler_intermediary_character_add(
  struct cexil_font_transpiler_intermediary* intermediary,
  char** character
) {
  intermediary->characters_count = intermediary->characters_count + 1;
  intermediary->characters = realloc(
    intermediary->characters,
    sizeof(char**) * intermediary->characters_count
  );

  intermediary->characters[intermediary->characters_count - 1] = malloc(
    sizeof(char*) * intermediary->size_height
  );

  for (
    unsigned int y_index = 0;
    y_index < intermediary->size_height;
    ++y_index
  ) {
    intermediary->characters[intermediary->characters_count - 1] = malloc(
      sizeof(char) * intermediary->size_width
    );

    for (
      unsigned int x_index = 0;
      x_index < intermediary->size_width;
      ++x_index
    ) {
      intermediary->characters[intermediary->characters_count - 1][y_index][x_index] = character[y_index][x_index];      
    }
  }
}

void cexil_font_transpiler_intermediary_print_basic_info(
  struct cexil_font_transpiler_intermediary* intermediary
) {
  printf(
    "name: %s\n"
    "character_set: %s\n"
    "characters_count: %u\n"
    "size_width: %u\n"
    "size_height: %u\n",
    intermediary->name,
    intermediary->character_set,
    intermediary->characters_count,
    intermediary->size_width,
    intermediary->size_height
  );
}

void cexil_font_transpiler_intermediary_print_characters(
  struct cexil_font_transpiler_intermediary* intermediary
) {
  for (
    unsigned int character_index = 0;
    character_index < intermediary->characters_count;
    ++character_index
  ) {
    if (cexil_font_transpiler_option_display_characters_numbers != 0) {
      printf(
        "__%s%u__\n",
        character_index < 10 ? "0" : "",
        character_index
      );
    }

    for (
      unsigned int y_index = 0;
      y_index < intermediary->size_height;
      ++y_index
    ) {
      for (
        unsigned int x_index = 0;
        x_index < intermediary->size_width;
        ++x_index
      ) {
        printf(
          "%c",
          intermediary->characters[
            character_index
          ][y_index][x_index] == 0 ? ' ' : '#'
        );
      }

      printf("\n");
    }

    printf("\n");
  }
}

void cexil_font_transpiler_intermediary_print_error(
  struct cexil_font_transpiler_intermediary* intermediary
) {
  switch (intermediary->error) {
    case cexil_font_transpiler_intermediary_error_none:
      break;
    case cexil_font_transpiler_intermediary_error_file_io:
      fprintf(
        stderr,
        "Something went wrong while opening, reading, or writting a file\n"
      );
      break;
    case cexil_font_transpiler_intermediary_error_parsing:
      fprintf(
        stderr,
        "Something went wrong while trying to parse the font file\n"
        "Ensure the file is properly formatted\n"
      );
      break;
    case cexil_font_transpiler_intermediary_error_unknown:
    default:
      fprintf(
        stderr,
        "An unknown error has occured\n"
      );
      break;
  } 
}

void cexil_font_transpiler_intermediary_destroy(
  struct cexil_font_transpiler_intermediary* intermediary
) {
  free(intermediary->name);
  free(intermediary->character_set);

  for (
    unsigned int index_character;
    index_character < 
    intermediary->characters_count;
    ++index_character
  ) {
    for (
      unsigned int index_y = 0;
      index_y < intermediary->size_height;
      ++index_y
    ) {
      free(
        intermediary->characters[
          index_character
        ][index_y]
      );
    }

    free(
      intermediary->characters[index_character]
    );
  }

  free(intermediary->characters);
}

