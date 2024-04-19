doubleFunc :: Int -> Int
doubleFunc x = x * 2

main :: IO()
main = do
    print (doubleFunc 30)