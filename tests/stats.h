#ifndef LUNA_UTILS_H
#define LUNA_UTILS_H

#include <stdlib.h>

#define DIV     "---------------------------------------------------------------------------------------"
#define SUB_DIV "-----------------"

#define TEST_MAX_MESSAGE 100

typedef struct stats {
  unsigned int miss;
  unsigned int success;

  unsigned int messages_count;
  char *messages[TEST_MAX_MESSAGE];
} stats;

stats *stats_new() {
  stats *st = (stats *)malloc(sizeof(stats));

  st->miss = st->success = st->messages_count = 0;

  return st;
}

void stats_appendMessage(stats *st, char *message) {
  if (st->messages_count >= TEST_MAX_MESSAGE)
    return;

  st->messages[st->messages_count] = message;
  st->messages_count++;
}

void stats_print(stats *st) {
  for (int i = 0; i < st->messages_count; ++i)
    printf("\t[ERROR #%2d]: %s\n", i, st->messages[i]);

  float ratio = (float)st->success / (float)(st->miss + st->success);
  printf("stats: success<%d>, miss<%d>, ratio<%.2f%%>\n", st->success, st->miss, ratio * 100.0);
}

#endif //LUNA_UTILS_H
