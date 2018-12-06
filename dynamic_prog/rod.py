def rod(p,n):
    if n <= 0:
        return 0
    q = -1
    for i in range(n):
        q = max(q,p[i] + rod(p, n-i-1))
    return q

def rod_dp(p,n):
    aux = [0] * (n+1)
    aux[0] = 0
    for i in range(1,n+1):
        q = -1
        for j in range(i):
            #q = max(q, p[j] + aux[i-j-1])
            if p[j] + aux[i-j-1] > q:
                q = p[j] + aux[i-j-1]
                print("i: " + str(i) + ", j: " + str(j))
        aux[i] = q
    return aux[n]

print(str(rod([1,5,8,9,10,17,17,20,14,30],4)))
print(str(rod_dp([1,5,8,9,10,17,17,20,14,30],4)))
