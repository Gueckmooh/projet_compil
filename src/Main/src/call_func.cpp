#include "call_func.h"
#include "front_end.h"


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
  ptree p = (ptree)malloc(sizeof(ptree));
  asml_function_t *t=NULL;
  /*if (is_enabled(param,PARAM_OUTPUT)){
    cout << "OUTPUT OK";
  }*/
  if (is_enabled(param,PARAM_PARSE)){

	 parsecall(&p,const_cast<char*>(input.c_str()));
    //std::cout << "PARSE OK \n";
    if (!(is_enabled(param,PARAM_TYPECHECK)) && !(is_enabled(param,PARAM_ASMLI))){
      std::cout << "Not Implemented : On ne genere pas de fichier, mais on print l'arbre \n";
      parseprint(p,const_cast<char*>(output.c_str()));
    }
  }

  if (is_enabled(param, PARAM_TYPECHECK)){
    std::cout << "ON FAIT LE TYPECHECK \n";
    std::cout << "Retour du typecheck est de :" << init_tc(p) << "\n";
  }
asml::asml_factory::initialize();
  if (is_enabled(param, PARAM_ASML)){
    ptree p2 = ast_transform(p);
    t=build_asml_from_ptree(p2);
    if (!(is_enabled(param,PARAM_ARM))){
      parseprint(p2,const_cast<char*>(output.c_str()));

      asml_parser_create_function(t);
      vector <asml_function*>*vect = asml_factory::get_function();
      asml_generator* generator = new asml_generator(vect);
      generator->set_name(output);
      generator->generate();
    }
  }

  if(is_enabled(param,PARAM_ASMLI)){
  	//std::cout << "ON PASSE DU ASML INPUT AU ARM \n";
  	ASML_PARSER(input,output);
  }

  if (is_enabled(param,PARAM_ARM)){
    asml_parser_create_function(t);
    vector <asml_function*>*vect = asml_factory::get_function();
    arm_generator* generator = new arm_generator(vect);
    generator->set_name(output);
    generator->generate();
  }
  return 0;
}
