#include "call_func.h"
#include "front_end.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <vector>

extern "C" int caller_de_merde (const char* input);

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

int dirtypecheck (string input) {
	caller_de_merde(input.c_str());
	return 0;
}

/*
int dirtypecheck (string input) {
  pid_t pid = fork();
  std::vector<const char*> 
  if (pid == -1){
    std::cerr << "Erreur appel fork typecheck \n";;
    return 1;	
  }
  else{
    if (pid == 0) {
      execv("ls", args);
    } else {
      waitpid(pid, NULL, 0);
    }
  }
  return 0;
}*/

int mega_caller (int param, string input, string output){
  int retour = 0;
  int ret2 = 0;
  ptree p = (ptree)malloc(sizeof(ptree));
  asml_function_t *t=NULL;
  /*if (is_enabled(param,PARAM_OUTPUT)){
    cout << "OUTPUT OK";
  }*/
  if (is_enabled(param,PARAM_PARSE)){

	 parsecall(&p,const_cast<char*>(input.c_str()));
  }

  if (is_enabled(param, PARAM_TYPECHECK)){
    /*if (is_enabled(param,PARAM_DEBUG)){
      retour=init_tc_debug(b4_tc(p));
    }
    else {
    retour= init_tc(b4_tc(p)) ;}*/
	ret2 = dirtypecheck(input);
	if (ret2 != 0){
		return(ret2);
	} 
  }
asml::asml_factory::initialize();
  if (is_enabled(param, PARAM_ASML)){
    ptree p2 = ast_transform(p);
    t=build_asml_from_ptree(p2);
    if (!(is_enabled(param,PARAM_ARM))){
      //parseprint(p2,const_cast<char*>(output.c_str()));

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
  return retour;
}
