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
     * \brief Constructor of the class arm_function_generator
     * \param fun the function to generate in ARM
     */
    arm_function_generator (asml_function*);
    ~arm_function_generator (void);

    /**
     *  \brief  Generator of function
     *	\return a stringstream that contains the generated arm function
     */
    stringstream* generate (void);
    string get_name (void);
    vector<arm_instruction*>* get_instructions (void) const;
  protected:
    /**
     *  \brief Generator of function
     */
    void generate_function (void);

    /**
     *  \brief This function set the place to reserve in the stack for the parameters
     */
    void pre_process_params (void);

    /**
     *  \brief This function generate the ARM code that pushes the parameters on
     *         the stack
     */
    void process_params (void);

    /**
     *  \brief This function set the place to reserve in the stack for the variables
     */
    void pre_process_variables (void);

    /**
     *  \brief This function generate the ARM code that pushes the variables on
     *         the stack
     */
    void process_instructions (void);

    /**
     *  \brief This function generates the ARM code that correspond to the
     *         instructions in the function
     */
    void pre_process_conditions (void);

    /**
     *  \brief This function generates the ARM code that correspond to
     *         the prologue of the function
     */
    void generate_prologue (void);

    /**
     *  \brief This function generates the ARM code that correspond to
     *         the epilogue of the function
     */
    void generate_epilogue (void);

    stringstream* output;        /*!< The stringstrea that will be returned  */
    asml_function* asml;         /*!< asml definition of function            */
    int nb_params;               /*!< number of parameters                   */
    int nb_variables;            /*!< number of variables                    */
    int sp_offset;               /*!< offset of stack pointer                */
    int fp_offset;               /*!< offset of frame pointer                */
    string prologue;             /*!< prologue name                          */
    string epilogue;             /*!< epilogue name                          */
    string processed_params;     /*!< processed parameters                   */
    string processed_variables;  /*!< processed variables                    */
    string to_save;              /*!< The list of variables to save          */
    static int lien;             /*!< The index of the labels                */
    string name;                 /*!<     function name        */
    mutable vector<arm_instruction*> instructions; /*!< ector of instruction */
    map<string, string> var_offsets; /*!< map of variable offsets            */
  };

}

#endif //__ARM_FUNCTION_GENERATOR_H__
