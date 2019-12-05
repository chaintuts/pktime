// This file contains code for timing ops and calculating estimated brute-force times
#include <time.h>
#include <cryptops.h>

void calc_realtimes(const short keysizes[], double times[], int iterations[], const int sizes);
void calc_esttimes(const short keysizes[], double times[], double iterations[], const int length, double avg_time);
double time_bruteforce(int iterations);
double time_bruteforce_est(double iterations, double avg_time);
int pow_two(int exponent);
double pow_two_double(int exponent);
double average_optime_from_opssec(double ops_per_sec);
double average_optime(int iterations[], double times[], int length);
double optime(int iterations, double time);
