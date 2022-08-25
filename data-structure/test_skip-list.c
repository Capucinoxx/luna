#include <stdio.h>
#include <stdlib.h>
#include "skip-list.h"

int main() {
  skipList *sl = skipList_new();

  // insertion
  for (int i = 0; i < 10; ++i)
    skipList_put(sl, i, i);


  // get (present)
  for (int i = 0; i < 10; ++i) {
    skipList_node *node = skipList_get(sl, i);
    if (node == NULL)
      printf("la cle %d devrait etre presente\n", i);
  }

  // get (absent)
  for (int i = 100; i < 110; ++i) {
    skipList_node *node = skipList_get(sl, i);
    if (node != NULL)
      printf("la cle %d ne devrait pas etre presente\n", i);
  }

  return 0;
}