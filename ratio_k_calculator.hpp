/*This file, written by Andrew H. Pometta, is the header file for the integer 
  partition program.  Temp comment until everything is set up: insert details 
  here. */

#ifndef RATIO_K_CALCULATOR_H
#define RATIO_K_CALCULATOR_H

typedef long double bdouble;
typedef unsigned long long int lint;

/*Class for calculating smallest viable k from given ratio.  Complete later. */
class RatioKCalculator {
private:
  bdouble range_storage[61]; //double array for storing
  //range checkpoints, the 0'th slot is the max

  //get range of riven ratio with linear search, 0 on fail
  int getRange(bdouble r_goal) const;
  //get the 2t from a range.  return 0 if not found, 1 if
  //range invalid
  lint getTwoTInRange(bdouble r_goal, int range) const;
  //get the K value from a two_t value
  lint convertTwoTToK(lint two_t) const {return two_t * (two_t - 1);}

public:
  //constructor
  RatioKCalculator();
  //get K given ratio
  lint getK(bdouble r_goal) const;
  //get K given to unsigned long long ints
  lint getK(lint a, lint b) const { return getK((bdouble) a / (bdouble) b); }
  void test() const; //for testing, remove later
};

#endif
