def fib(n):
    if n <= 1:
        return n
    return fib(n-1) + fib(n-2)

def fib_dp(n):
    fib_list = [0]*(n+1)
    fib_list[0] = 0
    if n >= 1:
        fib_list[1] = 1
    for i in range(2,n+1):
        fib_list[i] = fib_list[i-2] + fib_list[i-1]
    return fib_list[n]

def fib_iter(n):
    a,b = 0,1
    for i in range(n):
        a,b = b, a+b
    return a


for i in range(10):
    print("regular fibonacci: " + str(fib(i)))
    print("dp fibonacci: " + str(fib_dp(i)))

print(str(fib(50)))
print(str(fib_dp(20000)))
