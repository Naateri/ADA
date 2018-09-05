def sum(a, b):
    if b == 0:
        return a
    return sum(a+1, b-1);
    
def subs(a,b):
    if b == 0:
        return a
    return subs(a-1, b-1);

def mult(a,b, temp = 0):
    if b == 0:
        return temp;
    return mult(a, b-1, sum(temp, a));

def div(a, b, temp = 0):
    if a < b:
        return temp;
    return div(subs(a,b), b, temp+1);
    

print str(sum(9,5));
print str(subs(9,5));
print str(mult(9,5));
print str(div(50,5));
