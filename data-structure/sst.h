#ifndef LUNA_SNTABLE_H
#define LUNA_SNTABLE_H

#include <pthread.h>
#include "skip-list.h"

#define FILENAME "luna.sst"

/* block:
 * +---------------------------------------------------------+
 * |  Header  (list offset)                                  |
 * +---------------------------------------------------------+
 * | > Data                                                  |
 * | Sérialisation d'une entrée:                             |
 * | +-----------------------------------------------------+ |
 * | | key_size: 4bytes | key | value_size: 4bytes | value | |
 * | +-----------------------------------------------------+ |
 * +---------------------------------------------------------+
 */

typedef struct sst_record {
  unsigned int size;
  unsigned int key_size;
  t_key key;
  unsigned int val_size;
  t_val val;
} sst_record;

typedef struct sst_header {
  unsigned int last_key;
  unsigned int count;
  unsigned int end_offset;
  unsigned int crc;
} sst_header;

typedef struct sst_block {
  unsigned int key;
  unsigned int offset;
} sst_block;

typedef struct sst {
  unsigned int lsn;
  pthread_mutex_t mu;

  sst_header hdr;
  unsigned int hdr_offset;
} sst;

/**
 * écrit les valeurs dans le fichier
 *
 * @param s     structure sst utilisé
 * @param sl    données à ajouter
 */
void _sst_write(sst *s, skipList *sl);

/**
 * constructeur d'une nouvelle instance d'un sst
 *
 * @return nouvelle instance du sst
 */
sst *sst_new();

/**
 * s'occupe de persister les valeurs en mémoire
 *
 * @param s     structure sst utilisé
 * @param sl    données à persister
 */
void sst_merge(sst *s, skipList *sl);

#endif //LUNA_SNTABLE_H
