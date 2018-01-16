/**
 * \file      arm_dom_node_factory.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     The factory that creates dominance graph
 */

#ifndef __ARM_DOM_NODE_FACTORY_H__
#define __ARM_DOM_NODE_FACTORY_H__

#include <map>
#include <set>
#include <vector>

#include "arm_cfg_node.h"
#include "arm_dom_node.h"

using namespace std;

namespace arm {

  class arm_dom_node_factory {
  public:

    /**
     * \brief   constructor of the dominance graph factory
     * \details This function takes the root of the control flow
     *          graph that is used to generate the dominance graph
     * \param   root the root of the control flow graph
     */
    arm_dom_node_factory (arm_cfg_node*);

    /**
     * \brief  This function generates a dominance tree using the control
     *         flow graph given to the constructor
     * \return an arm_dom_node*, the root of the dominance graph generated
     */
    arm_dom_node* generate (void);
  protected:
    typedef pair<arm_cfg_node*, arm_cfg_node*> succ;
    typedef vector<arm_cfg_node*> path;

    /**
     * \brief This function construct the dominance tree
     * \param node an arm_cfg_node* that has to be the root of the control
     *        flow graph to transform (this function use it recursively
     */
    void gen (arm_cfg_node*);

    /**
     * \brief  This function checks if a node is present in a path
     * \param  node the node to find in the path
     * \param  s the parh in which to search
     * \return true if the node is present in the path, false if not
     */
    bool present (arm_cfg_node*, set<path>*);

    /**
     * \brief  This function finds the bath between the root of the tree
     *         and the given node
     * \param  node the node for which we have to find the path
     * \return the set of all the paths between the root and the node
     */
    set<path>* find_path (arm_cfg_node*);

    /**
     * \brief   This function finds the father of a node using the fact that it has
     *          to be in every paths between the node and the root
     * \details This function is used to construct the dominance tree
     * \param   node the node for which we have to find the father
     * \return  the node that is the father of the param node
     */
    arm_cfg_node* find_father (arm_cfg_node*);

    /**
     * \brief This function finds the successors of all the nods
     *        of the control flow graph
     * \param node the root of the control flow graph
     */
    void get_succs (arm_cfg_node*);
    set<succ> succs;                            /*!< The set of succs for every nodes         */
    set<arm_cfg_node*> already_visited;         /*!< The set of nodes that has been visited   */
    arm_cfg_node* cfg_root;                     /*!< the root of the control flow graph       */
    arm_dom_node* dom_root;                     /*!< the root of the dominance graph          */
    map<arm_cfg_node*, arm_dom_node*> node_eq;  /*!< the map that binds a node of the control
                                                  flow graph to a node of the dominance graph */
  };

}

#endif//__ARM_DOM_NODE_FACTORY_H__
