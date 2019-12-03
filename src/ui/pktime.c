/* This file contains the main command-line UI for the program
*
* Author: Josh McIntyre
*/
#include "pktime.h"
#include "calc.h"

int main()
{
	// Calculate times to brute force a theoretical keysize for each "real" test
	printf("Calculating some real and estimated brute force times...please wait\n");

	double times[REAL_KEYSIZES_LENGTH];
	int iterations[REAL_KEYSIZES_LENGTH];
	calc_realtimes(REAL_KEYSIZES, times, iterations, REAL_KEYSIZES_LENGTH);
	
	// Get the average optime for the real tests
	double avg_optime = average_optime(iterations, times, REAL_KEYSIZES_LENGTH);

	// Get the estimated optime for large keysizes
	double etimes[EST_KEYSIZES_LENGTH];
	double eiterations[EST_KEYSIZES_LENGTH];
	calc_esttimes(EST_KEYSIZES, etimes, eiterations, EST_KEYSIZES_LENGTH, avg_optime);
	
	// Display the final calculations
	printf("Average optime for one keypair check: %f\n", avg_optime);
	
	for (int i = 0; i < REAL_KEYSIZES_LENGTH; i++)
	{
		printf("Real time to bruteforce %d bit keysize: %f seconds with %d iterations\n", REAL_KEYSIZES[i], times[i], iterations[i]);
	}

	for (int i = 0; i < EST_KEYSIZES_LENGTH; i++)
	{
		if (etimes[i] < SECONDS_PER_MINUTE)
		{
			printf("Est. time to bruteforce %d bit keysize: %f seconds with %.0f iterations\n", EST_KEYSIZES[i], etimes[i], eiterations[i]);
		}
		else if (etimes[i] < SECONDS_PER_HOUR)
		{
			printf("Est. time to bruteforce %d bit keysize: %f minutes with %.0f iterations\n", EST_KEYSIZES[i], etimes[i] / SECONDS_PER_MINUTE, eiterations[i]);
		}
		else if (etimes[i] < SECONDS_PER_DAY)
		{
			printf("Est. time to bruteforce %d bit keysize: %f hours with %.0f iterations\n", EST_KEYSIZES[i], etimes[i] / SECONDS_PER_HOUR, eiterations[i]);
		}
		else if (etimes[i] < SECONDS_PER_YEAR)
		{
			printf("Est. time to bruteforce %d bit keysize: %f days with %.0f iterations\n", EST_KEYSIZES[i], etimes[i] / SECONDS_PER_DAY, eiterations[i]);
		}
		else if (etimes[i] < SECONDS_PER_YEAR * 100000)
		{
			printf("Est. time to bruteforce %d bit keysize: %f years with %E iterations\n", EST_KEYSIZES[i], etimes[i] / SECONDS_PER_YEAR, eiterations[i]);
		}
		else
		{
			printf("Est. time to bruteforce %d bit keysize: %E years with %E iterations\n", EST_KEYSIZES[i], etimes[i] / SECONDS_PER_YEAR, eiterations[i]);
		}
	}

}

