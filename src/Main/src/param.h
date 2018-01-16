/**
 * \file      param.h
 * \author    The C Team - Florian MARCO
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     smart parameter enabler/disabler 
 *
 */
/*!
  \def PARAM_PARSE
  \brief MinCaml parsing
*/
#define PARAM_PARSE     0b0001<<0
/*!
  \def PARAM_TYPECHECK
  \brief MinCaml typechecking
*/
#define PARAM_TYPECHECK 0b0010<<0
/*!
  \def PARAM_ASML
  \brief ASML generation
*/
#define PARAM_ASML      0b0100<<0
/*!
  \def PARAM_ARM
  \brief ARM generation
*/
#define PARAM_ARM       0b1000<<0
/*!
  \def PARAM_OUTPUT
  \brief Output generation
*/
#define PARAM_OUTPUT 	0b0001<<4
/*!
  \def PARAM_ASMLI
  \brief ASML input and ARM generation
*/
#define PARAM_ASMLI 	0b0010<<4
/*!
  \def PARAM_DEBUG
  \brief Debug mode
*/
#define PARAM_DEBUG   0b0100<<4
/*!
  \def TOTAL_PARSE
  \brief Enable all parameters for parsing
*/
#define TOTAL_PARSE 0b00001
/*!
  \def TOTAL_TYPECHECK
  \brief Enable all parameters for typechecking
*/
#define TOTAL_TYPECHECK 0b00011
/*!
  \def TOTAL_ASML
  \brief Enable all parameters for ASML generation
*/
#define TOTAL_ASML 0b00111
/*!
  \def TOTAL_ARM
  \brief Enable all parameters for ARM generation
*/
#define TOTAL_ARM 0b01111

/*!
  \def enable(param, type)
  \brief Enable type inside param
*/
#define enable(param, type) do {param|=type;} while (0)
/*!
  \def disable(param, type)
  \brief Disable type inside param
*/
#define disable(param, type) do {param&=~type;} while(0)
/*!
  \def is_enabled(param, type)
  \brief Check if type is enabled inside param
*/
#define is_enabled(param, type) param&type
