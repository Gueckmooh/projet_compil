#!/bin/bash

echo "-- Execution des tests du Mincaml Compilateur"
echo "-- Version 1.0.0 - Bash"

mkdir tmp

echo "-- Test du Parsing [NOT YET FUNCTIONING]"


scripts/mincamlc tests/syntax/invalid/no_closing_paren.ml -p -o tmp/parse1
T1=$?
scripts/mincamlc tests/syntax/valid/simple_call.ml -p -o tmp/parse2
T2=$?
if [ $(($T1 + $T2)) = 0 ]; then 
	echo "-- Parsing effectue avec succes"
else
	echo "-- Echec du test de parsing"
fi


echo "-- Test de Typechecking [NOT YET IMPLEMENTED]"

scripts/mincamlc tests/typechecking/invalid/call_bad_arg.ml -t
T3=$?
scripts/mincamlc tests/typechecking/invalid/main_unit.ml -t
T4=$?
scripts/mincamlc tests/typechecking/valid/simple_call.ml -t
T5=$?

if [ $(($(($T3 + $T4))+ $T5)) = 0 ]; then
	echo "-- Typechecking effectue avec succes"
else
	echo "-- Echec du Typechecking"
fi

echo "-- Test d'execution"

scripts/mincamlc tests/gen-code/op.ml -o tests/outcode1.s
cd tests && make 
./default.arm 
T6=$?
make clean && rm outcode1.s && cd ..

ocamlc tests/gen-code/op.ml -o tmp/outgood1

tmp/outgood1
T7=$?

if [ $T6 = $T7 ]; then
	echo "-- Test d'execution effectue avec succes"
else
	echo "-- Echec du test d'execution"
fi

echo "-- Test de traitement de l'ASML"

scripts/mincamlc tests/asml_to_arm/print_zero.asml -i -o tests/outasml1.s
cd tests && make 
./default.arm 
T8=$?
make clean && rm outasml1.s && cd ..

scripts/asml tests/asml_to_arm/print_zero.asml 
T9=$?

if [ $T8 = $T9 ]; then
	echo "-- Test de traduction ASML a ARM effectue avec succes"
else
	echo "-- Echec du test de traduction ASML to ARM"
fi

rm -rf tmp
#YA DES PTITS BUGS JY RETOUCHE QUAND ON A FINI LINTEGRATION
