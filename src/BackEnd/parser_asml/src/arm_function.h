#include <string>
#include <map>
#include <list>
#include <cassert>

#ifndef __ARM_FUNCTION_H__
#define __ARM_FUNCTION_H__

#include "arm_function_generator.h"
/**
 * \file      arm_function.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Function management implementation in ARM
 *
 */
using namespace std;

namespace arm {
/*! \class arm_function
 * \brief function Object
 */
  class arm_function {
    friend class arm_function_generator;
  public:
    /*!
     *  \brief TODO
     *
     */
    static void initialize (void);
    static void set_processed_function (string);
    /*!
     *  \brief TODO
     *  \return string
     *
     */
    static string process_refs (void);
    /*!
     *  \brief TODO
     *  \param string name
     *  \return string 
     *
     */
    static string add_ref (string);
  protected:
    static list<string>* funcnames_list; /*!< list of function names              */
    static string processed_function; /*!< processed function             */
    static map<string, string>* ref_map; /*!< map of references             */
  };

} // TODO

#endif // __ARM_FUNCTION_H__
