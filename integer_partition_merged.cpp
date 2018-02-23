/*THIS FILE IS NOT TO BE USED.  DO NOT USE THIS FILE.


  DO NOT USE THIS FILE.  DO NOT USE THIS FILE.

  This file was made for the purpose of submitting to HackerRank, which
  requires the input to be one file of code.  This file is simply the
  ratio_k_calculator.hpp, ratio_k_calculator.cpp and integer_partition.cpp
  files merged into one and minorly altered such that it compiles. */

  /*Author: Andrew H. Pometta
    Last Updated: 2/23/2018

    This file is the header file for the RatioKCalculator class, which is
    responsible for taking in the relevant a and b numbers and outputting the
    desired k number.  It handles everything in between there.  For details on
    how it is done, see the readme or the relevant .cpp file for implementation.
  */

  #ifndef RATIO_K_CALCULATOR_H
  #define RATIO_K_CALCULATOR_H

  //faster ways of typing long winded variable names.
  typedef long double bdouble;
  typedef unsigned long long int lint;
  #define K_CALC_MINRATIO 1/(1e18 + 1) //based on problem restrictions on a and b
  #define K_CALC_MAXRANGE 67 //can be set to change code-wide maximum 2^t

  class RatioKCalculator {
  private:
    /*range_storage stores the perfection ratios at each integer t.  the index is
      t, the value is the perfection ratio. */
    bdouble range_storage[K_CALC_MAXRANGE];

    /*getRange takes in the desired perfection ratio r_goal, and returns an index
      t.  This index is used in range_storage to find the appropriate range,
      laterneeded when calculating the correct 2^t.  This can be a somewhat
      involvedprocess.  r_goal must be between 0 exclusive and 1 exclusive.  If
      this condition is not met, or the method otherwise fails, a value of 0 is
      returned.  */
    int getRange(bdouble r_goal) const;

    /*Given a range from getRange and the desired perfection ratio,
     getTwoTInRange finds the lowest 2^t value corresponding to a smaller
     perfection ratio thanthe desired one and returns it.  The given ratio r_goal
     must be between 0 exclusive and 1 exclusive, and the range must be an index
     between 1 inclusive and K_CALC_MAXRANGE - 1 exclusive (i.e. it cannot be the
     last element in range_storage).  If these conditions are not met, or the
     method otherwise fails to acquire the desired 2^t, 0 is returned. */
    lint getTwoTInRange(bdouble r_goal, int range) const;

    /*Inline method returning the desired k value from the inputted 2^t value,
    acquired from the method above. */
    lint convertTwoTToK(lint two_t) const { return two_t * (two_t - 1); }

  public:
    /*The constructor takes nothing in, but sets the correct values in
    range_storage. */
    RatioKCalculator();

    /*Given desired perfection ratio, getK with the long double argument uses the
      above methods to calculate the needed K and returns it.  r_goal must be
      between 0 exclusive and 1 exclusive.  If it is not, or the conversion fails
      for any reason, a value of 0 is returned. */
    lint getK(bdouble r_goal) const;

    /*This getK method simply takes in the relevant a and b values, and calls the
      other getK method from the acquired long double.  If a and b are not within
      their proper boundaries of 1 <= a < b <= 1e18, the method returns 0. */
    lint getK(lint a, lint b) const { return getK((bdouble) a / (bdouble) b); }
  };

  #endif

  /*Author: Andrew H. Pometta
    Last Updated: 2/23/2018
  890
    This file implements the RatioKCalculator class defined in
    ratio_k_calculator.hpp.  See the header file for details on the exact purpose
    of this class, or the readme.

    For all functions, a return value of 0 means failure. */

//  #include "ratio_k_calculator.hpp"
  #include <cmath>
  #include <iostream>
  using namespace std;

  /*The public constructor for RatioKCalculator fills the range_storage array
    with the relevant perfection ratios, where the t value is the index. */
  RatioKCalculator::RatioKCalculator(){
    //fill range_storage 0 with 0 to prevent unforeseen access errors, and return
    //the failure result.
    range_storage[0] = 0;
    //fill range storage with preset values
    for (int i = 1; i < K_CALC_MAXRANGE; ++i){
      //ensure i is a bdouble so calculations don't go badly with integer
      //truncation
      bdouble t = (bdouble) i;
      range_storage[i] = t/(exp2(t) - 1);
    }
  }

  /*Given a perfection ratio r_goal, there exists a 2^t in a partition which
    has a corresponding k for which P(k) has a lower perfection ratio.  This
    method finds the range of that 2^t, returning the t value such that, at some
    point between that one and the next, there's a 2^t with a lower perfection
    ratio.  See readme for details on acquiring the range.

    r_goal must be strictly between 0 and 1.  Returns 0 if failure. */
  int RatioKCalculator::getRange(bdouble r_goal) const {
    if (r_goal < K_CALC_MINRATIO || r_goal >= 1) {
      if (r_goal >= 1) std::cerr << "r_goal >= 1 at " << r_goal << std::endl;
      else {
        std::cerr << "r_goal < MINRATIO, which is " << K_CALC_MINRATIO;
        std::cerr << ", r_goal is " << r_goal << std::endl;
      }
      return 0;
    }
    for (int i = 1; i < K_CALC_MAXRANGE; ++i){
      //we're relying on lazy evaluation to not err out on final element in list
      if (i < K_CALC_MAXRANGE - 1 && range_storage[i + 1] > r_goal) continue;
      /*It's possible that the desired 2^k can actually be in the range before
        this, since the perfection ratios at t = i and t = i - 1 might both be
        larger than desired, but due to the decreasing-increasing nature of the
        function of perfection ratios, it could have crossed our desired ratio.

        Simple test: test if the smallest perfection ratio of the previous range
        is less than ours.  If it is, use the previous range.  Else use this one.
      */
      bdouble prev = (i - 1)/(exp2((bdouble)i) - 2);
      if (prev < r_goal) return i - 1;
      else return i;
    } //if for some reason we don't make it, return fail
    std::cerr << "Failed to find range in getRange." << std::endl;
    return 0;
  }

  /*Given a range and a desired perfection ratio, this method returns the
    corresponding lowest 2^t that has a smaller perfection ratio than the
    inputted r_goal.  Returns 0 if failure due to conditions not being met.
    r_goal must be strictly between 0 and 1, and range must be between 1
    inclusive and K_CALC_MAXRANGE - 1 inclusive. */
  lint RatioKCalculator::getTwoTInRange(bdouble r_goal, int range) const {
    if (r_goal <= 0 || r_goal >= 1){
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
    int t = range; //renaming for clarity
    /* Formula for 2^t with exact perfection ratio, where r = ratio:
      2^t = (t/r) + 1
      For details on how this is acquired see readme. */
    bdouble two_t_float = (t/r_goal) + 1;
    /*I did a lot of debugging and found that sometimes, even within the range
      of acceptable a and b values, we simply get an overflow, in either the
      bdouble or the lint, and it wraps back around.  There's nothing that can
      really be done about this other than ignoring it and hoping it doesn't
      matter or finding and using a library that allows >64bit numbers and
      doubles with even more precision - more work than it's worth.

      Basically, just hope that this doesn't screw up. */
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
//  #include "ratio_k_calculator.hpp"
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
