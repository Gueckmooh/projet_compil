/**
 * \file      arm_dom_node.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     The node of the dominance graph
 */

#ifndef __ARM_DOM_NODE_H__
#define __ARM_DOM_NODE_H__

#include <string>
#include <list>
#include <vector>

#include "arm_cfg_node.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_addition
   *  \brief Contains the classes that manages the asml
   */
  class arm_dom_node {
    friend class arm_register_optimizer;
  public:
    arm_dom_node (void) {};
    arm_dom_node (arm_cfg_node*);
    void set_element (arm_cfg_node*);
    arm_cfg_node* get_element (void) const;

    /**
     * \brief adds a successor to the node
     * \param node the node to add to the successors
     */
    void add_succ (arm_dom_node*);
    vector<arm_dom_node*>* get_succs (void) const;
    list<string>* get_variables_to_reduce (void) const;
    /**
     * \brief  This function finds the leafs of the dominance graph
     * \return a list<arm_dom_node*>*, the list of the leaves ???
     */
    list<arm_dom_node*>* find_leafs (void);

    /**
     * \brief This functon adds a list of variables used in the node
     * \param vars the list of variables to add to the variables used in the node
     */
    void add_succ_vars (list<string>*);
  protected:
    /**
     * \brief set the predecessor of the node
     * \param node the node to set as predecessor
     */
    void set_pred (arm_dom_node* node);
    list<string>* succ_vars;             /*!< The list of variables used in the successors   */
    list<string>* pred_vars;             /*!< The list of variables used in the predecessor  */
    list<string>* variables;             /*!< The list of variables used in this node        */
    list<string>* variables_to_reduce;   /*!< The list of variables that can be suppressed   */
    arm_cfg_node* element;               /*!< The element of the node                        */
    mutable vector<arm_dom_node*> succs; /*!< The list of successors of the node             */
    mutable arm_dom_node* pred;          /*!< The predecessor of the node                    */
  };

}

#endif//__ARM_DOM_NODE_H__
