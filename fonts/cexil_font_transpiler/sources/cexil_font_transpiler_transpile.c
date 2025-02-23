#include "cexil_font_transpiler_transpile.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const unsigned int __path_directory_output_final_sources_directory_length = 7;
const unsigned int __path_directory_output_final_include_directory_length = 7;
const unsigned int __path_directory_output_final_sources_file_extension_length = 2;
const unsigned int __path_directory_output_final_include_file_extension_length = 2;

const char* __path_directory_output_final_sources_directory = "sources";
const char* __path_directory_output_final_include_directory = "include";
const char* __path_directory_output_final_sources_file_extension = ".c";
const char* __path_directory_output_final_include_file_extension = ".h";

unsigned char cexil_font_transpiler_transpile(
  struct cexil_font_transpiler_intermediary* intermediary,
  char* path_directory_output
) {
  int mkdir_status = mkdir(
    path_directory_output,
    S_IRWXU | S_IRWXG | S_IRWXO
  );
  
  if (mkdir_status != 0 && errno != EEXIST) {
    fprintf(
      stderr,
      "unable_to_create_directory: %s\n",
      path_directory_output
    );
    return 1;
  }
  
  unsigned int path_directory_output_final_length = 2;
  char* path_directory_output_final = malloc(
    sizeof(char) * path_directory_output_final_length
  );
  
  for (
    unsigned int path_index = 0;
    path_directory_output[path_index] != '\0';
    ++path_index
  ) {
    path_directory_output_final_length = path_directory_output_final_length + 1;

    path_directory_output_final = realloc(
      path_directory_output_final,
      sizeof(char) * path_directory_output_final_length
    );

    path_directory_output_final[path_index] = (
      path_directory_output[path_index]
    );
  }
  
  path_directory_output_final[
    path_directory_output_final_length - 2
  ] = '/';

  unsigned int name_length = 0;

  for (
    unsigned int name_index = 0;
    intermediary->name[name_index] != '\0';
    ++name_index
  ) {
    name_length = name_length + 1;
    path_directory_output_final_length = path_directory_output_final_length + 1;
    
    path_directory_output_final = realloc(
      path_directory_output_final,
      sizeof(char) * path_directory_output_final_length
    );

    path_directory_output_final[path_directory_output_final_length - 2] = (
      intermediary->name[name_index]
    );
  }
  
  path_directory_output_final[
    path_directory_output_final_length - 1
  ] = '\0';

  mkdir_status = mkdir(
    path_directory_output_final,
    S_IRWXU | S_IRWXG | S_IRWXO
  );

  if (mkdir_status != 0 && errno != EEXIST) {
    fprintf(
      stderr,
      "unable_to_create_directory: %s\n",
      path_directory_output_final
    );
    
    free(path_directory_output_final);
    return 1;
  }

  unsigned int path_directory_output_final_sources_directory_length = (
    path_directory_output_final_length + __path_directory_output_final_sources_directory_length + 1
  );
  unsigned int path_directory_output_final_include_directory_length = (
    path_directory_output_final_length + __path_directory_output_final_include_directory_length + 1
  );
  unsigned int path_directory_output_final_sources_file_length = (
    path_directory_output_final_sources_directory_length + 
    name_length + 
    __path_directory_output_final_sources_file_extension_length +
    2
  );
  unsigned int path_directory_output_final_include_file_length = (
    path_directory_output_final_include_directory_length + 
    name_length + 
    __path_directory_output_final_include_file_extension_length +
    2
  );

  char* path_directory_output_final_sources_directory = malloc(
    sizeof(char) * path_directory_output_final_sources_directory_length
  );
  char* path_directory_output_final_include_directory = malloc(
    sizeof(char) * path_directory_output_final_include_directory_length
  );
  char* path_directory_output_final_sources_file = malloc(
    sizeof(char) * path_directory_output_final_sources_file_length
  );
  char* path_directory_output_final_include_file = malloc(
    sizeof(char) * path_directory_output_final_include_file_length
  );

  for (
    unsigned int path_index = 0;
    path_index < path_directory_output_final_length;
    ++path_index
  ) {
    char path_char = path_directory_output_final[path_index];

    path_directory_output_final_sources_directory[path_index] = path_char;
    path_directory_output_final_include_directory[path_index] = path_char;
    path_directory_output_final_sources_file[path_index] = path_char;
    path_directory_output_final_include_file[path_index] = path_char;
  }
  
  path_directory_output_final_sources_directory[
    path_directory_output_final_length - 1
  ] = '/';
  path_directory_output_final_include_directory[
    path_directory_output_final_length - 1
  ] = '/';
  path_directory_output_final_sources_file[
    path_directory_output_final_length - 1
  ] = '/';
  path_directory_output_final_include_file[
    path_directory_output_final_length - 1
  ] = '/';

  for (
    unsigned int sources_directory_index = 0;
    sources_directory_index < __path_directory_output_final_sources_directory_length;
    ++sources_directory_index
  ) {
    char sources_directory_char = __path_directory_output_final_sources_directory[
      sources_directory_index
    ];
    unsigned int path_index = (
      path_directory_output_final_length +
      sources_directory_index
    );

    path_directory_output_final_sources_directory[
      path_index
    ] = sources_directory_char;

    path_directory_output_final_sources_file[
      path_index
    ] = sources_directory_char;
  }
  
  for (
    unsigned int include_directory_index = 0;
    include_directory_index < __path_directory_output_final_include_directory_length;
    ++include_directory_index
  ) {
    char include_directory_char = __path_directory_output_final_include_directory[
      include_directory_index
    ];
    unsigned int path_index = (
      path_directory_output_final_length +
      include_directory_index
    );

    path_directory_output_final_include_directory[
      path_index
    ] = include_directory_char;

    path_directory_output_final_include_file[
      path_index
    ] = include_directory_char;
  }

  path_directory_output_final_sources_file[
    path_directory_output_final_sources_directory_length - 1
  ] = '/';

  path_directory_output_final_include_file[
    path_directory_output_final_include_directory_length - 1
  ] = '/';
 
  char* name_upper = malloc(sizeof(char) * (name_length + 1));
  char* name_lower = malloc(sizeof(char) * (name_length + 1));

  for (
    unsigned int name_index = 0;
    name_index < name_length;
    ++name_index
  ) {
    char name_upper_char = intermediary->name[name_index];
    char name_lower_char = name_upper_char;

    if (name_upper_char >= 'a' && name_upper_char <= 'z') {
      name_upper_char = name_upper_char + ('A' - 'a');
    } else if (name_lower_char >= 'A' && name_lower_char <= 'Z') {
      name_lower_char = name_lower_char - ('A' - 'a');
    } else if (name_upper_char == ' ') {
      name_upper_char = '_';
      name_lower_char = '_';
    }

    name_upper[name_index] = name_upper_char;
    name_lower[name_index] = name_lower_char;
  }
  
  name_upper[name_length] = '\0';
  name_lower[name_length] = '\0';
  
  for (
    unsigned int name_index = 0;
    name_index < name_length;
    ++name_index
  ) {
    path_directory_output_final_sources_file[
      path_directory_output_final_sources_directory_length +
      name_index 
    ] = name_lower[name_index];
    
    path_directory_output_final_include_file[
      path_directory_output_final_include_directory_length +
      name_index 
    ] = name_lower[name_index];
  }

  for (
    unsigned int extension_index = 0;
    extension_index < __path_directory_output_final_sources_file_extension_length;
    ++extension_index
  ) {
    path_directory_output_final_sources_file[
      path_directory_output_final_sources_file_length - 
      (__path_directory_output_final_sources_file_extension_length - extension_index) -
      2
    ] = __path_directory_output_final_sources_file_extension[extension_index];
  }
   
  for (
    unsigned int extension_index = 0;
    extension_index < __path_directory_output_final_include_file_extension_length;
    ++extension_index
  ) {
    path_directory_output_final_include_file[
      path_directory_output_final_include_file_length - 
      (__path_directory_output_final_include_file_extension_length - extension_index) -
      2
    ] = __path_directory_output_final_include_file_extension[extension_index];
  }

  path_directory_output_final_sources_directory[
    path_directory_output_final_sources_directory_length - 1
  ] = '\0';
  path_directory_output_final_include_directory[
    path_directory_output_final_include_directory_length - 1
  ] = '\0';
  path_directory_output_final_sources_file[
    path_directory_output_final_sources_file_length - 1
  ] = '\0';
  path_directory_output_final_include_file[
    path_directory_output_final_include_file_length - 1
  ] = '\0';
 
  mkdir_status = mkdir(
    path_directory_output_final_sources_directory,
    S_IRWXU | S_IRWXG | S_IRWXO
  );

  if (mkdir_status != 0 && errno != EEXIST) {
    fprintf(
      stderr,
      "unable_to_create_directory: %s\n",
      path_directory_output_final_sources_directory
    );

    free(name_upper);
    free(name_lower);
    free(path_directory_output_final);
    free(path_directory_output_final_sources_directory);
    free(path_directory_output_final_include_directory);
    free(path_directory_output_final_sources_file);
    free(path_directory_output_final_include_file);
    
    return 1;
  }

  mkdir_status = mkdir(
    path_directory_output_final_include_directory,
    S_IRWXU | S_IRWXG | S_IRWXO
  );

  if (mkdir_status != 0 && errno != EEXIST) {
    fprintf(
      stderr,
      "unable_to_create_directory: %s\n",
      path_directory_output_final_include_directory
    );

    free(name_upper);
    free(name_lower); 
    free(path_directory_output_final);
    free(path_directory_output_final_sources_directory);
    free(path_directory_output_final_include_directory);
    free(path_directory_output_final_sources_file);
    free(path_directory_output_final_include_file);
    
    return 1;
  }
  
  FILE* file_directory_output_final_sources_file = fopen(
    path_directory_output_final_sources_file,
    "w"
  );

  if (file_directory_output_final_sources_file == (void*)0) {
    fprintf(
      stderr,
      "unable_to_open_for_writing: %s\n",
      path_directory_output_final_sources_file
    );
    
    free(name_upper);
    free(name_lower);
    free(path_directory_output_final);
    free(path_directory_output_final_sources_directory);
    free(path_directory_output_final_include_directory);
    free(path_directory_output_final_sources_file);
    free(path_directory_output_final_include_file);
    
    return 1;
  }

  fprintf(
    file_directory_output_final_sources_file,
    "#include \"%s.h\"\n\n"
    "const char cexil_font_definition_%s_characters[\n"
    "  CEXIL_FONT_DEFINITION_%s_CHARACTERS_COUNT\n"
    "][\n"
    "  CEXIL_FONT_DEFINITION_%s_SIZE_HEIGHT\n"
    "][\n"
    "  CEXIL_FONT_DEFINITION_%s_SIZE_WIDTH\n"
    "] = {",
    name_lower,
    name_lower,
    name_upper,
    name_upper,
    name_upper
  );

  for (
    unsigned int character_index = 0;
    character_index < intermediary->characters_count;
    ++character_index
  ) {
    fprintf(
      file_directory_output_final_sources_file,
      "%s {",
      character_index > 0 ? "," : "\n "
    );
  
    for (
      unsigned int y_index = 0;
      y_index < intermediary->size_height;
      ++y_index
    ) {
      fprintf(
        file_directory_output_final_sources_file,
        "%s\n    {",
        y_index > 0 ? "," : ""
      );

      for (
        unsigned int x_index = 0;
        x_index < intermediary->size_width;
        ++x_index
      ) {
        fprintf(
          file_directory_output_final_sources_file,
          "%s %u",
          x_index > 0 ? "," : "",
          intermediary->characters[
            character_index
          ][y_index][x_index]
        );
      }

      fprintf(
        file_directory_output_final_sources_file,
        " }"
      );
    }

    fprintf(
      file_directory_output_final_sources_file,
      "\n  }"
    );
  }

  fprintf(
    file_directory_output_final_sources_file,
    "\n};\n\n"
    "const struct cexil_font cexil_font_definition_%s = {\n"
    "  character_set: %s,"
    "  characters: (char***)(\n"
    "    cexil_font_definition_%s_characters\n"
    "  ),\n"
    "  size: {\n"
    "    width: CEXIL_FONT_DEFINITION_%s_SIZE_WIDTH,\n"
    "    height: CEXIL_FONT_DEFINITION_%s_SIZE_HEIGHT\n"
    "  }\n"
    "};\n\n",
    name_lower,
    intermediary->character_set,
    name_lower,
    name_upper,
    name_upper
  );

  FILE* file_directory_output_final_include_file = fopen(
    path_directory_output_final_include_file,
    "w"
  );

  if (file_directory_output_final_include_file == (void*)0) {
    fprintf(
      stderr,
      "unable_to_open_for_writing: %s\n",
      path_directory_output_final_include_file
    );

    fclose(file_directory_output_final_sources_file);
    
    free(name_upper);
    free(name_lower);
    free(path_directory_output_final);
    free(path_directory_output_final_sources_directory);
    free(path_directory_output_final_include_directory);
    free(path_directory_output_final_sources_file);
    free(path_directory_output_final_include_file);
    
    return 1;
  }

  fprintf(
    file_directory_output_final_include_file,
    "#ifndef __CEXIL_FONT_DEFINITION_%s_H\n"
    "#define __CEXIL_FONT_DEFINITION_%s_H\n\n"
    "#include \"cexil_font.h\"\n\n"
    "#define CEXIL_FONT_DEFINITION_%s_CHARACTERS_COUNT %u\n"
    "#define CEXIL_FONT_DEFINITION_%s_SIZE_WIDTH %u\n"
    "#define CEXIL_FONT_DEFINITION_%s_SIZE_HEIGHT %u\n\n"
    "extern const char cexil_font_definition_%s_characters[\n"
    "  CEXIL_FONT_DEFINITION_%s_CHARACTERS_COUNT\n"
    "][\n"
    "  CEXIL_FONT_DEFINITION_%s_SIZE_HEIGHT\n"
    "][\n"
    "  CEXIL_FONT_DEFINITION_%s_SIZE_WIDTH\n"
    "];\n\n"
    "extern const struct cexil_font cexil_font_definition_%s;\n\n"
    "#endif\n\n",
    name_upper,
    name_upper,
    name_upper,
    intermediary->characters_count,
    name_upper,
    intermediary->size_width,
    name_upper,
    intermediary->size_height,
    name_lower,
    name_upper,
    name_upper,
    name_upper,
    name_lower
  );

  fclose(file_directory_output_final_sources_file);
  fclose(file_directory_output_final_include_file);

  free(name_upper);
  free(name_lower);
  free(path_directory_output_final);
  free(path_directory_output_final_sources_directory);
  free(path_directory_output_final_include_directory);
  free(path_directory_output_final_sources_file);
  free(path_directory_output_final_include_file);
 
  return 0;
}

