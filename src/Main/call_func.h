#ifndef __CALL_FUNC_H__
#define __CALL_FUNC_H__

#include "param.h"
#include <string>
#include <iostream>
#include <cstdarg>
using namespace std;
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

// Cette fonction prends en parametre la structure front-endee
// Cette fonction print dans un fichier l'ARM genere. 
int ARM_caller (int);

int mega_caller (int, std::string, ...);

#endif //__CALL_FUNC_H__