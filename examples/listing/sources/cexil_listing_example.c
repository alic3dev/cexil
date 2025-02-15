#include "cexil_listing_example.h"

#include <stdio.h>

#include "cexil.h"

int main() {
  for (unsigned short int p = 0; p < 256; ++p) {
    char pixels[4] = {
      cexil_pixel_mapping[p][0],
      cexil_pixel_mapping[p][1],
      cexil_pixel_mapping[p][2],
      '\0'
    };

    if (p < 10) {
      printf("00%i: %s\n", p, pixels);
    } else if (p < 100) {
      printf("0%i: %s\n", p, pixels);
    } else {
      printf("%i: %s\n", p, pixels);
    }
  }
  
  return 0;
}

