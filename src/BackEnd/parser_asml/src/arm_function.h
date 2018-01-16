/**
 * \file      arm_function.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Function management implementation in ARM
 */

#ifndef __ARM_FUNCTION_H__
#define __ARM_FUNCTION_H__

#include <string>
#include <map>
#include <list>
#include <cassert>

#include "arm_function_generator.h"

using namespace std;

/*! \namespace arm
 *  \brief     Contains the classes that manages the arm generation
 */
namespace arm {

  /*! \class arm_function
   * \brief function Object
   */
  class arm_function {
    friend class arm_function_generator;
  public:

    /**
     * \brief   Initializes the object (static)
     * \details This fucntion must be called before any call to this class
     */
    static void initialize (void);

    static void set_processed_function (string);

    /**
     * \brief  This function generate the code for the references to function address
     * \return the ARM code that correspond to the references
     */
    static string process_refs (void);

    /**
     *  \brief  This function adds returns a label, increment the link and maps it
     *          to name
     *  \param  name the name that will be mapped to the label
     *  \return string the generated label
     */
    static string add_ref (string);
  protected:
    static list<string>* funcnames_list; /*!< list of function names  */
    static string processed_function;    /*!< processed function      */
    static map<string, string>* ref_map; /*!< map of references       */
  };

}

#endif // __ARM_FUNCTION_H__
