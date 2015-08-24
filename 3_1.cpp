// 3.1
// CountDiv
// Compute number of integers divisible by k in range [a..b].
// Test Score: 100%
#include <iostream>
#include <math.h>
using namespace std;

int solution(int A, int B, int K) {
	/*int a = A / K;
	  int b = B / K;
	  int ret = b - a;
	  if((A > K) && ((A % K) == 0))
	  ret ++;
	  cout << A << "," << B << "," << K << ":" << ret << endl;
	  return ret;*/
	int shift = K - (A % K);
	if(shift == K)
		shift = 0;
	int A1 = A + shift;
	if(A1 > B)
		return 0;
	int dif = B - A1;
	int ret = dif / K + 1;
	//cout << A << "," << B << "," << K << ":" << ret << endl;
	return ret;

	/*int ret = 0;
	  if((A % K) == 0)
	  ret ++;

	  int dif = B - A;
	  if(dif == 0)
	  return ret;

	  ret += dif / K;
	  cout << A << "," << B << "," << K << ":" << ret << endl;
	  return ret;*/



	/*int ret = (B - A) / K;
	  if(A == B) {
	  ret = max(ret - 1, 0);
	  if((A % K) == 0)
	  ret ++;
	  } else {
	  ret = max(ret - 1, 0);
	  if((A % K) == 0)
	  ret ++;
	  if((B % K) == 0)
	  ret ++;
	  }
	  cout << A << "," << B << "," << K << ":" << ret << endl;
	  return ret;*/
}

int main(void) {
	if(solution(6, 11, 2) != 3) cout << "ERROR1" << endl;
	if(solution(0, 0, 1) != 1) cout << "ERROR2" << endl;
	if(solution(0, 1, 2) != 1) cout << "ERROR3" << endl;
	if(solution(6, 12, 2) != 4) cout << "ERROR4" << endl;
	if(solution(2, 6, 3) != 2) cout << "ERROR5" << endl;
	if(solution(0, 0, 11) != 0) cout << "ERROR6" << endl;
	if(solution(10, 10, 20) != 0) cout << "ERROR7" << endl;
	return 0;
}
