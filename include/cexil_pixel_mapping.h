#ifndef __CEXIL_PIXEL_MAPPING_H
#define __CEXIL_PIXEL_MAPPING_H

#define CEXIL_PIXEL_GROUP_WIDTH 2
#define CEXIL_PIXEL_GROUP_HEIGHT 4

#define CEXIL_PIXEL_MAPPING_LENGTH 256
#define CEXIL_PIXEL_MAPPING_STRING_LENGTH 3

unsigned short int cexil_pixel_group_to_index(
  unsigned char**
);

extern char cexil_pixel_mapping[
  CEXIL_PIXEL_MAPPING_LENGTH
][
  CEXIL_PIXEL_MAPPING_STRING_LENGTH
];

#endif

