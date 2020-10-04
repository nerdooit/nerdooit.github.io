
xs = [("Kim", 60), ("Park",80), ("Choi", 70), ("Lee", 90), ("Jung", 85)]

-- 2.1
listComprehension = [(a,b) | (a,b) <- xs, b >= 80]

-- 2.2
filterAndLambda= filter (\(a,b)-> if b >=80 then True else False) xs

-- 2.3
-- functionComposition xs3 = filter $ listComprehension
