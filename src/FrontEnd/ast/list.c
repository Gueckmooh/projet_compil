#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "list.h"

plist empty() {
  plist l = (plist) malloc(sizeof(list));
  l->logicalLength = 0;
  l->head = NULL;
  return l;
}

plist cons(void *element, plist l) {
  plist new_list = (plist) malloc(sizeof(list));
  listNode *node = (listNode *) malloc(sizeof(listNode));
  node->data = element;
  node->next = l->head;
  new_list->head = node;
  new_list->logicalLength = l->logicalLength + 1;
  return new_list;
}

void *head(plist l) {
   assert(l->head != NULL);
   return l->head->data;
}

plist tail(plist l) {
  assert(l->head != NULL);
  plist new_list = (plist) malloc(sizeof(list));
  new_list->head = l->head->next;
  new_list->logicalLength = l->logicalLength - 1;
  return new_list;
}

plist append(plist l1, plist l2) {
    if (is_empty(l1)) {
        return l2;
    } else {
        return cons(head(l1), append(tail(l1), l2));
    }
}


int list_size(list *list)
{
  return list->logicalLength;
}


bool is_empty(list *list) {
    return (list_size(list) == 0);
}

plist copy_list(plist list){
    // TODO -> real copy
    return list;
}
