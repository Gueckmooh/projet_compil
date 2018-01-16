/**
 * \file      asml_generator.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_generator class
 */
#include <map>
#include <vector>
#include <string>
#include <fstream>

#ifndef __ASML_GENERATOR_H__
#define __ASML_GENERATOR_H__

#include "asml_function.h"
#include "asml_funcall.h"
#include "asml_affectation.h"
#include "asml_addition.h"
#include "asml_soustraction.h"
#include "asml_condition.h"
#include "asml_negation.h"

using namespace std;
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {
  /*! \class   asml_generator
   *  \brief   class that generate ASML 
   *  \details TODO
   */
  class asml_generator {
  public:
    asml_generator(vector<asml_function*>*);
    ~asml_generator(void);
    void set_name (string);
    /**
     * \brief    TODO
     * \details  TODO
     */
    void generate (void);
  protected:
    /**
     * \brief    TODO
     * \details  TODO
     */
    void generate_function (void);
    ofstream* output; /*! filestream of output */
    string filename; /*! output filename */
    int nb_params; /*! number of parameters */
    int nb_variables; /*! number of variables */
    int sp_offset; /*! offset of stackpointer */
    int fp_offset; /*! offset of framepointer */
    bool do_save_sp; /*! boolean to check if we save the stack pointer */
    string prologue; /*! prologue name */
    string epilogue; /*! epilogue name */
    string processed_params; /*! processed parameters */
    string processed_variables; /*! processed variables */
    string to_save; /*! TODO */

    string name; /*! name of TODO */
    vector<asml_function*>* functions; /*!  vector of different functions */
    map<string, string> var_offsets;  /*! variables offset */
  };

} 


#endif //__ASML_GENERATOR_H__
