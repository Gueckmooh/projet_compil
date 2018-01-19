#!/bin/bash
echo "let x = 42 in print_int x" > test1.ml
scripts/mincamlc -t test1.ml 
echo $? # should be 0
scripts/mincamlc -asml test1.ml -o test1.asml
tools/asml test1.asml  # displays 42
scripts/mincamlc -o test1.s test1.ml
scripts/genarmexe test1.s # generates file test1 
qemu-arm test1 # displays 42
make test # should run your tests
