let rec f x y = (x,y) in let (a,b) = f 5 4 in print_int(a+b) ; let rec g n = g (n-1) in print_int(g 5) ;
let rec id x = x in print_int(id 5) ; print_float(id 5.0)