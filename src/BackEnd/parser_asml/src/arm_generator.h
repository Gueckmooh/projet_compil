#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#ifndef __ARM_GENERATOR_H__
#define __ARM_GENERATOR_H__

#include "arm_instruction_factory.h"
#include "arm_function_generator.h"
#include "asml_function.h"
#include "arm_instruction.h"
#include "asml_integer.h"
#include "asml_funcall.h"
#include "arm_funcall.h"
#include "arm_cfg_node.h"
#include "arm_cfg_util.h"
#include "arm_cfg_factory.h"
/**
 * \file      arm_generator.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     ARM Generator implementation
 *
 */
using namespace std;
using namespace asml;

namespace arm {
/*! \class arm_generator
 * \brief Generator of ARM
 */
  class arm_generator {
  public:
    /*!
     *  \brief Constructor of the class arm_generator
     *	\param Vector of ASML function
     */
    arm_generator(vector<asml_function*>*);
    /*!
     *  \brief Destructor of the class arm_generator
     *
     */
    ~arm_generator(void);
    void set_name (string);
    /*!
     *  \brief Generator TODO
     *
     */
    void generate (void);
  protected:
    /*!
     *  \brief function generator
     *
     */
    void generate_function (void);
    ofstream* output; /*!<   output file          */
    vector<asml_function*>* asml; /*!<     list of asml function        */
    string filename; /*!<    name of output file  */
    int nb_params; /*!<     parameters number        */
    int nb_variables; /*!<       variable number      */
    int sp_offset; /*!<     stack pointer offset        */
    int fp_offset; /*!<      frame pointer offset       */
    bool do_save_sp;    /*!<     boolean checking if we need to save or not stack pointer        */
    string prologue; /*!<    prologue name         */
    string epilogue; /*!<     epilogue name        */
    string processed_params; /*!<  parameter processed         */
    string processed_variables; /*!<  variables processed        */
    string to_save; /*!<    TODO         */

    string name; /*!<    name of the function       */
    vector<arm_function_generator*> generators; /*!<     vector of generators       */
    vector<arm_instruction*> instructions; /*!<     vecot of  instructions      */
    map<string, string> var_offsets; /*!<     offset map        */
  };

} // TODO

#endif //__ARM_GENERATOR_H__
