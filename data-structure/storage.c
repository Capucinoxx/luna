#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

storage *storage_new() {
  storage *s = (storage *)malloc(sizeof(storage));

  s->mem = skipList_new();
  s->f = flush_new();

  return s;
}

void storage_put(storage *s, t_key key, t_val val) {
  skipList_put(s->mem, key, val);

  if (s->mem->count >= FLUSH_THRESHOLD) {
    printf("[DEBUG] flush mem table\n");

    skipList mem;
    memcpy(&mem, s->mem, sizeof(skipList));

    flush_append(s->f, s->mem);

    s->mem = skipList_new();
  }
}

storage_output storage_get(storage *s, t_key key) {
  storage_output out;
  out.found = 0;

  skipList_node *node = skipList_get(s->mem, key);
  if (node != NULL) {
    out.val = node->val;
    out.found = 1;
    return out;
  }

  return out;
}

void storage_free(storage *s) {
//  flush_free(s->f);
}