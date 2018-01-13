#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "list.h"
#include "env.h"
#include "closure.h"
#include "print_and_write.h"

extern plist fd_list;

void convert_fd_bodies(){
    listNode *l_node = fd_list->head;
    while(l_node != NULL){
        convert_fd_body((pfundef)l_node->data);
        l_node = l_node->next;
    }
}

void convert_fd_body(pfundef fd){

}
