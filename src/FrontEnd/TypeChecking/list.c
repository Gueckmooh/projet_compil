#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "print_ast.h"

plist empty() {
  plist l = (plist) malloc(sizeof(struct listouille));
  l->logicalLength = 0;
  l->head = NULL;
  return l;
}

plist cons(void *element, plist l) {
  plist new_list = (plist) malloc(sizeof(struct listouille));
  listNode *node = (listNode *) malloc(sizeof(listNode));
  node->data = element;
  node->next = l->head;
  new_list->head = node;
  new_list->logicalLength = l->logicalLength + 1;
  free(l) ;
  return new_list;
}

void *head(plist l) {
   assert(l->head != NULL);
   return l->head->data;
}

plist tail(plist l) {
  assert(l->head != NULL);
  plist new_list = (plist) malloc(sizeof(struct listouille));
  new_list->head = l->head->next;
  new_list->logicalLength = l->logicalLength - 1;
  return new_list;
}

plist append(plist l1, plist l2) {
    if (is_empty(l1)) {
        return l2;
    } else {
        void * element = head(l1) ;
        plist tl1 = tail(l1) ;
        plist res = cons(element, append(tl1, l2));
        free(l1->head) ;
        //free(l1) ;
        free(tl1) ;
        return res ;
    }
}


int list_size(struct listouille *list)
{
  return list->logicalLength;
}


bool is_empty(struct listouille *list) {
    return (list_size(list) == 0);
}

plist copy_list(plist list){
    // TODO -> real copy
    return list;
}

plist free_list_node(plist list) {
    if (list) {
        listNode * node = list->head, *tmp ;
        while (node) {
            tmp = node ;
            node = node->next ;
            free_ast(tmp->data) ;
            free(tmp) ;
        }
        
        free(list) ;
    }
    
    return NULL ;
}

plist free_list_string (plist list) {
    if (list) {
        listNode * node = list->head, *tmp ;
        while (node) {
            tmp = node ;
            node = node->next ;
            free(tmp->data) ;
            free(tmp) ;
        }
        
        free(list) ;
    }
    
    return NULL ;
}