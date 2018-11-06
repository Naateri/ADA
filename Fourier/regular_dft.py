import cmath

def discrete_fourier_transformation(numbers):
    n = len(numbers)
    result = list()
    for k in range(n):
        s = complex(0)
        for t in range(n):
            #angle = 2j * cmath.pi * t * k / n
            #s += numbers[t] * cmath.exp(-angle)
            angle = 2*cmath.pi*k*t/n
            temp_cos = cmath.cos(angle)
            temp_sin = 1j * cmath.sin(angle)
            cos_sin = temp_cos - temp_sin 
            s += numbers[t] * cos_sin;
        result.append(s)
    return result

test = discrete_fourier_transformation([0,0,2,3,4,0,0,0])

for i in range (len(test)):
    print( str(test[i].real) + '\t' + str(test[i].imag ) )
