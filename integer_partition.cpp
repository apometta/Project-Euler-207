/*Author: Andrew H. Pometta
  Last updated: 2/23/2018

  This file is the main file for the Project Euler #207 project.  It uses
  the RatioKCalculator found in ratio_k_calculator.hpp and implemented in
  ratio_k_calculator.cpp.  The program takes in FROM THE STANDARD INPUT
  (i.e. NOT from an argument file, due to the specifications in the problem)
  a number on a line corresponding to a list of queries, followed by that
  number of queries on each line.  Each query has two integers a and b.
  For details, see the readme or the problem page at:
  https://www.hackerrank.com/contests/projecteuler/challenges/euler207 */

#include <iostream>
#include <cstdlib>
#include "ratio_k_calculator.hpp"
using namespace std;

int main(){
  RatioKCalculator calc;
  /*Since the problem doesn't test for checking input formatting and is really
    clear about it, I don't do any checking for proper formatting.  Don't run
    the program on one that is not properly formatted, lest it run until
    manually terminated.  I may add checks later. */
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
