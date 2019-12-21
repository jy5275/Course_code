#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>
#include<math.h>
using namespace std;
int i = 0;
double K[5] = { 0,20000,4700,1100,200 }, c_CuN[5] = { 0 }, c_N = 0;
double Solve(double a, double b, double c) {	// Find positive solution
	double delt, x1, x2;
	delt = b * b - 4 * a*c;
	if (delt < 0) {
		perror("Error1\n");
		_exit(1);
	}
	x1 = (-b + sqrt(delt)) / (2 * a);
	x2 = (-b - sqrt(delt)) / (2 * a);
	if (x2 <= -c_CuN[i + 1] || x2 >= c_N || x2 >= c_CuN[i])
		return x1;
	if (x1 <= -c_CuN[i + 1] || x1 >= c_N || x1 >= c_CuN[i])
		return x2;
	perror("Error2\n");
	_exit(2);
}
int main() {
	int time, N;
	double b, c, x;
	printf("c_Cu2+ = ");
	scanf("%lf", &c_CuN[0]);
	printf("c_NH3 = ");
	scanf("%lf", &c_N);
	printf("How many times do you want to recur? ");
	scanf("%d", &N);
	for (time = 1; time <= N; time++) {
		for (i = 0; i<4; i++) {
			b = -(c_CuN[i] + c_N + 1 / K[i + 1]);
			c = c_CuN[i] * c_N - c_CuN[i + 1] / K[i + 1];
			x = Solve(1, b, c);
			c_N = c_N - x;
			c_CuN[i] = c_CuN[i] - x;
			c_CuN[i + 1] = c_CuN[i + 1] + x;
		}
		printf("%d:[NH3]=%lf [Cu]=%lf [CuN]=%lf [CuN2]=%lf [CuN3]=%lf [CuN4]=%lf\n", 
			time, c_N, c_CuN[0], c_CuN[1], c_CuN[2], c_CuN[3], c_CuN[4]);
	}
	return 0;
}
