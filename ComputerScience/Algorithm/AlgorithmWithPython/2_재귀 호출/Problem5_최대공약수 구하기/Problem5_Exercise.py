def Fibo(num):
    if num < 0:
        print(Fibo.__name__,': wrong input')
    if num == 0:
        return 0

    if num == 1:
        return 1

    return Fibo(num-1) + Fibo(num-2)

def Fibo_list(num):
    "num 개의 피보나치 수열을 list 로 반환"
    fibo_list = []
    for i in range(num):
        fibo_list.append(Fibo(i))

    return fibo_list

print(Fibo_list(10))