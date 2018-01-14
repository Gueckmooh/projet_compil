#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "env.h"
#include "list.h"

plist empty() {
  plist l = malloc(sizeof(list_t));
  l->logicalLength = 0;
  l->head = NULL;
  return l;
}

plist cons(void *element, plist l) {
    plist new = malloc(sizeof(list_t));
    listNode *node = malloc(sizeof(listNode));
    node->data = element;
    node->next = l->head;
    new->head = node;
    new->logicalLength = l->logicalLength + 1;
    return new;
}

void *head(plist l) {
   assert(l->head != NULL);
   return l->head->data;
}

plist tail(plist l) {
  assert(l->head != NULL);
  plist new = malloc(sizeof(list_t));
  new->head = l->head->next;
  new->logicalLength = l->logicalLength - 1;
  return new;
}

plist append(plist l1, plist l2) {
    if (is_empty(l1)) {
        return l2;
    } else {
        return cons(head(l1), append(tail(l1), l2));
    }
}


int list_size(list_t *list)
{
  return list->logicalLength;
}


bool is_empty(list_t *list) {
    return (list_size(list) == 0);
}

bool is_in_str_list(plist l, char *str){
    listNode *l_node = l->head;
    while(l_node != NULL){
        if(strcmp((char *)l_node->data, str) == 0){
            return true;
        }
        l_node = l_node->next;
    }
    return false;
}
