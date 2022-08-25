#ifndef LUNA_SKIP_LIST_H
#define LUNA_SKIP_LIST_H

#define MAX_LEVEL 25

typedef unsigned int t_key;
typedef unsigned int t_val;

typedef struct skipList_node {
  t_key key;
  t_val val;
  struct skipList_node *forward[MAX_LEVEL];
} skipList_node;

typedef struct skipList {
  unsigned int count;
  unsigned int level;

  skipList_node *hdr;
  skipList_node *buf[MAX_LEVEL];
} skipList;

/**
 * générateur d'un valeur aléatoire comprise entre: [0, MAX_LEVEL[
 *
 * @return niveau généré aléatoirement
 */
unsigned int _random_level();

/**
 * constructeur d'une nouvelle instance d'une skipList
 *
 * @return nouvelle instance de la skipList
 */
skipList *skipList_new();

/**
 * insère une paire clé - valeur dans la structure
 *
 * @param sl structure ciblée
 * @param key clé voulant être insérée
 * @param val valeur voulant être insérée
 */
void skipList_put(skipList *sl, t_key key, t_val val);

/**
 * regarde si la clé a une valeur associé à la clé. Retourne NULL
 * si n'est pas présent dans la structure
 *
 * @param sl structure ciblée
 * @param key clé recherchée
 * @return valeur NULL si clé non présente
 */
skipList_node *skipList_get(skipList *sl, t_key key);

/**
 * libère les ressource d'une skip list
 *
 * @param sl structure à libérée
 */
void skipList_free(skipList *sl);

#endif //LUNA_SKIP_LIST_H
