let rec tup_maker value = (value, value, value) in
let rec make_adder x =
    let rec adder y = x + y in
    adder in
let rec apply_tup tup =
    let (f, a, b) = tup in
    f a b in
let x = 7 in
let rec whoisbest tup =
    let (f, g, a) = tup in
    let c1 = (f, a, x) in
    let c2 = (g, a, x) in
    if (apply_tup c1 < apply_tup c2)
    then (
        1
    ) else (
        2
    ) in
let rec add_x y = x + y in
let rec useless f a = f in
let tup = tup_maker 4 in
let tuptup = tup_maker tup in
let (t1, t2, t3) = tuptup in
let (a, b, c) = t1 in
let z = b + 3 in
let arg = (make_adder, useless add_x, z) in
print_int( whoisbest arg)
