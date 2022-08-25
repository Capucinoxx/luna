#ifndef LUNA_STORAGE_H
#define LUNA_STORAGE_H

#include "skip-list.h"

#define NB_MEM_TABLES 10

typedef struct storage_output {
  t_val val;
  int found;
} storage_output;


typedef struct storage {
  skipList *memTable[NB_MEM_TABLES];

  unsigned int flushThreshold;
} storage;

/**
 * constructeur d'une nouvelle instance d'une storage
 *
 * @return nouvelle instance du storage
 */
storage *storage_new();

/**
 * insère une nouvelle paire clé - valeur dans le storage
 *
 * @param s     storage ciblé
 * @param key   clé voulant être insérée
 * @param val   valeur voulant être insérée
 */
void storage_put(storage *s, t_key key, t_val val);

/**
 * regarde si la clé a une valeur associée. Si la clé
 * n'est pas présente dans le storage, le structure de
 * retour devrait avoir la valeur found à 0,
 *
 * @param s     storage ciblé
 * @param key   clé voulant être insérée
 * @return      structure donnant la valeur et si cette valeur a été trouvée
 */
storage_output storage_get(storage *s, t_key key);

#endif //LUNA_STORAGE_H
