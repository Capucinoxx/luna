#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "sst.h"

#ifdef __unix__
#define O_BINARY 0x00
#endif

sst *sst_new() {
  sst *s = (sst *)malloc(sizeof(sst));

  s->lsn = 0;
  pthread_mutex_init(&s->mu, NULL);

  s->hdr_offset = sizeof(sst_header);

  int f = open(FILENAME, O_RDONLY);
  if (f < 0) {
    close(f);
    f = open(FILENAME, O_WRONLY | O_APPEND | O_CREAT, 0644);
    s->hdr.count = s->hdr.last_key = 0;
    s->hdr.end_offset = s->hdr_offset;
    write(f, &s->hdr, s->hdr_offset);
  } else {
    read(f, &s->hdr, s->hdr_offset);
  }

  close(f);

  return s;
}

void sst_merge(sst *s, skipList *sl) {
  _sst_write(s, sl);
}

void _sst_write(sst *s, skipList *sl) {
  skipList_node *node = sl->hdr->forward[0];

  int f = open(FILENAME, O_RDONLY | O_WRONLY | O_APPEND | O_BINARY);
  if (f < 0)
    return;

  lseek(f, s->hdr.end_offset, SEEK_SET);
  for (int i = 0; i < sl->count; ++i) {
    int size = 0;

    sst_record rec;
    rec.key_size = sizeof(node->key);
    rec.key = node->key;
    rec.val_size = sizeof(node->val);
    rec.val = node->val;

    size = sizeof(rec.key_size) + sizeof(rec.val_size) + rec.key_size + rec.val_size;
    rec.size = size;

    write(f, &rec, size + sizeof(rec.size));

    s->hdr.count++;
    node = node->forward[0];
  }

  close(f);
}
