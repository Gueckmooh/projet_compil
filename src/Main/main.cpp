#include "optionparser.h"
#include <iostream>
#include <string>
#include <vector>

enum optionIndex {UNKNOWN, OUTPUT, HELP, VERSION, TYPECHECK, PARSER, ASML};
enum optionType {ENABLE, OTHER};

struct Arg: public option::Arg {
	static option::ArgStatus Mandatory(const option::Option& option, bool){
		return option.arg == 0 ? option::ARG_ILLEGAL : option::ARG_OK;
	}
};

const option::Descriptor usage[]=
{
	{UNKNOWN,OTHER,"","",option::Arg::None,"USAGE: ./mincamlc [options] \nOptions : "},
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
  option::Stats  stats(usage, argc, argv);
  std::vector<option::Option> options(stats.options_max);
  std::vector<option::Option> buffer(stats.buffer_max);
  option::Parser parse(usage, argc, argv, &options[0], &buffer[0]);

  if (parse.error()){
  	return 1;
  	// TODO : Print Stderr
  }

  if (options[HELP] || argc == 0){
  	option::printUsage(std::cout,usage);
  	return 0;
  }

return 0;

}
