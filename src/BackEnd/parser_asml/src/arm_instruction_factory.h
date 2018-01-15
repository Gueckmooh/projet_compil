#include <iostream>
#include <string>
#include <map>
#include <vector>

#ifndef __ARM_INSTRUCTION_FACTORY_H__
#define __ARM_INSTRUCTION_FACTORY_H__

#include "asml_instruction.h"
#include "asml_funcall.h"
#include "asml_affectation.h"
#include "asml_addition.h"
#include "asml_soustraction.h"
#include "asml_condition.h"
#include "asml_negation.h"
#include "asml_mem_create.h"
#include "asml_mem_read.h"
#include "asml_mem_write.h"
#include "asml_closure.h"
#include "arm_instruction.h"
#include "arm_funcall.h"
#include "arm_affectation.h"
#include "arm_addition.h"
#include "arm_soustraction.h"
#include "arm_condition.h"
#include "arm_negation.h"
#include "arm_mem_create.h"
#include "arm_mem_read.h"
#include "arm_mem_write.h"
#include "arm_closure.h"

using namespace std;
using namespace asml;
/**
 * \file      arm_instruction_factory.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Factory of ARM Instructions
 *
 */
namespace arm {
/*! \class arm_instruction_factory
 * \brief Factory of Instruction objects
 */
  class arm_instruction_factory {
  public:
    /*!
     *  \brief Factory of arm_instruction
     *	\param asml_instruction
     *  \return arm instruction
     */
    static arm_instruction* create_instruction (asml_instruction*);
  protected:
    /*!
     *  \brief Factory of arm funcall
     *	\param asml_funcall
     *  \return arm funcall
     */
    static arm_funcall* create_funcall (asml_funcall*);
    /*!
     *  \brief Factory of arm affectation
     *	\param asml_affectation
     *  \return arm affectation
     */
    static arm_affectation* create_affectation (asml_affectation*);
    /*!
     *  \brief Factory of arm addition
     *	\param asml_addition
     *  \return arm addition
     */
    static arm_addition* create_addition (asml_addition*);
    /*!
     *  \brief Factory of arm substraction
     *	\param asml_soustraction
     *  \return arm soustraction
     */
    static arm_soustraction* create_soustraction (asml_soustraction*);
    /*!
     *  \brief Factory of arm condition
     *	\param asml_condition
     *  \return arm condition
     */
    static arm_condition* create_condition (asml_condition*);
    /*!
     *  \brief Factory of arm negation
     *	\param asml_negation
     *  \return arm negation
     */
    static arm_negation* create_negation (asml_negation*);
    /*!
     *  \brief Factory of arm memory creation
     *	\param asml_mem_create
     *  \return arm mem_create
     */
    static arm_mem_create* create_mem_create (asml_mem_create*);
    /*!
     *  \brief Factory of arm memory reading
     *	\param asml_mem_read
     *  \return arm mem_read
     */
    static arm_mem_read* create_mem_read (asml_mem_read*);
    /*!
     *  \brief Factory of ARM memory writing
     *	\param asml_mem_write
     *  \return arm mem_write
     */
    static arm_mem_write* create_mem_write (asml_mem_write*);
    /*!
     *  \brief Factory of arm closure
     *	\param asml_closure
     *  \return arm closure
     */
    static arm_closure* create_closure (asml_closure*);
  };

}

#endif //__ARM_INSTRUCTION_FACTORY_H__
