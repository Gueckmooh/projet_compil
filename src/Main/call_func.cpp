#include "call_func.h"

// Cette fonction prends en parametre, le fichier d'entree
// Cette fonction renvois la structure.

int parser_caller (int zboub){
	return 0;
}

// Cette fonction prends en parametre la structure parsee
// Cette fonction print dans un fichier l'arbre.
int parser_printer (int zboub){
	return 0;
}

// Cette fonction prends en paramètre la structure
// Cette fonction renvois 0 si tout se passe bien
// Cette fonction renvoit 1 et affiche un message d'erreur en cas de probleme.
int typecheck_caller (int zboub){
	return 0;
}

// Cette fonction prends en parametre la structure
// Cette fonction renvoit la structure front-endee
int ASML_caller (int zboub){
	return 0;
}	

//Cette fonction prends en parametre la structure front-endee
// Cette fonction print dans un fichier l'ASML genere.
int ASML_PRINTER (int zboub){
	return 0;
}

// Cette fonction prends en parametre la structure front-endee
// Cette fonction print dans un fichier l'ARM genere. 
int ARM_caller (int zboub){
	return 0;
}

int mega_caller (int param, string input ...){
	string output;
	va_list args;
	va_start(args, input);
	if (is_enabled(param,PARAM_OUTPUT)){
		output = va_arg(args, string);
		cout << "ALORS";
		std::cout << output;
		std::cout << "ENZO COUCOUCOUCOUCOU";
	}
	if (is_enabled(param,PARAM_PARSE)){
		std::cout << "COUCOU ENZO \n";
		if (!is_enabled(param,PARAM_TYPECHECK)){
			std::cout << "ON PRINT LE PARSE \n";
		}
	}

	if (is_enabled(param, PARAM_TYPECHECK)){
		std::cout << "COUCOU COUCOU \n";

	}

	if (is_enabled(param, PARAM_ASML)){
		std::cout << "coucou ASML \n";
		if (!is_enabled(param,PARAM_ARM)){
			std::cout << "ON PRINT LE ASML \n";
		}
	}

	if (is_enabled(param,PARAM_ARM)){
		std::cout << "COUCOU ARM\n";
	}

}