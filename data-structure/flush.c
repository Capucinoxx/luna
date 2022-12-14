#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "flush.h"

void *_flush(void *arg) {
  _thread_flush_t *data = (_thread_flush_t *)arg;

  sst_merge(data->sst, data->sl);

  skipList_free(data->sl);

  pthread_exit(0);
}

flush *flush_new(sst *sst) {
  flush *f = (flush *)malloc(sizeof(flush));

  f->sst = sst;

  for (int i = 0; i < MAX_ELEMS_IN_FLUSH_QUEUE; ++i)
    f->queue[i] = NULL;

  return f;
}

void flush_append(flush *f, skipList *sl) {
  // TODO: gestion intelligente de l'id
  int id = 0;

  pthread_t tid;

  _thread_flush_t *data = (_thread_flush_t *)malloc(sizeof(_thread_flush_t));
  data->id = id;
  data->sl = sl;
  data->sst = f->sst;
  f->queue[id] = data;

  pthread_create(&tid, NULL, _flush, data);
  pthread_join(tid, NULL);
}