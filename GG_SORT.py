from random import randint
from time import clock

samples = [100, 1000, 10000, 50000, 100000, 1000000, 10000000]

def gg_sort(arr):
	n = len(arr)    
	for i in range(n):
		for j in range(0, n-i-1):
			if arr[j] > arr[j+1]:
				arr[j], arr[j+1] = arr[j+1], arr[j]
			for k in range(j+1):
				if arr[k] < arr[k+1]: #Por si acaso
					continue
 	
	return arr


def bubble_sort(arr):
	n = len(arr)    
	for i in range(n):
		for j in range(0, n-i-1):
			if arr[j] > arr[j+1]:
				arr[j], arr[j+1] = arr[j+1], arr[j]
	return arr

def quick_sort(arr):
	less = list()
	equal = list()
	greater = list()
	if len(arr) > 1:
		
		pivot = arr[0]
		for element in arr:
			if element < pivot:
				less.append(element)
			elif element > pivot:
				greater.append(element)
			else:
				equal.append(element)
		return quick_sort(less) + equal + quick_sort(greater)
	else:
		return arr

def heapify(arr, n, i):
	largest = i
	l = 2 * i + 1
	r = 2 * i + 2
	if l < n and arr[i] < arr[l]:
		largest = l

	if r < n and arr[largest] < arr[r]:
		largest = r

	if largest != i:
		arr[i], arr[largest] = arr[largest], arr[i]
		heapify(arr, n, largest)

def heapsort(arr):
	n = len(arr)
	for i in range(n, -1, -1):
		heapify(arr, n, i)

	for i in range(n-1, 0, -1):
		arr[i], arr[0] = arr[0], arr[i]
		heapify(arr, i, 0)				
	
	return arr

def merge(left, right):
	result = list()
	while (len(left) > 0 and len(right) > 0):
		if (left[0] < right[0]):
			result.append(left.pop(0))
		else:
			result.append(right.pop(0))
	while (len(left)>0):
		result.append(left.pop(0))
	while len(right)>0:
		result.append(right.pop(0))
	
	return result
		

def mergesort(arr):
	if len(arr) <= 1:
		return arr
	half = len(arr)//2
	left = arr[0:half]
	right = arr[half:len(arr)]
	return merge(mergesort(left), mergesort(right))	

def create_array(n):
	temp = list()
	for i in range(n):
		temp.append(randint(0,n))
	return temp

def compare_times():
	arr = list()
	temp = list()
	times = [0] * 5
	
	for sample in samples:
		print ("size: " + str(sample))
		print ("heapsort\tquicksort\tmergesort\tbubblesort\tggsort")
		arr.clear()
		arr = create_array(sample)
		start = clock()
		arr = heapsort(arr)
		end = clock()
		times[0] = (end-start)
		
		arr.clear()
		arr = create_array(sample)		
		start = clock()
		arr = quick_sort(arr)
		end = clock()
		times[1] = (end-start)

		arr.clear()
		arr = create_array(sample)
		start = clock()
		arr = mergesort(arr)
		end = clock()
		times[2] = (end-start)
	
		arr.clear()
		arr = create_array(sample)		
		start = clock()
		arr = bubble_sort(arr)
		end = clock()
		times[3] = (end-start)
#		times[3] = "xd"

		arr.clear()
		arr = create_array(sample)
		start = clock()
		arr = gg_sort(arr)
		end = clock()
		times[4] = (end-start)
#		times[4] = 0
			
		print ( str(times[0]) + "\t" +str(times[1]) + "\t"+str(times[2]) + "\t" + str(times[3]) + "\t" + str(times[4]) )
									
compare_times()
