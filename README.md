# Projet Compilation : The C Team

A Compiler from Mincaml to ARM, that also generates ASML a pseudo-code between mincaml and Assembly language. 

Group Member : Baptiste BLEUZE, Enzo BRIGNON, Florian MARCO, Maxime RAYNAL

USAGE
=====

USAGE mincamlc input_file options

|PARAMETER| FUNCTION|

| --- | --- | --- |

|-h, --help|                Print usage.|

|-o, --output output_file|  You must specifiy an output filename.|

|-v, --version           | Print version.|

|-t, --typecheck        |  Perform only Typecheck analysis. Return ErrorCode if incorrect typing.| 

|-p, --parser           |  Perform only mincaml parsing. Print AST in output file|

|-a --asml               |  Perform only ASML generation. Print ASML in output file.|

|-i, --asmlinput         | Take ASML input and generate ARM output. Print ARM in output file.|
 
 TODO LIST
 =====

FRONT END 
------

- [ ] Typechecking

- [X] K-Normalization
- [X] alpha-conversion
- [X] reduction of nested-let
- [ ] closure conversion
- [ ] ASML generation
- [ ] beta-reduction
- [ ] inline expansion
- [ ] constant folding
- [ ] elimination of unnecessary definitions

- [X] Contact with backend structure


BACK END 
------

- [X] simple arithmetic expression
- [X] call to external functions
- [X] functions (let rec)
- [X] if-then-else
- [X] closures, tuple, arrays

- [X] ASML Parsing
- [X] ASML Generation
- [X] ARM Generation

- [X] Basic Register Allocation
- [ ] Smart Register Allocation : dominance tree
- [ ] Garbage Collector

GENERAL
------

- [X] Command Line Options 
- [X] Full MAKEFILE
- [X] Libraries integration
- [ ] Full Integration

- [X] Test files
- [X] Make Test (basic BASH)
- [ ] Make Test (python)

NOTES
=====

S'il vous plait laisser le main dans un fichier main.c ou main.cpp
N'utiliser que les extensions .c, .cpp et .h
Les .o se trouvent dans le répertoire .obj
Les tests devons être dans le dossier test et devrons contennir chacun leur
main. (A négocier si vous voulez)

Ne pas modifier le mon joli Makefile, il a pour vocation de fonctionner de
manière générique. Il pourra être amélioré par la suite :)
