/**
 * \file      asml_node.h
 * \author    The C Team - Enzo Brignon
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Defines the asml_node class
 */

#ifndef __ASML_NODE_H__
#define __ASML_NODE_H__

using namespace std;
/*! \namespace asml
 *  \brief     Contains the classes that manages the asml
 */
namespace asml {
  /*! \class   asml_node
   *  \brief   class that represent an asml node
   *  \details TODO
   */
  class asml_node {
  public:
    static const int UNARY = 1; /*! Typedefinition of an Unary node */
    static const int BINARY = 2; /*! Typedefinition of a Binary node */

    virtual ~asml_node (void) {};
    virtual int get_type (void);
  protected:
    int type_id; /*! Type of the node */
  };

} 

#endif //__ASML_NODE_H__
