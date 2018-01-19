let rec ff aa bb = bb - aa in
let rec vicious f a b = f b a in
let simply = (vicious ff 42 111) in
print_int (simply)
