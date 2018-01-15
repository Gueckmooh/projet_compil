/**
 * \file      arm_boolean.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Boolean implementation in ARM
 */

#ifndef __ARM_BOOLEAN_H__
#define __ARM_BOOLEAN_H__

#include <string>
#include <map>
#include <list>

#include "arm_util.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_boolean
   *  \brief Boolean instruction Object
   */
  class arm_boolean {
    friend class arm_condition;
  public:
    static const int CONJONCTION = 1; /*!< Conjonction      */
    static const int DISJONCTION = 2; /*!< Disjonction      */
    static const int LT = 3;          /*!< Less Than        */
    static const int GT = 4;          /*!< Greater Than     */
    static const int LE = 5;          /*!< Less or Equal    */
    static const int GE = 6;          /*!< Greater or Equal */
    static const int EQUAL = 7;       /*!< Equal            */
    static const int NEQUAL = 8;      /*!< Not Equal        */

    arm_boolean (int);
    virtual ~arm_boolean (void) {};

    virtual string get_instruction (void);

    virtual void set_op1 (string);
    virtual void set_op2 (string);
    virtual void set_lFalse (string);

    virtual string get_op1 (void);
    virtual string get_op2 (void);

    virtual int get_type (void);

    /*!
     *  \brief Gives the number of registers used in this instruction
     *  \return an int, the number of register
     */
    virtual int nb_regs (void);

    /*!
     * \brief  This function gives the list of operands of this instruction
     * \return list of string of operands
     */
    virtual list<string>* get_op_list (void);
  protected:
    map<string, string>* offset; /*!< offset                 */
    string lFalse;               /*!< Label of te else part  */
    int type_id;                 /*!< type of the comparison */
    string cmp;                  /*!< Comparator             */
    string op1;                  /*!< first operand          */
    string op2;                  /*!< second operand         */
  };

}

#endif //__ARM_BOOLEAN_H__
