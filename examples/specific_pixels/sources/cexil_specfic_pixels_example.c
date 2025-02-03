#include "cexil_specific_pixels_example.h"

#include <stdio.h>

#include "cexil.h"

int main() {
  const unsigned char x_size = 12;
  const unsigned char y_size = 16;
  unsigned char pixels[x_size][y_size];

  for (unsigned char x = 0; x < x_size; ++x) {
    for (unsigned char y = 0; y < y_size; ++y) {
      pixels[x][y] = 0;
    }
  }
  pixels[7][7] = 1;
  pixels[7][6] = 1;
  pixels[7][5] = 1;
  pixels[8][5] = 1;
  pixels[4][7] = 1;
  pixels[4][6] = 1;
  pixels[4][5] = 1;
  pixels[3][5] = 1;
  
  pixels[1][4] = 1;
  pixels[1][3] = 1;
  pixels[0][4] = 1;
  pixels[2][2] = 1;
  pixels[2][3] = 1;
  pixels[2][4] = 1;
  pixels[3][4] = 1;
  pixels[4][4] = 1;
  pixels[5][4] = 1;
  pixels[6][4] = 1;
  pixels[7][4] = 1;
  pixels[8][4] = 1;
  pixels[9][4] = 1;
  pixels[10][4] = 1;
  pixels[11][4] = 1;
  pixels[8][3] = 1;
  pixels[10][3] = 1;
  pixels[3][0] = 1;
  pixels[3][1] = 1; 
  pixels[3][2] = 1;
  pixels[3][3] = 1;
  pixels[4][1] = 1; 
  pixels[4][2] = 1;
  pixels[4][3] = 1;
  pixels[5][3] = 1;
  pixels[6][3] = 1;
  pixels[7][1] = 1; 
  pixels[7][2] = 1;
  pixels[7][3] = 1;
  pixels[8][0] = 1;
  pixels[8][1] = 1; 
  pixels[8][2] = 1;
  pixels[8][3] = 1;
  pixels[9][2] = 1;
  pixels[9][3] = 1;
  pixels[5][5] = 1;
  pixels[5][6] = 1;
  pixels[5][7] = 1;
  pixels[5][8] = 1;
  pixels[5][9] = 1;
  pixels[5][10] = 1;
  pixels[5][11] = 1; 
  pixels[5][12] = 1; 
  pixels[5][13] = 1; 
  pixels[5][15] = 1; 
  pixels[6][5] = 1;
  pixels[6][6] = 1;
  pixels[6][7] = 1;
  pixels[6][8] = 1;
  pixels[6][9] = 1;
  pixels[6][10] = 1;
  pixels[6][11] = 1;
  
  const unsigned char x_group = 2;
  const unsigned char y_group = 4;

  for (
    unsigned char y_index = 0;
    y_index < y_size;
    y_index = y_index + y_group
  ) {
    for (
      unsigned char x_index = 0;
      x_index < x_size;
      x_index = x_index + x_group
    ) {
      unsigned char pixel_mapping_index = 0;

      if (pixels[x_index][y_index]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00000001
        );
      }
      
      if (pixels[x_index][y_index + 1]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00000010
        );
      }

      if (pixels[x_index][y_index + 2]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00000100
        );
      }

      if (pixels[x_index][y_index + 3]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b01000000
        );
      }
     
      if (pixels[x_index + 1][y_index]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00001000
        );
      }
      
      if (pixels[x_index + 1][y_index + 1]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00010000
        );
      }

      if (pixels[x_index + 1][y_index + 2]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b00100000
        );
      }

      if (pixels[x_index + 1][y_index + 3]) {
        pixel_mapping_index = (
          pixel_mapping_index +
          0b10000000
        );
      }
      char pixels_string[4] = {
        pixel_mapping[pixel_mapping_index][0],
        pixel_mapping[pixel_mapping_index][1],
        pixel_mapping[pixel_mapping_index][2],
        '\0'
      };

      printf("%s", pixels_string);
    }

    printf("\n");
  }
  
  return 0;
}

