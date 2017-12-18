#include "optionparser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <system_error>

using namespace std;

enum optionIndex {UNKNOWN, OUTPUT, HELP, VERSION, TYPECHECK, PARSER, ASML};
enum optionType {ENABLE, OTHER};

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
	{ASML,ENABLE,"asml","asml",option::Arg::None,"-asml \t Perform only ASML generation"},
	{0,0,0,0,0,0}
};

int main(int argc, char *argv[]) { 

  argc-=(argc>0); argv+=(argc>0); // skip program name argv[0] if present
  bool is_inputfile = false;
  std::string inputfilename;
  if ( argv[0][0] != '-' && argc != 0){
  	inputfilename = argv[0];
  	argc-=(argc>0); argv+=(argc>0); // input name argv[0] if present
	//std::cout << "test : " << filename;
	is_inputfile = true;
}

  option::Stats  stats(usage, argc, argv);
  std::vector<option::Option> options(stats.options_max);
  std::vector<option::Option> buffer(stats.buffer_max);
  option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);


/* GESTION DES ERREURS */

//std::cout << argv[0];

  if (parse.error()){
  	std::cout << "zboub";
  	return 1;
  	// TODO : Print Stderr
  }


  if ((options[TYPECHECK].count() + options[PARSER].count() + options[ASML].count()) > 1){
  	std::cout << "Erreur : Veuillez choisir une seule option \n";
  	//TODO : Print Stderr
  	return 1;
  }

//TODO : Test sur le fichier d'input
// Check si le fichier existe réellement
  
std::ifstream f;

// Set exceptions to be thrown on failure
f.exceptions(std::ifstream::failbit | std::ifstream::badbit);

try {
    f.open(inputfilename.c_str());
} catch (std::system_error& e) {
    std::cerr << e.code().message() << std::endl;
}


// TODO : Test : aucun input fichier donne et on veut regarder la liste des arguments

//TODO : Si fichier d'output : TEST
// Check si on peut créer ou effacer ce fichier. 
// Si pas de O : fichier par defaut ? 

/* TRAITEMENT DES OPTIONS */
  if (options[HELP] || ( argc == 0 && !is_inputfile) ){
  	option::printUsage(std::cout,usage);
  	return 0;
  }

  if (options[VERSION]){
  	std::cout << "Version du logiciel : TODO \n";
  	//return 0;
  }

  if (options[OUTPUT]){
  	std::cout << "On prends un fichier output : TODO \n";
  }
  else {
  	// TODO : tester si on est pas dans Version ou Help. (et eventuellement typecheck)
  	std::cout <<"On prends le fichier output par defaut : TODO";
  }

  if (options[TYPECHECK]){
  	std::cout << "On fait le Typecheck : TODO \n";
  	//return 0;
  }

  if (options[PARSER]){
  	std::cout << "On fait le parsing : TODO \n";
  	// return 0;
  }

  if (options[ASML]){
  	std::cout << "On fait la generation ASML : TODO \n";
  	// return 0;
  }

return 0;

}
