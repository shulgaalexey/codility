// Test Score: 100%

#include <math.h>
int solution(int X, int Y, int D) {
	double dif = double(Y - X);
	double dst = dif / D;
	int steps = int(ceil(dst));
	return steps;
}
