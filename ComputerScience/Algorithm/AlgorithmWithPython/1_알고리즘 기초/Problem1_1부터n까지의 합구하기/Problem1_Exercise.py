# Problem 1 +3
def sum_square1(num):
    s =0
    for n in range(1, num+1):
        s += n*n

    return s

def sum_square2(num):
    return num*(num + 1)*(2*num +1)//6

print(sum_square1(10))
print(sum_square2(10))


# Problem 2 +3
print("sum_square1 has complexity O(n)")
print("sum_square2 has complexity O(1)")
