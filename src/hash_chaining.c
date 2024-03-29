#include "../inc/hash_chaining.h"
#include "../inc/hash_func.h"


hash_chaining *hash_chaining_init(uint32_t size) {
  // TODO
  hash_chaining *table = malloc(sizeof(hash_chaining));
  if (table == NULL) {
    return NULL;
  }
  if (size == 0) {
    free(table);
    return NULL;
  }
  table->size = size;
  table->slots = malloc(sizeof(list_node *) * size);
  for (uint32_t i = 0; i < size; i++) {
    table->slots[i] = NULL;
  }
  table->parameters = generate_hash_parameters();
  return table;
}

void hash_chaining_insert(hash_chaining *table, uint32_t key) {
  // TODO
  if (table == NULL) {
    return;
  }
  list_node *node = malloc(sizeof(list_node));
  node->key = key;
  node->next = table->slots[hash_func(key, table->parameters, table->size)];
  table->slots[hash_func(key, table->parameters, table->size)] = node;
}

bool hash_chaining_search(hash_chaining *table, uint32_t key) {
  // TODO
  list_node *node = table->slots[hash_func(key, table->parameters, table->size)];
  while (node != NULL) {
    if (node->key == key) {
      return true;
    } else {
      node = node->next;
    } 
  }
  return false;
}

void hash_chaining_destroy(hash_chaining *table) {
  // TODO
  if (table == NULL) {
    return;
  }
  for (uint32_t i = 0; i < table->size; i++)
  {
    list_node *node = table->slots[i];
    while (node != NULL) {
      list_node *ptr = node;
      node = node->next;
      free(ptr);
    }
  }
  free(table->slots);
  free(table);
}
