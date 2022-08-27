#ifndef LUNA_FLUSH_H
#define LUNA_FLUSH_H

#include <pthread.h>
#include "sst.h"
#include "skip-list.h"

#define MAX_ELEMS_IN_FLUSH_QUEUE 10

typedef struct _thread_flush_t {
  unsigned int id;
  skipList *sl;

  sst *sst;
} _thread_flush_t;

typedef struct flush {
  _thread_flush_t *queue[MAX_ELEMS_IN_FLUSH_QUEUE];
  pthread_t tid[MAX_ELEMS_IN_FLUSH_QUEUE];

  sst *sst;
} flush;

/**
 * fonction retirant une skipList de la mémoire pour le faire persister
 *
 * @param arg pointeur faisant référence à _thread_flush_t
 * @return
 */
void *_flush(void *arg);

/**
 * constructeur d'une nouvelle instance d'un flush
 *
 * @return nouvelle instance
 */
flush *flush_new(sst *sst);

/**
 * insère une nouvelle table en mémoire à se faire
 * persister.
 *
 * @param f
 * @param sl
 */
void flush_append(flush *f, skipList *sl);


#endif //LUNA_FLUSH_H
