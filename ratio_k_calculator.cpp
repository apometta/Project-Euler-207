/*Author: Andrew H. Pometta
  Last Updated: 2/23/2018
890
  This file implements the RatioKCalculator class defined in
  ratio_k_calculator.hpp.  See the header file for details on the exact purpose
  of this class, or the readme.

  For all functions, a return value of 0 means failure. */

#include "ratio_k_calculator.hpp"
#include <cmath>
#include <iostream>
using namespace std;

/*The public constructor for RatioKCalculator fills the range_storage array
  with the relevant perfection ratios, where the t value is the index. */
RatioKCalculator::RatioKCalculator(){
  //fill range_mins[0] with 0 to prevent unforeseen access errors, and return
  //the failure result.
  range_mins[0] = 0;
  //fill range storage with preset values
  for (int i = 1; i < K_CALC_MAXRANGE; ++i){
    //ensure i is a bdouble so calculations don't go badly with integer
    //truncation
    bdouble t = (bdouble) i;
    range_mins[i] = t/(exp2(t+1) - 2);
    // std::cout << "range_mins[" << i << "] = " << range_mins[i] << std::endl;
  }
}

/*Given a perfection ratio r_goal, there exists a 2^t in a partition which
  has a corresponding k for which P(k) has a lower perfection ratio.  This
  method finds the range of that 2^t, returning the t value such that, at some
  point between that one and the next, there's a 2^t with a lower perfection
  ratio.  See readme for details on acquiring the range.

  r_goal must be strictly between 0 and 1.  Returns 0 if failure. */
int RatioKCalculator::getRange(bdouble r_goal) const {
  if (r_goal < K_CALC_MINRATIO || r_goal > 1) {
    if (r_goal >= 1) std::cerr << "r_goal > 1 at " << r_goal << std::endl;
    else {
      std::cerr << "r_goal < MINRATIO, which is " << K_CALC_MINRATIO;
      std::cerr << ", r_goal is " << r_goal << std::endl;
    }
    return 0;
  }
  //Find the range by going through the minimums and picking the first one.
  for (int i = 1; i < K_CALC_MAXRANGE; ++i){
    if (range_mins[i] < r_goal) return i;
  }
  std::cerr << "Failed to find range in getRange." << std::endl;
  return 0;
}

/*Given a range and a desired perfection ratio, this method returns the
  corresponding lowest 2^t that has a smaller perfection ratio than the
  inputted r_goal.  Returns 0 if failure due to conditions not being met.
  r_goal must be strictly between 0 and 1, and range must be between 1
  inclusive and K_CALC_MAXRANGE - 1 inclusive. */
lint RatioKCalculator::getTwoTInRange(bdouble r_goal, int range) const {
  if (r_goal <= 0 || r_goal > 1){
    std::cerr << "Error: r_goal of " << r_goal << " not within acceptable ";
    std::cerr << "boundaries of 0 and 1." << std::endl;
    return 0;
  }
  if (range < 1 || range >= K_CALC_MAXRANGE){
    std::cerr << "Error: range of " << range << " not within acceptable ";
    std::cerr << "boundaries of 1 and " << K_CALC_MAXRANGE - 1 << ".";
    std::cerr << std::endl;
    return 0;
  }
  bdouble t = (bdouble) range; //renaming for clarity
  /* Formula for 2^t with exact perfection ratio, where r = ratio:
    2^t = (t/r) + 1
    For details on how this is acquired see readme. */
  bdouble two_t_float = (t/r_goal) + 1;
  lint two_t = (lint)two_t_float;
  /*Nonetheless we add one more to our 2^t.  The reason for this is as follows:
    We need the first 2^t with a perfection ratio LESS THAN the desired
    ratio inputted, the goal ratio.  That means the 2^t we want should be as
    minimally higher as possible of the above calculated one.  Now when we
    performed that calculation, one of two things happened:
      1. The 2^t calculation returned an integer exactly.  Since this has the
         exact perfection ratio that we need to beat, we add one to 2^t we
         got so that we can go below it.
      2. The 2^t calculation returned a decimal number, which was rounded down
         when the number was casted as a lint.  In this case, we add one to
         2^t.
    In either event, we must add one to 2^t for the right one.  The last
    caveat that must be considered is that the 2^t returned is the lowest
    perfection ratio in the range that's exactly equal to the goal ratio, and
    adding one to it will only increase it and return a wrong answer.  However,
    the checks done in getRange ensure that this doesn't happen.

    Basically, just leave the increment there. */
  two_t++;
  return two_t;
}

/*Takes in the bdouble r_goal and returns the k value corresponding to the
  correct answer.  Just calls the other methods.  Returns 0 on failure. */
lint RatioKCalculator::getK(bdouble r_goal) const {
  if (r_goal < K_CALC_MINRATIO || r_goal > 1){
    std::cerr << "Error: r_goal of " << r_goal << " not within acceptable";
    std::cerr << " boundaries of 0 and 1." << std::endl;
    return 0;
  }
  //The monster call.  If 0 is returned at any method, the whole thing
  //properly returns 0.
  return convertTwoTToK(getTwoTInRange(r_goal, getRange(r_goal)));
}
