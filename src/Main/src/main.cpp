/**
 * \file      main.cpp
 * \author    The C Team - Florian MARCO
 * \version   1.0
 * \date      17 Janvier 2018
 * \brief     Main function of program : dedicated to handling parameters 
 */
#include "optionparser.h"
#include "param.h"
#include "call_func.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <system_error>

using namespace std;

enum optionIndex {UNKNOWN, OUTPUT, HELP, VERSION, TYPECHECK, PARSER, ASML,ASML2,ASMLI,NOTYPECHECK,DEBUG};
enum optionType {ENABLE, OTHER,DISABLE};

struct Arg: public option::Arg {
  static option::ArgStatus Mandatory(const option::Option& option, bool){
    return option.arg == 0 ? option::ARG_ILLEGAL : option::ARG_OK;
  }
};

const option::Descriptor usage[]=
  {
    {UNKNOWN,OTHER,"","",option::Arg::None,"USAGE: ./mincamlc input file [options] \nOptions :"},
    {HELP,OTHER,"h","help",option::Arg::None,"-h, --help \t Print usage then quit."},
    {OUTPUT,OTHER,"o","output",Arg::Mandatory,"-o, --output filename\t You must specifiy an output filename"},
    {VERSION,OTHER,"v","version",option::Arg::None,"-v, --version \t Print version and exit"},
    {TYPECHECK,ENABLE,"t","typecheck",option::Arg::None,"-t, --typecheck \t Perform only Typecheck analysis. Return ErrorCode if incorrect typing [TODO]"},
    {PARSER,ENABLE,"p","parser",option::Arg::None,"-p, --parser \t Perform only mincaml parsing. Print AST in output file"},
    {ASML,ENABLE,"a","asml",option::Arg::None,"-a, --asml \t Perform only ASML generation"},
    {ASML2,ENABLE,"asml","asmlgen",option::Arg::None,""},
    {ASMLI,ENABLE,"i","asmlinput",option::Arg::None,"-i, --asmlinput \t Take ASML input and generate ARM output"},
    {NOTYPECHECK,DISABLE,"n","notypecheck",option::Arg::None,"-n, --notypecheck \t Dont do Typecheck analysis"},
    {DEBUG,ENABLE,"d","debug",option::Arg::None,"-d, --debug \t Print output for debug mode"},
    {0,0,0,0,0,0}
  };

int main(int argc, char *argv[]) { 
  int traitement_param = 0;
  bool is_inputfile = false;
  std::string inputfilename;
  std::string outputfilename;

  argc-=(argc>0); argv+=(argc>0); // skip program name argv[0] if present
  if ( argv[0][0] != '-' && argc != 0){
    inputfilename = argv[0];
    argc-=(argc>0); argv+=(argc>0); // input name argv[0] if present
    is_inputfile = true;
  }
  // cas ou le nom du fichier n'est pas au debut.
  if (!is_inputfile){
    for (int i=0; i < argc; i++) {
      if(strstr(argv[i], ".ml") ){
         inputfilename = argv[i];
         is_inputfile = true;
         for (int j = i; j < argc; j++){
          argv[j]=argv[j+1];         }
         argc -=(argc>0); 
    }
  }
  }
/*
  //Cas ou on veut generer un fichier .asml 
  if (!is_inputfile){
    for (int i=0; i < argc; i++) {
      if(strstr(argv[i], ".asml") ){
        inputfilename = argv[i];
        std::cout << "AFFICHAGE DU NOMFICHIER ENTREE" << inputfilename ;;
        is_inputfile = true;
      }
    }

  }*/

  option::Stats  stats(usage, argc, argv);
  std::vector<option::Option> options(stats.options_max);
  std::vector<option::Option> buffer(stats.buffer_max);
  option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);


  /* GESTION DES ERREURS */

  if (parse.error()){
    std::cerr << "Erreur: Parsing Error ";
    return 1;
  }


  if ((options[TYPECHECK].count() + options[PARSER].count() + options[ASML].count() +options[ASMLI].count()) > 1){
    
    std::cerr << "Erreur : Veuillez choisir une seule option \n";
    return 1;
  }

  //Test sur le fichier d'input
  // Check si le fichier existe réellement
  if (is_inputfile) {
    std::ifstream f(inputfilename.c_str());
    if (f.good()){
      //std::cout << "J'existe \n";
      f.open(inputfilename.c_str());
      if (f.is_open()){
	//std::cout << "Je suis ouvert \n";
	f.close();
      }
      else {
	std::cerr << "Erreur d'ouverture du fichier input\n";
	return 1;
      }
    }
    else {
      std::cerr <<"Erreur : le fichier input n'existe pas \n";
      return 1;
    }
  }


  // Test : aucun input fichier donne et on veut regarder la liste des arguments
  if (!is_inputfile) {
    if (!options[HELP] && !options[VERSION] && (argc > 0)){
      std::cerr <<"Erreur : Aucun fichier donne en entree ou mauvaise syntaxe \nTapez ./mincamlc -h pour afficher l'aide\n";
      return 1;
    }
  }
  // Check si on peut créer ou effacer ce fichier. 
  // Si pas de O : fichier par defaut ? 
  if (options[OUTPUT]){
    //std::cout << options[OUTPUT].arg ;
    std::ofstream outfile (options[OUTPUT].arg);
    outfile.close();
    outputfilename = options[OUTPUT].arg;
  }



  /* TRAITEMENT DES OPTIONS */
  if (options[HELP] || ( argc == 0 && !is_inputfile) ){
    option::printUsage(std::cout,usage);
    return 0;
  }

  if (options[VERSION]){
    std::cout << "Version du logiciel : 1.0.0 \n";
    return 0;
  }

  if (options[OUTPUT]){
    enable(traitement_param,PARAM_OUTPUT);
    if (!options[TYPECHECK] && !options[PARSER] && !options[ASML] && !options[ASMLI]){
      enable(traitement_param,TOTAL_ARM);}
  }
  else if (!options[HELP] && !options[VERSION] && !options[TYPECHECK]){
    //std::cout << "Fichier output : " << outputfilename;
    std::cerr <<"Erreur : aucun fichier output specifie \n" ;
    return 1;
  }

  if (options[TYPECHECK]){
    enable(traitement_param,TOTAL_TYPECHECK);
    //return 0;
  }

  if (options[PARSER]){
    enable(traitement_param,TOTAL_PARSE);
    // return 0;
  }

  if (options[ASML] || options[ASML2]){
    enable(traitement_param,TOTAL_ASML);
    // return 0;
  }

if (options[ASMLI]){
  enable(traitement_param,PARAM_ASMLI);

}

if (options[DEBUG]){
enable(traitement_param,PARAM_DEBUG);
}

  if (options[NOTYPECHECK]){
    disable(traitement_param,PARAM_TYPECHECK);
  }

  if (options[OUTPUT]){
    mega_caller(traitement_param,inputfilename,outputfilename);
  }
  else{
    mega_caller(traitement_param,inputfilename,"");
  }

  return 0;

}
