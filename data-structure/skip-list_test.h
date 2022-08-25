#ifndef LUNA_SKIP_LIST_TEST_H
#define LUNA_SKIP_LIST_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include "skip-list.h"
#include "../tests/stats.h"

stats *_get_present_pairs();
stats *_get_absent_pairs();


void test_skipList() {
  printf("> rapport lorsque l'on recherche des cles presentes\n");
  stats_print(_get_present_pairs());
  puts(SUB_DIV);

  printf("> rapport lorsque l'on recherche des cles absentes\n");
  stats_print(_get_absent_pairs());
}

stats *_get_present_pairs() {
  stats *st = stats_new();

  skipList *sl = skipList_new();

  for (int i = 0; i < 10; ++i)
    skipList_put(sl, i, i);

  for (int i = 0; i < 10; ++i) {
    skipList_node *node = skipList_get(sl, i);
    if (node == NULL) {
      char *buf = malloc(100);
      sprintf(buf, "la cle %d devrait etre presente", i);
      stats_appendMessage(st, buf);

      st->miss++;
    } else
      st->success++;
  }

  skipList_free(sl);
  return st;
}

stats *_get_absent_pairs() {
  stats *st = stats_new();

  skipList *sl = skipList_new();

  for (int i = 0; i < 10; ++i)
    skipList_put(sl, i, i);

  for (int i = 100; i < 110; ++i) {
    skipList_node *node = skipList_get(sl, i);
    if (node != NULL) {
      char *buf = malloc(100);
      sprintf(buf, "la cle %d ne devrait pas etre presente", i);
      stats_appendMessage(st, buf);

      st->miss++;
    } else
      st->success++;
  }

  skipList_free(sl);
  return st;
}

#endif //LUNA_SKIP_LIST_TEST_H
