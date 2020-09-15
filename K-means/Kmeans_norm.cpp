#include <stdlib.h>
#include <stdio.h>

#include <errno.h>
#include <limits.h>

// #include "functions.h"
#include <math.h>

#define READ_ERROR_STRING "Error:\tFile was not in correct format.\n"

#define USAGE_STRING "(USAGE:./executableName input_file k_value)"


// Define a struct point
typedef struct point {
	double x = 0, y = 0, z = 0;
	//double *p;
	//int pSize = 2;
	int count = 0;
	int group = 0;
} point;


// Define functions

// calculate eucledean distance
double dist(point* c, point* p) {
	double xx = c->x - p->x;
	double yy = c->y - p->y;
	double zz = c->z - p->z;
	return sqrt(xx * xx + yy * yy + zz * zz);
}


// assign points to k centroids
void Group(point* p, point** parr, int k) {
	double min = dist(p, parr[0]);
	p->group = parr[0]->group;

	for (int i = 0; i < k; i++) {
		double d = dist(p, parr[i]);
		if (d <= min) {
			min = d;
			p->group = parr[i]->group;
		}
	}
}


// calculate the sum of root-mean-square
double sum_rms(double** data_array, int r, int c, point** parr, int k) {
	double rms = 0;
	//int k = sizeof(**parr);

	for (int i = 0; i < r; i++) {
		point* p = (point*)malloc(sizeof(point));

		if (c == 2) {
			p->x = data_array[i][0];
			p->y = data_array[i][1];
			Group(p, parr, k);
		}

		if (c == 3) {
			p->x = data_array[i][0];
			p->y = data_array[i][1];
			p->z = data_array[i][2];
			Group(p, parr, k);
		}

		for (int i = 0; i < k; i++) {
			if (p->group == i) {

				rms += dist(p, parr[i]);
				break;
			}
		}
		free(p);
	}
	rms = rms / r;
	return rms;
}


// update k centroids
void update(double** data_array, int r, int c, point* parr[], int k) {

	// record coordinates of initial centroids
	
	for (int i = 0; i < r; i++) {
		point* p = (point*)malloc(sizeof(point));

		if (c == 2) {
			p->x = data_array[i][0];
			p->y = data_array[i][1];
			Group(p, parr, k);
		}

		if (c == 3) {
			p->x = data_array[i][0];
			p->y = data_array[i][1];
			p->z = data_array[i][2];
			Group(p, parr, k);
		}

		for (int i = 0; i < k; i++) {
			if (p->group == i) {
				parr[i]->x += p->x;
				parr[i]->y += p->y;
				parr[i]->z += p->z;

				(parr[i]->count)++;
				break;
			}
		}
		free(p);
	}
	for (int i = 0; i < k; i++) {
		parr[i]->x = (parr[i]->x) / (parr[i]->count +1);
		parr[i]->y = (parr[i]->y) / (parr[i]->count +1);
		parr[i]->z = (parr[i]->z) / (parr[i]->count +1);
		int g = i + 1;
		printf("\tsize of group %d is: %d\t", g, parr[i]->count);
		parr[i]->count = 0;
	}
}


// conduct K-means iterations
void Kmeans(int k, double** data_array, int row, int col) {
	// Parameters
	int iteration_max = 1000;
	int step = 1;
	double thresold = 100;
	double rms = 1000000;


	// initialize k centroids
	point** parr = (struct point**)malloc(k * sizeof(struct point));
	for (int i = 0; i < k; i++) {
		parr[i] = (point*)malloc(sizeof(struct point));
	}
	if (col == 2) {
		for (int i = 0; i < k; i++) {

			parr[i]->x = data_array[i][0];
			parr[i]->y = data_array[i][1];
			parr[i]->group = i;
		}
	}
	if (col == 3) {
		for (int i = 0; i < k; i++) {
			parr[i]->x = data_array[i][0];
			parr[i]->y = data_array[i][1];
			parr[i]->z = data_array[i][2];
			parr[i]->group = i;
		}
	}


	// Repeat iterations until iter_step = iteration_max or sum_rms < thredshold
	while (step <= iteration_max) {
		rms = sum_rms(data_array, row, col, parr, k);

		for (int i = 0; i < k; ++i) {
			double xx = parr[i]->x;
			double yy = parr[i]->y;
			double zz = parr[i]->z;
			int g = i + 1;

			if (col == 2) {
				printf("\nCoordinates of centroid of group %d is: %.1f, %.1f", g, xx, yy);
			}
			if (col == 3) {
				printf("\nCoordinates of centroid of group %d is: %.1f, %.1f, %.1f", g, xx, yy, zz);
			}
		}
		printf("\n root-mean-square of %d th iteration is: %.1f", step, rms);
		++step;
		if (rms < thresold) {
			break;
		}

		update(data_array, row, col, parr, k);
	}

	printf("\nKmeans stop after %d iterations; the final root-mean-square is: %.1f", step, rms);
	// release point_array parr
	for (int i = 0; i < k; i++) {
		free(parr[i]);
		free(parr);
	}

}




int main(int argc, char** argv)
{


	// nRows will hold how many rows of data there are, nCols holds the number of
	// columns (attributes.) Do not change these variables. k will hold the value of k

   // passed in to the program from the command line.
	int nRows, nCols, k;

	/*
	################################################################################
	## Begininning of provided code to read in file
	################################################################################
	*/

	// Here we check to be sure that the correct number of arguments have been
	// passed in from the command line. The first argument is always the program
	// name. If not, we print and error and return error status.
	if (argc != 3)
	{
		fprintf(stderr, "%s\nYou must pass your data file  and k value "
			"(in that order)as an argument to this program.\n", USAGE_STRING);
		return 1;
	}



	// This section will safely parse the value of k passed in to the program.
	// If the argument cannot be parsed to an integer, or if it is larger than
	// INT_MAX, we error out.
	char* endptr = NULL;
	int base = 10;
	errno = 0;
	long int long_k = strtol(argv[2], &endptr, base);

	// This will trigger if an error was encountered when trying to parse the
	// input, or if the input was not a proper integer (e.g. 124A). This
	// can also trigger if the input is too long to fit even in a long int.
	if ((errno != 0) || (*endptr != '\0'))
	{
		fprintf(stderr, "The input: \"%s\" could not be parsed as an integer.\""
			" \n", argv[2]);
		return 1;
	}
	if ((long_k > INT_MAX) || (long_k <= 0))
	{
		fprintf(stderr, "The k-value input was:\t%ld\n"
			"K must be larger than zero, and no larger than %u.\n", long_k,
			INT_MAX);
		return 1;
	}
	k = (int)long_k;


	// This opens the file for reading. A return value of NULL indicates the file
	// failed to open for some reason, in which case we print out the error and
	// return an error status.
	FILE* infile = fopen(argv[1], "r");
	if (infile == NULL)
	{
		fprintf(stderr, "Could not open the file:\t%s\n", argv[1]);
		perror("Failed to open file");
		return 2;
	}


	// This will read in the number of rows and columns (first line of the file).
	// If it reads fewer than two things, we know the file is incorrect.
	int readIn = fscanf(infile, " %d %d", &nRows, &nCols);

	if (readIn != 2)
	{
		fprintf(stderr, READ_ERROR_STRING);
		fclose(infile);
		return 1;
	}

	// Makes a stack array with nRows rows and nCols columns.
	// May be indexed with data_array[i][j].

	//double data_array[nRows][nCols];
	double** data_array = (double**)malloc(sizeof(double*) * nRows);
	for (int i = 0; i < nRows; i++) {
		data_array[i] = (double*)malloc(sizeof(double) * nCols);
	}

	// This loop reads in the expected number of rows and columns. If it fails to
	// read the expected number, it errors out. This doesn't catch some errors,
	// E.G. too *many* lines in the input file, but you should not be editing
	// those files for the assignment anyway.
	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			readIn = fscanf(infile, " %lf", &data_array[i][j]); // &data_array[i][j];// 
			// printf(" %1f", data_array[i][j]);
			if (!readIn)
			{
				fprintf(stderr, READ_ERROR_STRING);
				return 1;
			}
		}
	}


	// Since we've read in all the data we need, close the file.
	fclose(infile);

	/*
	################################################################################
	## End of code provided for reading file.
	################################################################################
	*/

	/*

	 IMPORTANT!

	 Variables you will need, which *already exist* at this point in the
	 code!

	 nRows: an int containing the number of rows (items) in the dataset

	 nCols:  an int containing the number of columns(attributes per item).


	 k:  an int containing the value of 'k' (number of clusters) passed
	   to the program from the command line.

	 data_array: a 2-dimensional double array which is nRows x nCols.
		This may be indexed like data_array[i][j], where i is
		a row index and j is a column index.

	*/

	// normalize data as z-score
	double* mean_array = (double*)malloc(sizeof(double) * nRows);
	double* Sigma_array = (double*)malloc(sizeof(double) * nRows);
	
	// calculate mean for each attribute j
	for (int j = 0; j < nCols; j++) {
		for (int i = 0; i < nRows; i++) {
			mean_array[j] += data_array[i][j];
		}
		mean_array[j] /= nRows;
	}

	// calculate standard deviation for each attribute j
	for (int j = 0; j < nCols; j++) {
		for (int i = 0; i < nRows; i++) {
			Sigma_array[j] = sqrt((data_array[i][j] - mean_array[j]) * (data_array[i][j] - mean_array[j])/nRows);
		}
	}

	// normalize data_array[i][j]
	for (int j = 0; j < nCols; j++) {
		for (int i = 0; i < nRows; i++) {
			data_array[i][j] = (data_array[i][j] - mean_array[j])/Sigma_array[j];
		}
	}

	Kmeans(k, data_array, nRows, nCols);

	// release data_array

	for (int i = 0; i < nRows; i++) {
		free(data_array[i]);
		free(data_array);
	}

	free(mean_array);
	free(Sigma_array);

	return 0;
}