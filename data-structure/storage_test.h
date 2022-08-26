#ifndef LUNA_STORAGE_TEST_H
#define LUNA_STORAGE_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include "storage.h"
#include "../tests/stats.h"

stats *_get_present_pairs_without_flush();
stats *_get_present_pairs_with_flush();

void test_storage() {
  puts("> rapport lorsque l'on recherche des cles presentes sans debordement");
  stats_print(_get_present_pairs_without_flush());
  puts(SUB_DIV);

  puts("> rapport lorsque l'on recherche des cles presentes avec debordement");
  stats_print(_get_present_pairs_with_flush());
}

stats *_get_present_pairs_without_flush() {
  stats *st = stats_new();

  storage *s = storage_new();

  for (int i = 0; i < 10; ++i)
    storage_put(s, i, i);

  for (int i = 0; i < 10; ++i) {
    storage_output res = storage_get(s, i);
    if (res.found)
      st->success++;
    else {
      char *buf = malloc(100);
      sprintf(buf, "la cle %d devrait etre presente", i);
      stats_appendMessage(st, buf);

      st->miss++;
    }
  }

  return st;
}

stats *_get_present_pairs_with_flush() {
  stats *st = stats_new();

  storage *s = storage_new();

  for (int i = 0; i < 200; ++i)
    storage_put(s, i, i);

  for (int i = 0; i < 200; ++i) {
    storage_output res = storage_get(s, i);
    if (res.found)
      st->success++;
    else {
      char *buf = malloc(100);
      sprintf(buf, "la cle %d devrait etre presente", i);
      stats_appendMessage(st, buf);

      st->miss++;
    }
  }

  return st;
}

#endif //LUNA_STORAGE_TEST_H
