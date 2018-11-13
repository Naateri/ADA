import cmath
from time import time
import matplotlib.pyplot as plt
import numpy as np

def discrete_fourier_transformation(numbers):
    n = len(numbers)
    result = list()
    for k in range(n):
        s = complex(0)
        for t in range(n):
            angle = 2*cmath.pi*k*t/n
            temp_cos = cmath.cos(angle)
            temp_sin = 1j * cmath.sin(angle)
            cos_sin = temp_cos - temp_sin 
            s += numbers[t] * cos_sin;
        result.append(s)
    return result

def time_measurement(n):
	iterations = 2 ** n
	fourier = list()
	for i in range(iterations):
		fourier.append(cmath.sin(i))
	start = time()
	discrete_fourier_transformation(fourier)
	end = time()
	print ("Tiempo de " + str(iterations) + " elementos: " + str(end-start) + " segundos.")			

test = discrete_fourier_transformation([0,2,2,3,4,4,5,6,0,0])
test_real = list()
test_imag = list()

print ("DFT")
print ("Valor real \t Valor imaginario")

for i in range (len(test)):
	print( str(test[i].real) + '\t' + str(test[i].imag ) )
	test_real.append(test[i].real)
	test_imag.append(test[i].imag)

print ("IDFT")
print ("Valor real \t Valor imaginario")

xd = np.fft.ifft(test)

for i in range (len(xd)):
	print (str(xd[i].real) + '\t' + str(xd[i].imag) )


plt.plot(range(len(test)), test_real, range(len(test)), test_imag)
plt.legend(('real', 'imaginary'))
plt.show()

plt.plot(range(len(test)), xd.real, range(len(test)), xd.imag)
plt.legend(('real', 'imaginary'))
plt.show()
"""
for i in range(5,15):
	time_measurement(i)	"""
