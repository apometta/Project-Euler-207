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
#define K_CALC_MAXRANGE 65 //can be set to change code-wide maximum 2^t

class RatioKCalculator {
private:
  /*range_mins is, given a corresponding range, the minimum perfection ratio
    possible within that range.  Useful for finding the range for a 2^t. */
  bdouble range_mins[K_CALC_MAXRANGE];

  /*getRange takes in the desired perfection ratio r_goal, and returns an index
    t.  This index is used in range_storage to find the appropriate range,
    laterneeded when calculating the correct 2^t.  This can be a somewhat
    involvedprocess.  r_goal must be between 0 exclusive and 1 inclusive.  If
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
    between 0 exclusive and 1 inclusive.  If it is not, or the conversion fails
    for any reason, a value of 0 is returned. */
  lint getK(bdouble r_goal) const;

  /*This getK method simply takes in the relevant a and b values, and calls the
    other getK method from the acquired long double.  If a and b are not within
    their proper boundaries of 1 <= a < b <= 1e18, the method returns 0. */
  lint getK(lint a, lint b) const { return getK((bdouble) a / (bdouble) b); }
};

#endif
