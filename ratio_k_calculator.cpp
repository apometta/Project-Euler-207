/*Implementation file for ratio k calculator class.  Update comments later.
  Code by Andrew H. Pometta.  */

#include "ratio_k_calculator.hpp"
#include <cmath>
#include <cassert>
using namespace std;
#define MINRATIO range_storage[0]

//constructor, check for range error when running
RatioKCalculator::RatioKCalculator(){
  //the 0th slot stores the lowest possible ratio.  if we get one with less
  //than this than we err out.
  bdouble max_two_t = exp2(bdouble(60));
  range_storage[0] = 59/(max_two_t - 1);
  //fill range storage with preset values
  for (int i = 1; i < 61; ++i){
    //ensure i is a bdouble so calculations don't go badly with rounding
    bdouble t = (bdouble) i;
    range_storage[i] = t/(exp2(t) - 1);
  }
  assert(range_storage[1] == 1);
  //debug
  for (int i = 1; i < 5; ++i) cout << "range_storage[" << i << "] = " <<
				range_storage[i] << endl;
}

int getRange(bdouble r_goal){
  //desired ratio can't be 1, or less than the best we can do
  if (r_goal < MINRATIO || r_goal >= 1) return 0;
  for (int i = 1; i < 60; ++i){
    if (range_storage[i + 1] > r_goal) continue;
    else if (range_storage[i] == r_goal) return i - 1;
    else if (range_storage[i] < r_goal) return i;
  }
  return 0;
}
