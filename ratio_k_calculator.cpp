/*Author: Andrew H. Pometta
  Last Updated: 2/23/2018

  This file implements the RatioKCalculator class defined in ratio_k_calculator.hpp.
  See the header file for details on the exact purpose of this class, or the readme.

  For all functions, a return value of 0 means failure. */

#include "ratio_k_calculator.hpp"
#include <cmath>
#include <cassert>
#include <iostream> //debugging, delete later
using namespace std;

//constructor, check for range error when running
RatioKCalculator::RatioKCalculator(){
  range_storage[0] = 0; //keeping this filled prevents unassigned value access errors
                        //and returns 
  //fill range storage with preset values
  for (int i = 1; i < K_CALC_MAXRANGE; ++i){
    //ensure i is a bdouble so calculations don't go badly with rounding
    bdouble t = (bdouble) i;
    range_storage[i] = t/(exp2(t) - 1);
  }
}

//return the lower bound of the t range our goal ratio is in.
int RatioKCalculator::getRange(bdouble r_goal) const {
  //desired ratio can't be 1, or less than the best we can do
  if (r_goal < K_CALC_MINRATIO || r_goal >= 1) {
    if (r_goal >= 1) std::cerr << "r_goal >= 1 at " << r_goal << std::endl;
    else {
      std::cerr << "r_goal < MINRATIO, which is " << K_CALC_MINRATIO;
      std::cerr << ", r_goal is " << r_goal << std::endl;
    }
    return 0;
  }
  for (int i = 1; i < K_CALC_MAXRANGE - 1; ++i){ //will not operate on last element
    if (range_storage[i + 1] > r_goal) continue;
    //i should be our range, but we ensure manually that it isn't before,
    //which occasionally is the case.  see readme
    bdouble prev = (i - 1)/(exp2((bdouble)i) - 2);
    if (prev < r_goal){
      std::cout << "returning successfully in getRange with i decrement, i = ";
      std::cout << i << std::endl;
      return i - 1;
    }
    //it could also be the case that the very last viable 2^t has a ratio exactly
    //equal to r_goal, which is bad.  If that's the case, we must use the next range
    bdouble next = i/(exp2((bdouble)(i + 1)) - 2);
    if (next == r_goal){
      if (i < K_CALC_MAXRANGE - 1){
	std::cout << "returning successfully in getRange with i increment, i = ";
	std::cout << i << std::endl;
	return i + 1; //sanity check that we don't return 60
      }
      return 0;
    }
    std::cout << "returning successfully in getRange, i = " << i << std::endl;
    return i;
  } //if for some reason we don't make it, return fail
  std::cerr << "fell out of for loop in getRange." << std::endl;
  return 0;
}

//get the right TwoT from the range.  Assumes the range is correct.
lint RatioKCalculator::getTwoTInRange(bdouble r_goal, int range) const {
  //it should be noted here that, assuming r_goal meets the necessary requirements of
  //0 < r_goal < 1 and the rest of the program is working properly, that
  //1 < range < 60.
  if (0 < r_goal && r_goal < 1 && range < 1 && range >= K_CALC_MAXRANGE - 1) return 0;
  int t = range; //renaming for clarity
  //formula: purity = t/(2^t - 1), we need to find 2^t.  thus:
  //2^t = (t/purity) + 1
  //since r_goal is what we want to become less than, we round up.  if it's exact, we
  //add one.  then find proper ratio and return
  //only caveat is if two_t before the 
  lint two_t = (lint)(t / r_goal) + 1;
  //we add one more because casting as lint either rounds down - meaning we go up one
  //more - or it got us an exact match, and since the desired ratio must be strictly
  //less than r_goal, we need to go up one.
  //the only caveat is if we land two_t exactly on the two_t right before the next
  //pure partition.  however, the getRange checks assure this does not happen
  two_t++;
  return two_t;
}

lint RatioKCalculator::getK(bdouble r_goal) const {
  //the monster call
  return convertTwoTToK(getTwoTInRange(r_goal, getRange(r_goal)));
}
