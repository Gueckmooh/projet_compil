/**
 * \file      arm_register_optimizer.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Optiomization of the use of the registers
 */

#ifndef __ARM_REGISTER_OPTIMIZER_H__
#define __ARM_REGISTER_OPTIMIZER_H__

#include <functional>

#include "arm_dom_node.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_register_optimizer
   *  \brief Optimize the register
   */
  class arm_register_optimizer {
  public:
    arm_register_optimizer (void) {};
    arm_register_optimizer (arm_dom_node*);

    arm_dom_node* get_dom_root (void);
    void set_dom_root (arm_dom_node*);

    /**
     * \brief This function optimize the register allocation
     */
    void optimize (void);

    /**
     * \brief This function finds the variables used in the node that
     *        succede to node
     * \param node the node for which we have to find the variables of the
     *        successors
     */
    void find_succs_variables (arm_dom_node*);

    /**
     * \brief This function finds the variables used in the node that
     *        is the predecessor of node
     * \param node the node for which we have to find the variables of the
     *        predecessor
     */
    void find_preds_variables (arm_dom_node*);

    /**
     * \brief This function finds the variables in the node
     * \param node the node in which to find the variables
     */
    void find_variables (arm_dom_node*);

    /**
     * \brief This function finds the variables that qwe can suppress
     *        during the optimization
     * \param node the node in which to find the varibles that we can
     *        suppress
     */
    void find_variables_to_reduce (arm_dom_node*);

    /**
     * \brief This function finds the scope of the variables in the node
     * \param node the node in which to finf the scope ov variables
     */
    void find_scope (arm_dom_node*);

    /**
     * \brief This function optimize the use of registers in the node
     * \param node the node in which we have to optimize the use of registers
     */
    void optimize_node (arm_dom_node*);
  protected:
    arm_dom_node* dom_root;              /*!< The root of the dominance graph */
    list<arm_dom_node*> already_visited; /*!< The list of node that has been
                                           already visited */
  };

}

#endif//__ARM_REGISTER_OPTIMIZER_H__
