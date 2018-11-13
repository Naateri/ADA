import cmath
import numpy as np
import matplotlib.pyplot as plt
from time import time

def cooley_tukey_fft(numbers):
    n = len(numbers)
    if n == 1:
        return
    else:
        numbers_first_half = numbers[0:n:2] #even
        numbers_second_half = numbers[1:n:2] #odd
        cooley_tukey_fft(numbers_first_half)
        cooley_tukey_fft(numbers_second_half)

        for k in range(int(n/2)):
            t = numbers_first_half[k]
            t_1 = numbers_second_half[k]
            temp = complex(0, -2*cmath.pi*k/n)
            w = complex(cmath.exp(temp))
            numbers[k] = t + w * t_1
            numbers[k + int(n/2)] = t - w * t_1

        return numbers

def time_measurement(n):
	iterations = 2 ** n
	fourier = list()
	for i in range(iterations):
		fourier.append(cmath.sin(i))
	start = time()
	cooley_tukey_fft(fourier)
	end = time()
	print ("Tiempo de " + str(iterations) + " elementos: " + str(end-start) + " segundos.")			

        

test = cooley_tukey_fft([0,2,2,3,4,4,5,6,0,0])
test_2 = np.fft.fft([0,2,2,3,4,4,0,0])
test_real = list()
test_imag = list()

#print ("My fourier: ")
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
plt.legend(('real fft', 'imaginary fft'))
plt.show()

plt.plot(range(len(test)), xd.real, range(len(test)), xd.imag)
plt.legend(('real fft', 'imaginary fft'))
plt.show()

"""
#test_freq = np.fft.fftfreq(int(len(test)),0.1)
temp_real = list()
temp_imag = list()
test_freq = list()
for i in range(8):
    test_freq.append(i)


print ( test_freq )

for i in range (len(test)):
    temp_real.append(test[i].real)
    temp_imag.append(test[i].imag)

plt.plot(test_freq, temp_real, test_freq, temp_imag)
plt.show()

print ("numpy: ")
for i in range (len(test_2)):
    print( str(test_2[i].real) + '\t' + str(test_2[i].imag ) )


t = [0]* 256
for i in range(0,256):
    t[i] = (cmath.sin(i))
    #t[i] = 4;

sp = cooley_tukey_fft(t)
freq = np.fft.fftfreq(len(t))
sp_real = list()
sp_imag = list()
for i in range(len(t)):
    sp_real.append(t[i].real)
    sp_imag.append(t[i].imag)

plt.plot(freq, sp_real, freq, sp_imag)
plt.show()

for i in range(5,15):
	time_measurement(i)	

"""

