/**
 * \file      asml_binary_node.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_binary_node class
 */

#ifndef __ASML_BINARY_NODE_H__
#define __ASML_BINARY_NODE_H__

#include "asml_unary_node.h"
#include "asml_boolean.h"

/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {

  /*! \class   asml_binary_node
   *  \brief   class that represent binary node for asml tree
   *  \details it inherits from asml_unary_node
   *           it is used to manage if then else statements
   */
  class asml_binary_node : public asml_unary_node {
  public:
    asml_binary_node (void);
    virtual ~asml_binary_node (void) {};

    virtual string get_var (void);
    virtual asml_boolean* get_boolean (void);
    virtual asml_node* get_next_true (void);
    virtual asml_node* get_next_false (void);

    virtual void set_var (string);
    virtual void set_boolean (asml_boolean*);
    virtual void set_next_true (asml_node*);
    virtual void set_next_false (asml_node*);
  protected:
    string var;             /*! name of the variable associated to the node */
    asml_node* next_true;   /*! pointer to the node of the true branch */
    asml_node* next_false;  /*! pointer to the node of the false branch */
    asml_boolean* boolean;  /*! pointer to the asml_boolean corresponding to the condition */
  };

}

#endif // __ASML_BINARY_NODE_H__
