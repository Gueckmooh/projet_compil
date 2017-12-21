#!/bin/bash

echo "Execution des tests du Mincaml Compilateur"
echo "Version 1.0.0 - Bash"

mkdir tmp

echo "Test du Parsing"


scripts/mincamlc tests/syntax/invalid/no_closing_paren.ml -p -o tmp/parse1
T1=$?
scripts/mincamlc tests/syntax/valid/simple_call.ml -p -o tmp/parse2
T2=$?
#TODO : MODIFIER LES VALEURS RETOURS
if [ $(($T1 + $T2)) = 1 ]; then 
	echo "Parsing effectue avec succes"
else
	echo "Echec du test de parsing"
fi


echo "Test de Typechecking "

scripts/mincamlc tests/typechecking/invalid/call_bad_arg.ml -t
T3=$?
scripts/mincamlc tests/typechecking/invalid/main_unit.ml -t
T4=$?
scripts/mincamlc tests/typechecking/valid/simple_call.ml -t
T5=$?

#TODO : MODIFIER LES VALEURS RETOURS
if [ $(($(($T3 + $T4))+ $T5)) = 0 ]; then
	echo "Typechecking effectue avec succes"
else
	echo "Echec du Typechecking"
fi

echo "Test d'execution"

scripts/mincamlc tests/gen-code/op.ml -o tmp/outcode1

ocamlc tests/gen-code/op.ml -o tmp/outgood1

tmp/outcode1
T6=$?

tmp/outgood1
T7=$?

if [ $T6 = $T7 ]; then
	echo "Test d'execution effectue avec succes"
else
	echo "Echec du test d'execution"
fi

echo "Test de traitement de l'ASML"

scripts/mincamlc tests/asml_to_arm/print_zero.asml -i -o tmp/outasml1
tmp/outasml1
T8=$?

scripts/asml tests/asml_to_arm/print_zero.asml 
T9=$?

if [ $T8 = $T9 ]; then
	echo "Test de traduction ASML a ARM effectue avec succes"
else
	echo "Echec du test de traduction ASML to ARM"
fi


