let rec incr n = if n <= 1 then n else 1 + incr (n-1) in print_int (incr 5)
