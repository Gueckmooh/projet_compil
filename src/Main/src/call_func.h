#ifndef __CALL_FUNC_H__
#define __CALL_FUNC_H__
/*!
 * \file call_func.h
 * \brief Caller of various configuration functions
 * \author THE C TEAM - Florian MARCO
 * \version 1.0
 * \date 17 Janvier 2018
 * \details Main program that calls all the different functions of our compiler, MinCaml Parsing, Typchecking, ASML generation and optimisation, ARM generation...
 */
#include "param.h"
#include "asml.h"
#include "arm.h"
extern "C" {
#include "alpha_conv.h"
#include "ast.h"
#include "ast_to_asmlt.h"
#include "env.h"
#include "knorm.h"
#include "list.h"
#include "front_end.h"
#include "print_and_write.h"
#include "reduce_nested_let.h"
#include "type.h"
#include "utils.h"
}

#include <string>
#include <iostream>
#include <cstdarg>
using namespace std;
using namespace asml;
using namespace arm;


/*!
 *  \brief This function take an ASML file, parse it, and generate an ARM output.
 *
 *  
 *	\param string input : The ASML input file
 *	\param string output : The ASML output file
 */
void ASML_PARSER (string, string);

/*!
 *  \brief This function calls all compilation function
 *  
 *	\param int param : List of active parameters
 *	\param string input : The input files
 *	\param string output : The output files
 *	\return 0 if everything goes well, 1 if there is an error
 */
int mega_caller (int, std::string, string);

#endif //__CALL_FUNC_H__
