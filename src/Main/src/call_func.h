#ifndef __CALL_FUNC_H__
#define __CALL_FUNC_H__

#include "param.h"
#include "asml.h"
#include "arm.h"
#include "type_caller.h"
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

// Cette fonction prends en parametre, le fichier d'entree
// Cette fonction renvois la structure.

int parser_caller (int);

// Cette fonction prends en parametre la structure parsee
// Cette fonction print dans un fichier l'arbre.
int parser_printer (int);

// Cette fonction prends en paramètre la structure
// Cette fonction renvois 0 si tout se passe bien
// Cette fonction renvoit 1 et affiche un message d'erreur en cas de probleme.
int typecheck_caller (int);

// Cette fonction prends en parametre la structure
// Cette fonction renvoit la structure front-endee
int ASML_caller (int);

//Cette fonction prends en parametre la structure front-endee
// Cette fonction print dans un fichier l'ASML genere.
int ASML_PRINTER (int);

//Cette fonction prends en parametre un fichier ASML
//Cette fonction genere de l'ARM dans un fichier output.s
void ASML_PARSER (string, string);

// Cette fonction prends en parametre la structure front-endee
// Cette fonction print dans un fichier l'ARM genere.
int ARM_caller (int);

int mega_caller (int, std::string, string);

#endif //__CALL_FUNC_H__
