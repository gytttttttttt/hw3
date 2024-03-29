#include "../inc/fks_level1.h"
#include "../inc/hash_func.h"
#include <stdio.h>

static int get_list_len(list_node *node) {
  // TODO
  int length = 0;
  while (node != NULL) {
    length++;
    node = node->next;
  }
  return length;
}

fks_level1 *fks_level1_build(hash_chaining *hash_chaining_table) {
  // TODO
  if (hash_chaining_table == NULL) {
    return NULL;
  } 
  fks_level1 *table = malloc(sizeof(fks_level1));
  table->size = hash_chaining_table->size;
  table->level2_tables = malloc(table->size * sizeof(fks_level2 *));
  table->parameters = hash_chaining_table->parameters;
  for (uint32_t i = 0; i < table->size; i++) {
    list_node *node = hash_chaining_table->slots[i];
    int len = get_list_len(node) * get_list_len(node);
    if (node == NULL) {
      table->level2_tables[i] = NULL;
    } else {
      table->level2_tables[i] = fks_level2_build(node, len, generate_hash_parameters());
    }
  }
  return table;
}

bool fks_level1_search(fks_level1 *table, uint32_t key) {
  // TODO
  return fks_level2_search(table->level2_tables[hash_func(key, table->parameters, table->size)], key);
}

void fks_level1_destroy(fks_level1 *table) {
  // TODO
  if (table == NULL) {
    return;
  }
  for (uint32_t i = 0; i < table->size; i++) {
    if (table->level2_tables[i] != NULL) {
      fks_level2_destroy(table->level2_tables[i]);
    }
  }
  free(table->level2_tables);
  free(table);
}