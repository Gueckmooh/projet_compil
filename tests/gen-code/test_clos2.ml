let a = 2 in
let rec make_adder x =
  let rec adder y = x + y + a in
  adder in
print_int ((make_adder 3) 7)
