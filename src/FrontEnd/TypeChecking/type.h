/**
 * \file      type.h
 * \author    The C Team - Baptiste
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Type definition of a ptree
 *
 */

#ifndef __TYPE_H
#define __TYPE_H

enum TCode {
    TY_UNDEFINED,
    TY_UNIT,
    TY_BOOL,
    TY_INT,
    TY_FLOAT,
    TY_FUN,
    TY_TUPLE,
    TY_ARRAY,
    TY_VAR
};

typedef struct {
    enum TCode code;
    union {
      char *var;
     // TODO
    } params;
} type;

typedef type *ptype;

ptype gentvar();

ptype copy_type(ptype original_type);
#endif
