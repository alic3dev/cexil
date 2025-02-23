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
  FILE* file_cexil_font,
  char* name
) {
  static struct cexil_font_transpiler_intermediary* intermediary;

  intermediary = malloc(
    sizeof(
      struct cexil_font_transpiler_intermediary
    )
  );

  cexil_font_transpiler_intermediary_initialize(
    intermediary,
    name
  );

  enum cexil_font_transpiler_parser_mode mode = (
    cexil_font_transpiler_parser_mode_parameters
  );

  char buffer_char = '\0';
  char buffer_char_last = '\0';

  char* buffer_line = malloc(0);
  long buffer_line_length = 0;

  long position_line_beginning = 0;
  long position_line_end = 0;

  unsigned int character_y_index = 0;

  while (feof(file_cexil_font) == 0) {
    buffer_char_last = buffer_char;
    buffer_char = fgetc(file_cexil_font);

    if (
      buffer_char == '\n' || buffer_char == EOF
    ) {
      position_line_end = ftell(file_cexil_font);
      buffer_line_length = position_line_end - position_line_beginning + 2;
      
      buffer_line = realloc(
        buffer_line,
        sizeof(char) * buffer_line_length
      );

      fseek(
        file_cexil_font,
        -(buffer_line_length - 2),
        SEEK_CUR
      );

      char* fgets_status = fgets(
        buffer_line,
        buffer_line_length,
        file_cexil_font
      );

      if (fgets_status == NULL) {
        if (ferror(file_cexil_font) != 0) {
          intermediary->error = cexil_font_transpiler_intermediary_error_file_io;
        }

        return intermediary;
      }
      
      position_line_beginning = ftell(file_cexil_font);
    } else {
      continue;
    }
    
    switch (mode) {
      case cexil_font_transpiler_parser_mode_parameters:
        if (buffer_char_last == '\n') {
          mode = cexil_font_transpiler_parser_mode_characters;
          break;
        }

        signed int parameter_index_found = -1;
        unsigned int parameter_character_index = 0;
         
        for (
          unsigned int parameter_index = 0;
          parameter_index < CEXIL_FONT_TRANSPILER_PARSER_PARAMETER_COUNT;
          ++parameter_index
        ) {
          parameter_character_index = 0;
          
          while (1) {
            if (
              cexil_font_transpiler_parser_prefixes[
                parameter_index
              ][parameter_character_index] == '\0'
            ) {
              parameter_index_found = parameter_index;
              
              break;
            }

            if (
              buffer_line[parameter_character_index] !=
              cexil_font_transpiler_parser_prefixes[parameter_index][parameter_character_index]
            ) {
              break;
            }
              
            parameter_character_index = parameter_character_index + 1;
          }
          
          if (parameter_index_found != -1) {
            break;
          }
        }

        if (parameter_index_found == -1) {
          intermediary->error = cexil_font_transpiler_intermediary_error_parsing;
          return intermediary;
        }

        unsigned int parameter_value_length = (
          buffer_line_length - parameter_character_index - 2
        );

        switch (parameter_index_found) {
          case cexil_font_transpiler_parser_parameter_character_set:
            intermediary->character_set = realloc(
              intermediary->character_set,
              sizeof(char) * 
              parameter_value_length
            );

            for (
              unsigned int parameter_value_index = 0;
              parameter_value_index < parameter_value_length - 1;
              ++parameter_value_index
            ) {
              intermediary->character_set[parameter_value_index] = (
                buffer_line[parameter_character_index + parameter_value_index]
              );
            }
  
            intermediary->character_set[parameter_value_length - 1] = '\0';
            break;
          case cexil_font_transpiler_parser_parameter_size_width:
            intermediary->size_width = 0;
            
            for (
              unsigned int parameter_value_index = 0;
              parameter_value_index < parameter_value_length - 1;
              ++parameter_value_index
            ) {
              char potential_digit = buffer_line[
                parameter_character_index + parameter_value_index
              ];

              if (potential_digit < '0' || potential_digit > '9') {
                intermediary->error = cexil_font_transpiler_intermediary_error_parsing;
                return intermediary;
              }
 
              intermediary->size_width = (
                (intermediary->size_width * 10) +
                (potential_digit - '0')
              );
            }
            break;
          case cexil_font_transpiler_parser_parameter_size_height:
            intermediary->size_height = 0;
            
            for (
              unsigned int parameter_value_index = 0;
              parameter_value_index < parameter_value_length - 1;
              ++parameter_value_index
            ) {
              char potential_digit = buffer_line[
                parameter_character_index + parameter_value_index
              ];
              
              if (potential_digit < '0' || potential_digit > '9') {
                intermediary->error = cexil_font_transpiler_intermediary_error_parsing;
                return intermediary;
              }

              intermediary->size_height = (
                (intermediary->size_height * 10) +
                (potential_digit - '0')
              );
            }
            break;
          default:
            intermediary->error = cexil_font_transpiler_intermediary_error_unknown;
            return intermediary;
        }  
        break;
      case cexil_font_transpiler_parser_mode_characters:
        if (buffer_line_length == 3 || intermediary->characters_count == 0) {
          character_y_index = 0;
          
          intermediary->characters_count = intermediary->characters_count + 1;

          intermediary->characters = realloc(
            intermediary->characters,
            sizeof(char**) * intermediary->characters_count
          );

          intermediary->characters[
            intermediary->characters_count - 1
          ] = malloc(
            sizeof(char*) * intermediary->size_height
          );

          for (
            unsigned int y_index = 0;
            y_index < intermediary->size_height;
            ++y_index
          ) {
            intermediary->characters[
              intermediary->characters_count - 1
            ][y_index] = malloc(
              sizeof(char) * intermediary->size_width
            );
              
            for (
              unsigned int x_index = 0;
              x_index < intermediary->size_width;
              ++x_index
            ) {
              intermediary->characters[intermediary->characters_count - 1][y_index][x_index] = 0;
            }
          }
        }
        
        if (buffer_line_length != 3) {
          if (
            character_y_index >= intermediary->size_height ||
            buffer_line_length - 3 != intermediary->size_width
          ) {
           intermediary->error = cexil_font_transpiler_intermediary_error_parsing;
           return intermediary;
          }

          for (
            unsigned int x_index = 0;
            x_index < buffer_line_length - 3;
            ++x_index
          ) {
            char buffer_character_character = buffer_line[x_index];
            
            if (
              buffer_character_character != '0' &&
              buffer_character_character != '.'
            ) {
              intermediary->error = cexil_font_transpiler_intermediary_error_parsing;
              return intermediary;
            } else if (buffer_character_character == '0') {
              intermediary->characters[
                intermediary->characters_count - 1
              ][character_y_index][x_index] = 1;
            }
          }
  
          character_y_index = character_y_index + 1;
        }
        
        break;
      default:
        intermediary->error = cexil_font_transpiler_intermediary_error_unknown; 
        return intermediary;
    }
  }

  free(buffer_line);
  
  return intermediary;
}

