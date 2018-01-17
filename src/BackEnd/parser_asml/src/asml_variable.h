/**
 * \file      asml_variable.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Class that represent a variable in ASML
 */

#ifndef __ASML_VARIABLE_H__
#define __ASML_VARIABLE_H__

#include <string>

using namespace std;
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {
  /*! \class   asml_variable
   *  \brief   a variable for asml generation
   */
  class asml_variable {
    friend class asml_factory;
  public:
    static const int INTEGER = 1; /*!< The identifier for integer variables */

    virtual ~asml_variable (void) {};

    virtual void set_name (string);

    virtual int get_type(void);
    virtual string get_name (void) const;
  protected:
    int type_id; /*!< The type of the variable */
    string name; /*!< The name of the variable */
  };

}

#endif //__ASML_VARIABLE_H__
