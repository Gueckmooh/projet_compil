let rec f x =
    let rec g y = (y,y) in x + x
in print_int(f 5)
