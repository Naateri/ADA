from Tkinter import *
from matplotlib import pyplot as plt
import numpy as np


x_axis_size = 100;
y_axis_size = 1000;
x = np.arange(1.0, x_axis_size, 1.0);

const_temp = [];
for i in range (x_axis_size):
	const_temp.append(1);

const = np.array(const_temp);
loglogn = np.log2(np.log2(x));
logn = np.log2(x);
ne = np.power(x, 0.5);
n2 = np.power(x,2);
nlogn = np.power(x, np.log2(x));
expo = np.power(2, x);
ntothen = np.power(x,x);
c_c_n = np.power(2, np.power(2, x));

plt.axis([1,x_axis_size,0,y_axis_size]);
plt.grid(True);

plt.plot(const, label="constant (O(1))");
plt.plot(x, loglogn, label="log(logn)");
plt.plot(x, logn, label="logn");
plt.plot(x, ne, label="n^e, e = 0.5");
plt.plot(x, n2, label="n^c, c = 2");
plt.plot(x, nlogn, label="n^logn");
plt.plot(x, expo, label="c^n, c = 2");
plt.plot(x, ntothen, label="n^n");
plt.plot(x, c_c_n, label="c^c^n, c = 2");

plt.legend();

plt.show();
