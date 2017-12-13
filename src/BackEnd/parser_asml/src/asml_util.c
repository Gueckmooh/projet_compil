#include "asml_util.h"

void first_word (char* dest, char* src) {
  int idxmax = 0;
  while (src[idxmax] != ' ' && src[idxmax] != '\n' && src[idxmax] != '\0')
    idxmax++;
  dest = (char*) malloc (sizeof(char)*idxmax+1);
  strncpy (dest, src, idxmax);
  dest[idxmax] = '\0';
}
