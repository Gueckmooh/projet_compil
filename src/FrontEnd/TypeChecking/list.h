/**
 * \file      list.h
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     list constructor and destructor
 *
 */

#ifndef __LIST_H
#define __LIST_H

#include <stdbool.h>

typedef struct _listNode {
  void *data;
  struct _listNode *next;
} listNode;

typedef struct {
  int logicalLength;
  listNode *head;
} list;

typedef list *plist;

plist empty();

plist cons(void *element, plist l);

int list_size(plist l);

void *head(plist l);
plist tail(plist l);
plist append(plist l1, plist l2);
bool is_empty(plist l);
plist copy_list(plist list);
plist free_list_node(plist list);
plist free_list_string(plist list);
#endif
