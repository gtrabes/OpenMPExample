//============================================================================
// Name        : example.cpp
// Author      : Guillermo Trabes
// Version     :
// Copyright   : * Copyright (c) 2020, Guillermo G. Trabes * Carleton University, Universite de Nice-Sophia Antipolis* All rights reserved.
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include "mytime.h"
#include <sched.h>


using namespace std;

int main(int argc, char **argv) {

	double *x,*y, time, *partial_result, result=0;
	int P, n, i;
	CLOCK_TYPE begin, end;

	P=atoi(argv[1]);
	n=atoll(argv[2]);

	x = (double*)malloc(n*sizeof(double));
	y = (double*)malloc(n*sizeof(double));

	partial_result = (double*)malloc(P*sizeof(double));

	/* initialization */

	for(int i=0; i<n; i++){
		x[i]=1.0;
		y[i]=1.0;
	}

	for(int i=0; i<P; i++){
		partial_result[i]=0.0;
	}

	omp_set_num_threads(P);

	GETTIME(begin);

	/* inner product */
	#pragma omp parallel shared (i,x,y) private(partial_result)
	{
		int tid   = omp_get_thread_num();
		int procs = omp_get_num_threads();
		unsigned long len;
		cpu_set_t mascara;
		CPU_ZERO (&mascara);

		//Esto es para 1 Thread por core
		len = sizeof(cpu_set_t);
		CPU_SET (tid, &mascara);
		if (sched_setaffinity(0, len, &mascara) < 0)
			printf("\n\nError :: sched_setaffinity\n\n");

		#pragma parallel for static(1)
		for(i=0; i<n; i++){
				partial_result[tid]+=x[i]*y[i];

//				#pragma omp critical
//				cout << "ID:" << omp_get_thread_num()  << endl ;
		}

	}

	for(int i=0; i<P; i++){
		result+=partial_result[i];
	}

	GETTIME(end);
	DIFTIME(end,begin,time);

	cout << "Result:" << partial_result << " time: "<< time << endl ;

	return EXIT_SUCCESS;
}
