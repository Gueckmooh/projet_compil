let (o,p,q) = (int, (), false) in
let tuple = o,p,q in
let (a,b,c) = (1,2,3) in
let x = 5 in
let y = 4 in
(a+4,5-b,c+6) ;
print_int(x+y+x+y+x-x-y-x-y-x) ;
true ;
false ;
0.0 ;
() ;
let tup = (1,2,3,4) in
let (e,f,g,h) = tup in
print_int(e) ;
let y1 =
    let x1 = 2 in x1,x1+1 in
let (a1,b1) = y1 in
print_int(b1) ;
let rec f1 x2 y2 = (x2,y2) in let (a2,b2) = f1 5 4 in print_int(a+b) ; let rec g1 n = g1 (n-1) in print_int(g1 5) ;
let rec id x3 = x3 in print_int(id 5) ; print_float(id 5.0)
