def print_mat(m):
    for i in range(len(m)):
        for j in range(len(m[0])):
            print(str(m[i][j]), end = " ")
        print()

def lcs(s1,s2):
    lcs_s1 = list()
    lcs_s2 = list()
    for i in range(len(s1)):
        lcs_s1.append(s1[i])
    for i in range(len(s2)):
        lcs_s2.append(s2[i])
    m = list()
    temp = list()
    for i in range(len(s2)+1):
        temp.append(0)
    for i in range(len(s1)+1):
        m.append(temp)
    #print(m)
    #print_mat(m)
    #for i in range(len(s2)):
    #    m[i][0] = 0
    for i in range(len(s1)):
        for j in range(len(s2)):
            if s1[i] == s2[j]:
                m[i+1][j+1] = m[i][j] + 1
            else:
                m[i+1][j+1] = max(m[i][j+1],m[i+1][j])

    return m[len(s1)][len(s2)]
    
print(str(lcs('abcbdab','bdcaba')))
