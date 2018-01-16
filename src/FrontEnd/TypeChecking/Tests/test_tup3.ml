let (e,h,g) = 1,2,3 in
let rec f x =
    let (a,b) = x in a in
print_int(f (2,3))
