/*This file, written by Andrew H. Pometta on 2/21/2018, is a C++ program for 
solving Project Euler problem #207, found on HackerRank at:
https://www.hackerrank.com/contests/projecteuler/challenges/euler207

This is the C++ version, in the hopes that it will go faster.  Please see 
the readme file in this project for more details on the problem, plan, 
solution, etc. */

using namespace std;

//Returns if the inputted integer is a power of 2.  If the integer bitwise
//ANDed with itself minus 1 is 0, that means that in binary it's a 1 followed
//by some amount of 0's - a power of 2.
#define lint unsigned long long;
bool power_of_2(lint n){
  return n & (n-1) == 0;
}

int main(){
  //test power_of_2
  cout << "power_of_2 tests:" << endl;
  cout << "1: " << power_of_2(1) << endl;
  cout << "2: " << power_of_2(2) << endl;
  cout << "3: " << power_of_2(3) << endl;
  cout << "4: " << power_of_2(4) << endl;
  cout << "5: " << power_of_2(5) << endl;
  cout << "8: " << power_of_2(8) << endl;
  cout << "10: " << power_of_2(10) << endl;
  cout << "16: " << power_of_2(16) << endl;

  //test I/O
  lint a, b, c;
  cin >> a;
  cin >> b >> c;
  cout << "a = " << a << endl;
  cout << "b, c = " << b << ", " << c << endl;
  return 0;
}
