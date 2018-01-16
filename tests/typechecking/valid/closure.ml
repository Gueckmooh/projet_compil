let rec f x y = (x,y) in let rec g n = g (n-1) in let (a,b) = f 5 4 in print_int (g a+b)
