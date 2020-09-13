// head of code
#include <stdio.h>
#include <math.h>

// main function
int main() {
	//(1). Input of data pair(mass, maxSpeed) and taking logs; convert to (log(mass), log(maxSpeed)) = (xi, yi)

		// input of data pairs
	double mass[19] = { 4.22E-04, 4.50E-04, 3.90E-04, 0.0138, 5.22E-06, 6.86E-06, 1.30E-06, 1.76E-07, 7.47E-07, 7.89E-08, 2.05E-07, 9.00E-05, 1.70E-04, 0.0015, 4.73E-05, 0.002, 0.002, 6.52E-05, 1.01E-04 };
	double maxSpeed[19] = { 36, 27, 25.92, 36, 6.48, 4.8, 3.6, 3.24, 6.84, 3.06, 4.32, 36, 36, 25.56, 6, 19.08, 18, 10.8, 23.76 };

	// initiate two arrays to save log(mass) and log(maxSpeed)
	double x[19], y[19];
	// convert to log form:
	for (int i = 0; i < 19; i++) {
		x[i] = log(mass[i]);
		y[i] = log(maxSpeed[i]);
	}
	// print arrays x[] and y[]
	printf("log[mass] array is: \n");
	for (int i = 0; i < 19; i++) {
		printf("%.3f\t", x[i]);
	}
	printf("\nlog[maxSpeed] array is: \n");
	for (int i = 0; i < 19; i++) {
		printf("%.3f\t", y[i]);
	}


	//(2) Solving b1 & b2 of matrix b
	//(3) Solving m11, m12, m21, m22 of matrix M
	
	double b1 = 0, b2 = 0;
	double m11 = 0, m12 = 0, m21 = 0, m22 = 0;
	for (int i = 0; i < 19; i++) {
		b1 = b1 + y[i];
		b2 = b2 + x[i] * y[i];
		m11++;
		m12 = m12 + x[i];
		m21 = m21 + x[i];
		m22 = m22 + x[i] * x[i];
	}
	//printf("\n%.3f\t, %.3f\n", b1, b2);

	
	//(4) Solving M(-1) and k = M(-1)b
	double k0, k1;
	k0 = (m22 * b1 - m12 * b2) / (m11 * m22 - m12 * m21);
	k1 = (-m21 * b1 + m11 * b2) / (m11 * m22 - m12 * m21);

	// Print final results k0, k1
	printf("\nThe power law exponent is % .3f and the coefficient is % .3f", k1, k0);

	// Print the original power law form
	double ek0 = exp(k0);
	printf("\nThe original power law form is: maxSpeed = %.3f * mass^%.3f", ek0, k1);

	return 0;
}





