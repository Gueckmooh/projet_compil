#ifndef __ASML_BINARY_NODE_H__
#define __ASML_BINARY_NODE_H__

#include "asml_unary_node.h"
#include "asml_boolean.h"

namespace asml {

  class asml_binary_node : public asml_unary_node {
  public:
    asml_binary_node (void);
    virtual ~asml_binary_node (void) {};

    virtual asml_boolean* get_boolean (void);
    virtual asml_node* get_next_true (void);
    virtual asml_node* get_next_false (void);

    virtual void set_boolean (asml_boolean*);
    virtual void set_next_true (asml_node*);
    virtual void set_next_false (asml_node*);
  protected:
    asml_node* next_true;
    asml_node* next_false;
    asml_boolean* boolean;
  };

}

#endif // __ASML_BINARY_NODE_H__
