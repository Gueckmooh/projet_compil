let rec f x =
    let rec g y = y
    in g x
in print_int(f 8)
