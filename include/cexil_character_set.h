#ifndef __CEXIL_CHARACTER_SET
#define __CEXIL_CHARACTER_SET

enum cexil_character_set {
  ascii,
  lower
};

signed int cexil_character_set_index_get(
  enum cexil_character_set,
  char
);

#endif

