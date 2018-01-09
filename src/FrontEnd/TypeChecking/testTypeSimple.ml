type typeSimple = Bool | Float | Int | Unit ;;
type typeComplexe = TS of typeSimple | TC of typeSimple * typeComplexe ;;


let rec print_typeSimple type_simple =
match type_simple with
|Bool -> "bool"
|Float -> "float"
|Int -> "int"
|Unit -> "unit" ;;

let rec print_typeComplexe type_complexe =
match type_complexe with
|TS ts -> print_typeSimple ts
|TC (ts,tc) -> "(" ^ print_typeSimple ts ^ " -> " ^ print_typeComplexe tc ^ ")" ;;


(* print_typeComplexe (TC (Int, (TC (Int, (C Int))))) ;; *)

(* print_typeComplexe TC (TS Int, (TC (TS Int, (TS Int)))) ;; *)

print_typeComplexe (TC (Int, (TC (Int, (TS Int))))) ;;
