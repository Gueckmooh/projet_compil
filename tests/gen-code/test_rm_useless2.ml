let rec f x = x + x in
let z = f 5 in
let useless = z + z in
let useless2 = useless + z in
let x = 8 in
print_int(x)
