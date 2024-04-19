myFirstInit [] = []
myFirstInit ns = take (length ns - 1) ns

mySecondInit [] = []
mySecondInit ns = reverse (drop 1 (reverse ns))

add :: (Int, Int) -> Int
add (x, y) = x + y

sub :: Int -> (Int -> Int)
sub x y = x - y

connect :: [a] -> ([a] -> ([a] -> [a]))
connect a b c = (a ++ b) ++ c

myAbs :: Int -> Int
myAbs n = if n >= 0 then n else -n

myNewAbs n | n >= 0 = n
           | otherwise = -n


myHead :: [a] -> a
myHead (x:_) = x

myTail :: [a] -> [a]
myTail (_:xs) = xs