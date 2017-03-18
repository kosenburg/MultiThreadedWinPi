// WinPi.cpp : Defines the entry point for the console application.
// Kevin Osenburg
// Cocs 509
// Lab 2
// Creates multiple threads the calculate the value of Pi. Each thread will perform the sum for a
// partition of the problem. The total number of steps is divided by the number of threads. Each
// thread will then start at a multiple of the partition and perform the sum for its area. The sums
// are stored in an array of solutions, which are then added together after all of the threads have returned.
// The rest of the program then follows the original one given for finding Pi.




#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
static long num_steps = 100000;
double step, pi;
const int numThreads = 4;
double solutionsForEachThread[numThreads] = { 0.0 };

DWORD WINAPI helloFunc(LPVOID pArg) {
	int partition = num_steps / numThreads;
	int threadNumber = *((int*)pArg);

	 
	
	// calculates the upperbound for the partition this thread is working on
	int upperBound = threadNumber*partition + partition; 
	
	double x, sum = 0.0; // internal loop variables used
	
	for (int i = threadNumber * partition; i < upperBound; i++) {
		x = (i + 0.5)*step;
		sum = sum + 4.0 / (1.0 + x*x);
	}
	solutionsForEachThread[threadNumber] = sum;
	return 0;
}

int main()
{
	
	step = 1.0 / (double)num_steps;
	
	HANDLE hThread[numThreads]; // holds all the threads created
	int tNum[numThreads]; // reference variable for each thread number
	
	for (int i = 0; i < numThreads; i++) {
		tNum[i] = i;
		hThread[i] = CreateThread(NULL, 0, helloFunc, &tNum[i], 0, NULL);
		printf("Creating thread %d\n", tNum[i]);
	}
	
	printf("Waiting...\n");
	WaitForMultipleObjects(numThreads, hThread, TRUE, INFINITE);

	printf("All threads have returned! Calculating sum now...\n");
	double sum = 0.0;
	for (int j = 0; j < numThreads; j++) {
		sum += solutionsForEachThread[j];
	}

	pi = step * sum;
	printf("Pi =%12f\n", pi);
    return 0;
}

