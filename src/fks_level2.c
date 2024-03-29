#include "../inc/fks_level2.h"
#include "../inc/hash_func.h"
#include <string.h>
#include<stdio.h>

fks_level2 *fks_level2_init(uint32_t size, hash_parameters parameters) {
  // TODO
  fks_level2 *table = malloc(sizeof(fks_level2));
  if (table == NULL) {
    return NULL;
  }
  if (size == 0) {
    return NULL;
  }
  table->size = size;
  table->parameters = parameters;
  table->slots = malloc(sizeof(uint32_t) * size);
  for (uint32_t i = 0; i < size; i++) {
    table->slots[i] = FKS_LEVEL2_EMPTY;
  }
  return table;
}

fks_level2 *fks_level2_build(list_node *head, uint32_t size,
                             hash_parameters parameters) {
  // TODO
  fks_level2 *table = fks_level2_init(size, parameters);
  if (table == NULL) {
    return NULL;
  }
  list_node *current = head;
  while (current != NULL) {
    if (fks_level2_insert(table, current->key) == false) {
      free(table->slots);
      free(table);
      table = fks_level2_init(size, generate_hash_parameters());
      current = head;
    } else {
      current = current->next;
    }
  }
  return table;
}

bool fks_level2_insert(fks_level2 *table, uint32_t key) {
  // TODO
  if (table == NULL) {
    return false;
  } 
  uint32_t num = hash_func(key, table->parameters, table->size);
  if (table->slots[num] != FKS_LEVEL2_EMPTY && key != table->slots[num]) {
    return false;
  }
  table->slots[num] = key;
  return true;
}

bool fks_level2_search(fks_level2 *table, uint32_t key) {
  // TODO
  if (table == NULL) {
    return false;
  } 
  return table->slots[hash_func(key, table->parameters, table->size)] == key;
}

void fks_level2_destroy(fks_level2 *table) {
  // TODO
  if (table != NULL) {
    free(table->slots);
    free(table);
  }
}