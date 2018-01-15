#include <string>
#include <map>
#include <vector>
#include <sstream>

#ifndef __ARM_CONDITION_H__
#define __ARM_CONDITION_H__

#include "arm_instruction.h"
#include "arm_boolean.h"
/**
 * \file      arm_condition.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Condition function implementation in ARM
 *
 */
using namespace std;

namespace arm {
/*! \class arm_condition
 * \brief Condition instruction Object
 */
  class arm_condition : public arm_instruction {
  public:
    /*!
     *  \brief Constructor of the class arm_condition
     *
     */
    arm_condition (void);
    /*!
     *  \brief Destructor of the class arm_condition
     *
     */
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
     *  \brief Number of Register
     *
     *  Return the number of registers
     *  \return int of register
     */
    virtual int nb_regs (void);
    /*!
     * \brief Getter of operands
     * Return the list of operands
     * \return list of string of operands
     */
    virtual list<string>* get_op_list (void);
  protected:
    string var; /*!< var name             */
    arm_boolean* boolean; /*!< TODO              */
    vector<arm_instruction*>* list_then; /*!< list of then instruction              */
    vector<arm_instruction*>* list_else; /*!< list of else instruction              */
    string lFalse; /*!< label to go to false              */
    string lFin; /*!< label to go to the end              */
  };

}

#endif //__ARM_CONDITION_H__
