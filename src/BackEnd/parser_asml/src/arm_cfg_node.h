/**
 * \file      arm_cfg_node.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Definition of the control flow graph
 */

#ifndef __ARM_CFG_NODE_H__
#define __ARM_CFG_NODE_H__

#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>

#include "arm_cfg_element.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_cfg_node
   *  \brief The node of a control flow graph
   */
  class arm_cfg_node {
    friend class arm_cfg_factory;
    friend class arm_register_optimizer;
  public:
    /**
     * \brief  This function add an element to the node
     * \param  elt the element to add
     */
    void add_element (arm_cfg_element*);

    /**
     * \brief  This function looks into every elements of the node and add
     *         them to the variable used_variables and var_instr
     */
    void find_vars (void);

    /**
     * \brief  This function adds an successor to this node
     * \param  succ the element to add as a successor
     */
    void add_succ (arm_cfg_node*);

    /**
     * \brief  This function returns the list of the elements used in this node
     * \return the list of variables
     */
    list<string>* get_vars (void);

    vector<arm_cfg_node*>* get_succs (void);
    vector<arm_cfg_node*>* get_preds (void);
  protected:
    /**
     * \brief  This function adds a node as predecessors of this node
     * \param  pred the node to add as predecessor
     */
    void add_pred (arm_cfg_node*);

    vector<arm_cfg_node*> preds;            /*!< vector of the predecessors of this node */
    vector<arm_cfg_node*> succs;            /*!< vector of the successord of this node */
    vector<arm_cfg_element*> elements;      /*!< vector of elements in this node */
    vector<list<string>*> var_instr;        /*!< vector of list of used variables in each instructions */
    list<string> used_variables;            /*!< list of used variables */
    set<string> destroyed_variables;        /*!< list of variables destroyed by the optimization */
    vector<map<string, string>> regs_maps;  /*!< vecror the mapping between the variables and the registers in each instructons */
    vector<map<string, int>> scope;         /*!< Vector of the mapping between each variables and their scope in every instructions */
    vector<int> nb_regs;                    /*!< vector of the number of regs in every instructons in  the node */
  };

}

#endif //__ARM_CFG_NODE_H__
