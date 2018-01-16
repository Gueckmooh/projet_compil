/**
 * \file      env.h
 * \author    The C Team - Maxime Raynal
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     contains the definitions of an environnement and useful functions
 *
 * \details
 */
#ifndef ENV_H
#define ENV_H

#include "list.h"

#include <stdbool.h>

/**
 * \struct str_to_str
 * \brief     contains a couple of strings
 * \details
 */
typedef struct {
    char *src, *dest;
} str_to_str;

/**
 * \struct    env_node
 * \brief     stack structure used as a variable environnement
 * \details
 */
typedef struct env_node_t{
    char *src, *dest;            /*!< src -> original name ; dest -> new_name*/
    int value;                   /*!< integer value for constant folding */
    struct env_node_t *next;     /*!< next node in the stack */
} env_node;

/**
 * \brief     applies epsilon(x) by calling epsilon_rec
 * \details   cf mincaml compiler paper
 * \param     env : the variable environnement, x the value to transform
 * \return    the result of epsilon(x)
 */
char *epsilon(env_node *env, char *x);

/**
 * \brief     applies epsilon(x) until a fix point is reached
 * \details
 * \param     env : the variable environnement, x the value to transform
 * \return    the result of epsilon(x)
 */
char *epsilon_rec(env_node *env, char *x);

/**
 * \brief     checks if var_name is in environnement env
 * \details   checks if var_name is the src field of a node of the stack
 * \param     env : the variable environnement, var_name the variable to check presence
 * \return    true if var_name is in env
 */
bool is_in_env(env_node *env, char *var_name);

/**
 * \brief     adds a new node to the stack on top
 * \details   creates a new stack if next is NULL
 * \param     src, dest : fields to fill ; next : the stack to add the node to
 * \return    the resulting stack
 */
env_node *gen_env_node(char *src, char *dest, env_node *next);

/**
 * \brief     adds a new node to the stack on top
 * \details   creates a new stack if next is NULL
 * \param     src, value : fields to fill ; next : the stack to add the node to
 * \return    the resulting stack
 */
env_node *gen_env_node_int(char *var_name, int value, env_node *next);

/**
 * \brief     gets the value of a variable in the environnement
 * \details   returns 0 if the value is not present in the environnement
 * \param     var_name : the variable name ; env : the environnement
 * \return    the value of the variable
 */
int get_value(char *var_name, env_node *env);
#endif
