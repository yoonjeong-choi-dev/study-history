"""
Make a function which returns the absolute value
"""

def abs_sign(num):
    if num < 0:
        return -num
    else:
        return num

def abs_square(num):
    import math
    b = num * num
    return math.sqrt(b)



test1 = 9
test2 = 4
print(abs_sign(test1))
print(abs_square(test2))