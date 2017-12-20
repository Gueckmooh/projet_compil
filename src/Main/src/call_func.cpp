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

//Cette fonction prends en parametre un fichier ASML
//Cette fonction genere de l'ARM dans un fichier output.s
void ASML_PARSER (string i, string s){
	extern FILE* asml_in;
	arm::arm_generator* generator;
	asml::asml_factory::initialize();
	asml_in = fopen (i.c_str(), "r");
	asml_parse();
	generator = new arm::arm_generator(asml::asml_factory::get_function());
	generator->set_name(s);
	generator->generate();
	fclose (asml_in);
	delete generator;
}


// Cette fonction prends en parametre la structure front-endee
// Cette fonction print dans un fichier l'ARM genere. 
int ARM_caller (int zboub){
  return 0;
}

int mega_caller (int param, string input, string output){

  if (is_enabled(param,PARAM_OUTPUT)){
    cout << "ALORS";
    std::cout << output;
    std::cout << "ENZO COUCOUCOUCOUCOU";
  }
  if (is_enabled(param,PARAM_PARSE)){
    std::cout << "COUCOU ENZO \n";
    if (!(is_enabled(param,PARAM_TYPECHECK)) && !(is_enabled(param,PARAM_ASMLI))){
      std::cout << "ON PRINT LE PARSE \n";
    }
  }

  if (is_enabled(param, PARAM_TYPECHECK)){
    std::cout << "COUCOU COUCOU \n";

  }

  if (is_enabled(param, PARAM_ASML)){
    std::cout << "coucou ASML \n";
    if (!(is_enabled(param,PARAM_ARM))){
      std::cout << "ON PRINT LE ASML \n";
    }
  }

  if(is_enabled(param,PARAM_ASMLI)){
  	std::cout << "COUCOU ASMLI TO ARM \n";
  	ASML_PARSER(input,output);
  }

  if (is_enabled(param,PARAM_ARM)){
    std::cout << "COUCOU ARM\n";
  }
  return 0;
}
