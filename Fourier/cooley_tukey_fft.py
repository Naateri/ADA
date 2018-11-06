import cmath
import numpy as np
import matplotlib.pyplot as plt

def separate(numbers):
    temp = list()
    n = len(numbers)
    for i in range(int(n/2)):
        temp.append(numbers[i*2 + 1])
    for i in range(int(n/2)):
        numbers[i] = numbers[i*2]
    for i in range (int(n/2)):
        numbers[i+int(n/2)] = temp[i]
    #return numbers

def cooley_tukey_fft(numbers):
    n = len(numbers)
    if n == 1:
        return
    else:
        #separate(numbers)
        numbers_first_half = numbers[0:n:2] #even
        numbers_second_half = numbers[1:n:2] #odd
        cooley_tukey_fft(numbers_first_half)
        cooley_tukey_fft(numbers_second_half)

        #numbers.clear()

        for k in range(int(n/2)):
            t = numbers_first_half[k]
            t_1 = numbers_second_half[k]
            temp = complex(0, -2*cmath.pi*k/n)
            w = complex(cmath.exp(temp))
            numbers[k] = t + w * t_1
            numbers[k + int(n/2)] = t - w * t_1

        return numbers
        

test = cooley_tukey_fft([0,0,2,3,4,0,0,0])
#test = cooley_tukey_fft([complex(1,0),complex(2,-1),complex(0,-1),complex(-1,2)])
test_2 = np.fft.fft([0,0,2,3,4,0,0,0])

print ("My fourier: ")
for i in range (len(test)):
    print( str(test[i].real) + '\t' + str(test[i].imag ) )

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
