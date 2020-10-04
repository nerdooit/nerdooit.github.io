mymap::(a->b)->[a]->[b]

mymap _ [] = []
mymap f (x:xs) = f x : mymap f xs
