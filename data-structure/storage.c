#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "storage.h"

storage *storage_new() {
  storage *s = (storage *)malloc(sizeof(storage));

  s->mem = skipList_new();
  s->sst = sst_new();
  s->f = flush_new(s->sst);


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

  // si non présente en mem on va chercher dans le fichier
  // note: à déporter
  int f = open(FILENAME, O_RDONLY);
  if (f < 0)
    return out;

  unsigned int c_size = sizeof(unsigned int);

  lseek(f, s->sst->hdr.end_offset, SEEK_SET);
  // manière idiomatique, on parcours tout les éléments, (POC)
  for (int i = 0; i < s->sst->hdr.count; ++i) {
    unsigned int size;
    read(f, &size, c_size);

    unsigned int key_size;
    read(f, &key_size, c_size);

    t_key c_key;
    read(f, &c_key, key_size);

    if (c_key == key) {
      unsigned int val_size;
      read(f, &val_size, c_size);

      t_val val;
      read(f, &val, val_size);

      out.val = val;
      out.found = 1;
      return out;
    }

    lseek(f, size - c_size - key_size, SEEK_CUR);
  }

  close(f);

  return out;
}