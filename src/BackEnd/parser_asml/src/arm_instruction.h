#include <string>
#include <map>
#include <vector>
#include <list>
#include <functional>

#ifndef __ARM_INSTRUCION_H__
#define __ARM_INSTRUCION_H__

#include "arm_util.h"
/**
 * \file      arm_instruction.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Instruction implementation
 *
 */
namespace arm {
/*! \class arm_instruction
 * \brief ARM instruction Object
 */
  class arm_instruction {
  public:
    static const int FUNCALL = 1; /*!<    Function call         */
    static const int AFFECTATION = 2; /*!<   Variable Affectation          */
    static const int ADDITION = 3; /*!<    Addition         */
    static const int SOUSTRACTION = 4; /*!<     Substraction        */
    static const int CONDITION = 5; /*!<      condition        */
    static const int NEGATION = 6; /*!<        Not     */
    static const int MEM_CREATE = 7; /*!<    Memory creation         */
    static const int MEM_WRITE = 8; /*!<      Memory writing       */
    static const int MEM_READ = 9; /*!<      Memory reading       */
    static const int CLOSURE = 10; /*!<      Closure       */
   /*!
     *  \brief Destructor of the class arm_instruction
     *
     */
    virtual ~arm_instruction (void) {};

    int get_type (void);
    /*!
     *  \brief Number of Register
     *
     *  Return the number of registers
     *  \return int of register
     */
    virtual int nb_regs (void) = 0;
    /*!
     * \brief Getter of operands
     * Return the list of operands
     * \return list of string of operands
     */
    virtual list<string>* get_op_list (void) = 0;
    /*!
     * \brief Getter of instructions
     * Return the instruction 
     * \return string of instruction
     */
    virtual string get_instruction (void) = 0;

    virtual void set_var_offset (map<string, string>*);
    /*!
     * \brief Parameter adder
     * \param string name of parameter
     */
    void add_param (string);
    void set_callback (function<map<string, string>(void)>);
    vector<string> get_used (void);
  protected:
    int type_id; /*!<      Id of type of insutrction       */
    function<map<string, string>(void)> callback; /*!<        TODO     */
    map<string, string>* offset; /*!<        map of offsets     */
    vector<string> params; /*!<   vector of parameters          */
  };

}

#endif //__ARM_INSTRUCION_H__
