#Assigment 3:Bubble_and_Shell_Sort_complexity

import time
from random import randint

def bubbleSort(arr,n):
	st=time.perf_counter()
	for i in range(n - 1):
		for j in range(0, n - i - 1):
			if arr[j] > arr[j + 1]:
				arr[j], arr[j + 1] = arr[j + 1], arr[j]
	sp=time.perf_counter()
	return sp - st

def shellSort(arr, n):
	st = time.perf_counter()
	gap = n // 2
	while gap > 0:
		j = gap
		while j < n:
			i = j - gap
			while i >= 0:
				if arr[i + gap] > arr[i]:
					break
				else:
					arr[i + gap], arr[i] = arr[i], arr[i + gap]
				i = i - gap
			j += 1
		gap = gap // 2
	sp = time.perf_counter()
	return sp - st

num=int(input("Type 1 for best case, 2 for average case or 3 for worst case: "))
if num==1:
	n = 400
	arr = []
	for i in range(0,(n*16)):
		arr.append(i)
	aux=[]
	aux=arr.copy()
	print("Bubble Sort, 400 elements execution time:",bubbleSort(aux,n))
	aux = arr.copy()
	print("Bubble Sort, 800 elements execution time:", bubbleSort(aux, 2*n))
	aux = arr.copy()
	print("Bubble Sort, 1600 elements execution time:", bubbleSort(aux, 4*n))
	aux = arr.copy()
	print("Bubble Sort, 3200 elements execution time:", bubbleSort(aux, 8 * n))
	aux = arr.copy()
	print("Bubble Sort, 6400 elements execution time:", bubbleSort(aux, 16 * n))
	print("\n")
	print("Shell Sort, 400 elements execution time:", shellSort(aux,n))
	aux = arr.copy()
	print("Shell Sort, 800 elements execution time:", shellSort(aux, 2*n))
	aux = arr.copy()
	print("Shell Sort, 1600 elements execution time:", shellSort(aux, 4 * n))
	aux = arr.copy()
	print("Shell Sort, 3200 elements execution time:", shellSort(aux, 8 * n))
	aux = arr.copy()
	print("Shell Sort, 6400 elements execution time:", shellSort(aux, 16 * n))

elif num==2:
	n = 400
	arr = []
	for i in range(0, 16*n):
		value=randint(0,6400)
		arr.append(value)

	aux = arr.copy()
	print("Bubble Sort, 400 elements execution time:", bubbleSort(aux, n))
	aux = arr.copy()
	print("Bubble Sort, 800 elements execution time:", bubbleSort(aux, 2 * n))
	aux = arr.copy()
	print("Bubble Sort, 1600 elements execution time:", bubbleSort(aux, 4 * n))
	aux = arr.copy()
	print("Bubble Sort, 3200 elements execution time:", bubbleSort(aux, 8 * n))
	aux = arr.copy()
	print("Bubble Sort, 6400 elements execution time:", bubbleSort(aux, 16 * n))
	print("\n")
	print("Shell Sort, 400 elements execution time:", shellSort(aux, n))
	aux = arr.copy()
	print("Shell Sort, 800 elements execution time:", shellSort(aux, 2 * n))
	aux = arr.copy()
	print("Shell Sort, 1600 elements execution time:", shellSort(aux, 4 * n))
	aux = arr.copy()
	print("Shell Sort, 3200 elements execution time:", shellSort(aux, 8 * n))
	aux = arr.copy()
	print("Shell Sort, 6400 elements execution time:", shellSort(aux, 16 * n))

elif num==3:
	n = 400
	arr = []
	for i in range(0, 16 * n):
		arr.append(6400-i)
	aux=[]
	aux=arr.copy()
	print("Bubble Sort, 400 elements execution time:", bubbleSort(aux, n))
	aux = arr.copy()
	print("Bubble Sort, 800 elements execution time:", bubbleSort(aux, 2 * n))
	aux = arr.copy()
	print("Bubble Sort, 1600 elements execution time:", bubbleSort(aux, 4 * n))
	aux = arr.copy()
	print("Bubble Sort, 3200 elements execution time:", bubbleSort(aux, 8 * n))
	aux = arr.copy()
	print("Bubble Sort, 6400 elements execution time:", bubbleSort(aux, 16 * n))
	print("\n")
	arr.clear()
	for i in range(0, 16*n):
		value=randint(0,6400)
		arr.append(value)
	aux=arr.copy()
	print("Shell Sort, 400 elements execution time:", shellSort(aux, n))
	aux = arr.copy()
	print("Shell Sort, 800 elements execution time:", shellSort(aux, 2 * n))
	aux = arr.copy()
	print("Shell Sort, 1600 elements execution time:", shellSort(aux, 4 * n))
	aux = arr.copy()
	print("Shell Sort, 3200 elements execution time:", shellSort(aux, 8 * n))
	aux = arr.copy()
	print("Shell Sort, 6400 elements execution time:", shellSort(aux, 16 * n))
