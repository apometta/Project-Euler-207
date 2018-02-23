/*This file, written by Andrew H. Pometta on 2/21/2018, is a C++ program for 
solving Project Euler problem #207, found on HackerRank at:
https://www.hackerrank.com/contests/projecteuler/challenges/euler207

This is the C++ version, in the hopes that it will go faster.  Please see 
the readme file in this project for more details on the problem, plan, 
solution, etc. */

#include <iostream>
#include <cstdlib>
#include "ratio_k_calculator.hpp"
using namespace std;

int main(){
  RatioKCalculator calc;
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i){
    lint a, b;
    cin >> a >> b;
    lint k = calc.getK(a, b);
    if (k == 0){
      cerr << "K acquisition failed at a = " << a << ", b = " << b << endl;
      return EXIT_FAILURE;
    }
    cout << k << endl;
  }
  return EXIT_SUCCESS;
}

