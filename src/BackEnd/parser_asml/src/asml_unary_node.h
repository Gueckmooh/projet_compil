#ifndef __ASML_UNARY_NODE_H__
#define __ASML_UNARY_NODE_H__

#include "asml_node.h"
#include "asml_instruction.h"

namespace asml {

  class asml_unary_node : public asml_node {
  public:
    asml_unary_node (void);
    virtual ~asml_unary_node (void) {};

    virtual asml_instruction* get_instruction (void);
    virtual asml_node* get_next (void);

    virtual void set_instruction (asml_instruction*);
    virtual void set_next (asml_node*);
  protected:
    asml_node* next;
    asml_instruction* instruction;
  };

}

#endif // __ASML_UNARY_NODE_H__
