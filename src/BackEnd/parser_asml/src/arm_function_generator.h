/**
 * \file      arm_function_generator.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Generator of functions in ARM
 *
 */

#ifndef __ARM_FUNCTION_GENERATOR_H__
#define __ARM_FUNCTION_GENERATOR_H__

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>

#include "arm_instruction_factory.h"
#include "asml_function.h"
#include "arm_instruction.h"
#include "asml_integer.h"
#include "asml_funcall.h"
#include "arm_funcall.h"
#include "arm_function.h"

using namespace std;
using namespace asml;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_function_generator
   * \brief Function generator Object
   */
  class arm_function_generator {
    friend class arm_function;
  public:
    /**
     *  \brief Constructor of the class arm_function_generator
     *
     */
    arm_function_generator (asml_function*);
    /**
     *  \brief Destructor of the class arm_function_generator
     *
     */
    ~arm_function_generator (void);

    /*!
     *  \brief Generator of function
     *	\return TODO
     */

    stringstream* generate (void);
    string get_name (void);
    vector<arm_instruction*>* get_instructions (void) const;
  protected:
    /*!
     *  \brief Generator of function
     */
    void generate_function (void); 
    /*!
     *  \brief TODO
     */
    void pre_process_params (void);
    /*!
     *  \brief TODO
     */
    void process_params (void);
    /*!
     *  \brief TODO
     */
    void pre_process_variables (void);
    /*!
     *  \brief TODO
     */
    void process_instructions (void);
    /*!
     *  \brief TODO
     */
    void pre_process_conditions (void);
    /*!
     *  \brief TODO
     */
    void generate_prologue (void);
    /*!
     *  \brief TODO
     */
    void generate_epilogue (void);
    stringstream* output; /*!<    TODO         */
    asml_function* asml; /*!<    asml definition of function */
    int nb_params; /*!<          number of parameters   */
    int nb_variables; /*!<        number of variables     */
    int sp_offset; /*!<    offset of stack pointer         */
    int fp_offset; /*!<    offset of frame pointer         */
    string prologue; /*!<     prologue name        */
    string epilogue; /*!<     epilogue name        */
    string processed_params; /*!<      processed parameters       */
    string processed_variables; /*!<    processed variables         */
    string to_save; /*!<    TODO         */
    static int lien; /*!<     TODO        */

    string name; /*!<     function name        */
    mutable vector<arm_instruction*> instructions; /*!<     vector of instruction        */
    map<string, string> var_offsets; /*!<  map of variable offsets           */
  };

} // TODO

#endif //__ARM_FUNCTION_GENERATOR_H__
