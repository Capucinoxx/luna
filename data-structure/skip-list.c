#include <stdlib.h>
#include "skip-list.h"

unsigned int _random_level() {
  unsigned int level = 1;

  while ((rand() & 0xffff) < (0xffff / 2))
    level++;

  if (level < MAX_LEVEL)
    return level;
  return MAX_LEVEL;
}

skipList *skipList_new() {
  skipList *sl = (skipList *)malloc(sizeof(skipList));

  sl->hdr = (skipList_node *)malloc(sizeof(skipList_node));
  for (int i = 0; i < MAX_LEVEL; ++i)
    sl->hdr->forward[i] = NULL;

  sl->count = sl->level = 0;

  return sl;
}

void skipList_put(skipList *sl, t_key key, t_val val) {
  skipList_node  *update[MAX_LEVEL];

  for (int i = 0; i < MAX_LEVEL; ++i)
    sl->buf[i] = update[i] = NULL;

  skipList_node *node = sl->hdr;

  for (int i = sl->level - 1; i >= 0; --i) {
    while (node->forward[i] != NULL && node->forward[i]->key < key)
      node = node->forward[i];
    update[i] = node;
  }

  unsigned int level = _random_level();
  if (level > sl->level) {
    for (int i = sl->level; i < level; ++i)
      update[i] = sl->hdr;
    sl->level = level;
  }

  node = (skipList_node *)malloc(sizeof(skipList_node));
  node->key = key;
  node->val = val;

  for (int i = 0; i < level; ++i) {
    node->forward[i] = update[i]->forward[i];
    update[i]->forward[i] = node;
  }
  sl->count++;
}

skipList_node *skipList_get(skipList *sl, t_key key) {
  skipList_node *node = sl->hdr;

  for (int i = sl->level - 1; i >= 0; --i) {
    while (node->forward[i] != NULL && node->forward[i]->key < key)
      node = node->forward[i];
  }

  node = node->forward[0];
  if (node != NULL && node->key == key)
    return node;

  return NULL;
}

void skipList_free(skipList *sl) {
  free(sl->hdr);
  free(sl);
}