/*This file, written by Andrew H. Pometta on 2/21/2018, is a C++ program for 
solving Project Euler problem #207, found on HackerRank at:
https://www.hackerrank.com/contests/projecteuler/challenges/euler207

This is the C++ version, in the hopes that it will go faster.  Please see 
the readme file in this project for more details on the problem, plan, 
solution, etc. */

#include <iostream>
#include <cstdlib>
using namespace std;

//Returns if the inputted integer is a power of 2.  If the integer bitwise
//ANDed with itself minus 1 is 0, that means that in binary it's a 1 followed
//by some amount of 0's - a power of 2.
#define lint unsigned long long
bool power_of_2(lint n){
  return (n & (n-1)) == 0;
}

int main(){
  return 0;
}
