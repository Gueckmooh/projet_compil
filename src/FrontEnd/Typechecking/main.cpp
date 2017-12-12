/* 
 * File:   main.cpp
 * Author: bleuzeb
 *
 * Created on 12 décembre 2017, 12:51
 */

#include "Ast.h"
#include <stdlib.h>
#include <iostream>
/*
 * 
 */
int main(int argc, char** argv) {
    Ast ast ;
    try {
	ast = Ast("../../pc-archive/mincaml/even-odd.ml") ;
    } catch (std::string const & message) {
	std::cout << message ;
	return EXIT_FAILURE ;
    }
    ast.print() ;
    return EXIT_SUCCESS ;
}

