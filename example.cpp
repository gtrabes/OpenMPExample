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

using namespace std;

int main(int argc, char **argv) {

	double *x,*y, partial_result, result;
	int P, n;

	P=atoi(argv[1]);
	n=atoll(argv[2]);

	x = (double*)malloc(n*sizeof(double));
	y = (double*)malloc(n*sizeof(double));

	/* initialization */

	for(int i=0;i<n; i++){
		x[i]=1.0;
		y[i]=1.0;
	}

	/* inner product */

	for(int i=0;i<n; i++){
		partial_result+=x[i]*y[i];
	}

	cout << "Result:" << partial_result << endl;

	return EXIT_SUCCESS;
}
