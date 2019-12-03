// This file contains code for timing ops and calculating estimated brute-force times
#include <calc.h>
#include <stdio.h>

/* This function calculates real brute-force times for a particular keysize
* The code iterates over an array of keysizes, and provides the CPU time and number of iterations
* needed to brute-force the keyspace. Data is returned back in the array arguments for times and iterations.
*/
void calc_realtimes(const short keysizes[], double times[], int iterations[], const int length)
{

	// Calculate times to brute force a theoretical keysize for each "real" test
	for (int i = 0; i < length; i++)
	{
		iterations[i] = pow_two(keysizes[i]);
		times[i] = time_bruteforce(iterations[i]);
	}
}

/* This function calculates a set of estimated brute force times for different keysizes
* It iterates over an array of keysizes, and provides estimated CPU time and number of iterations
* needed to brute-force the keyspace. Data is returned back in the array arguments for times and iterations.
*/
void calc_esttimes(const short keysizes[], double times[], double iterations[], const int length, double avg_time)
{
	for (int i = 0; i < length; i++)
	{
		iterations[i] = pow_two_double(keysizes[i]);
		times[i] = time_bruteforce_est(iterations[i], avg_time);
	}
}

/* This function calculates the CPU time for a brute force attack, given the number of iterations */
double time_bruteforce(int iterations)
{
	clock_t start;
	clock_t end;
	double calc_time;
	
	start = clock();
	for (int i = 0; i < iterations; i++)
	{
		generate_bitcoin_keypair();
	}
	end = clock();

	calc_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	return calc_time;
}

/* This function estimates the time needed to bruteforce a particular keysize
* It takes the number of iterations required and an average time and returns
* the estimated brute-force time in seconds
*/
double time_bruteforce_est(double iterations, double avg_time)
{
	double calc_time = 0.0;

	calc_time = iterations * avg_time;
	return calc_time;
}

/* This function calculates a power of two for an integer.
* It uses the left-shift operator for efficiency.
*/
int pow_two(int exponent)
{
	int result = 1;

	result = result << exponent;
	return result;
}

/* This function calculates a power of two for a double
* This will be used to calculate the required brute-force iterations for keysizes
* that exceed the available integer size, since doubles can store much larger values.
* This will use multiplication, as bit-shifting is an invalid/undefined operation on a double
*/
double pow_two_double(int exponent)
{
	double result = 1;

	for (int i = 0; i < exponent; i++)
	{
		result = result * 2;
	}

	return result;
}

/* This function calculates the average time for one keypair generation operation
* (privkey -> pubkey -> base58 encoding), given a data set of iterations and times
* for multiple keysizes
*/
double average_optime(int iterations[], double times[], int length)
{
	double sum_optimes = 0.0;
	for (int i = 0; i < length; i++)
	{
		sum_optimes += optime(iterations[i], times[i]);
	}

	double average_optime = sum_optimes / length;
	return average_optime;
}

/* Returns the amount of time for one keypair generation operation (privkey -> pubkey -> base58 encoding),
* Given the number of iterations (total ops) and the total time taken for all iterations
*/
double optime(int iterations, double time)
{
	double optime = time / iterations;
	return optime;
}
