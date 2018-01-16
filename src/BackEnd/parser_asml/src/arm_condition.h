/**
 * \file      arm_condition.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Condition function implementation in ARM
 */

#ifndef __ARM_CONDITION_H__
#define __ARM_CONDITION_H__

#include <string>
#include <map>
#include <vector>
#include <sstream>

#include "arm_instruction.h"
#include "arm_boolean.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_condition
   *  \brief Condition instruction Object
   */
  class arm_condition : public arm_instruction {
  public:
    arm_condition (void);
    virtual ~arm_condition (void);

    virtual string get_instruction (void);

    virtual void set_var (string);
    virtual void add_then (arm_instruction*);
    virtual void add_else (arm_instruction*);
    virtual void set_boolean (arm_boolean*);
    virtual void set_lFalse (string);
    virtual void set_lFin (string);
    virtual void set_var_offset (map<string, string>*);

    virtual vector<arm_instruction*>* get_list_then (void);
    virtual vector<arm_instruction*>* get_list_else (void);

    /*!
     *  \brief This function returns the number of regsters used in this instruction
     *  \return an int, the number of registers that are used in this instruction
     */
    virtual int nb_regs (void);

    /*!
     * \brief  This function returns a list of the operands used in this instruction
     * \return list of string of operands
     */
    virtual list<string>* get_op_list (void);
  protected:
    string var;                          /*!< var name                 */
    arm_boolean* boolean;                /*!< the conditional statement corresponding
                                           to the condition            */
    vector<arm_instruction*>* list_then; /*!< list of then instruction */
    vector<arm_instruction*>* list_else; /*!< list of else instruction */
    string lFalse;                       /*!< label to go to false     */
    string lFin;                         /*!< label to go to the end   */
  };

}

#endif //__ARM_CONDITION_H__
