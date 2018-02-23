/*Implementation file for ratio k calculator class.  Update comments later.
  Code by Andrew H. Pometta.  */

#include "ratio_k_calculator.hpp"
#include <cmath>
#include <cassert>
#include <iostream>
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
}

//return the lower bound of the t range our goal ratio is in.
int RatioKCalculator::getRange(bdouble r_goal) const {
  //desired ratio can't be 1, or less than the best we can do
  if (r_goal < MINRATIO || r_goal >= 1) return 0;
  for (int i = 1; i < 60; ++i){
    if (range_storage[i + 1] > r_goal) continue;
    //i should be our range, but we ensure manually that it isn't before,
    //which occasionally is the case.  see readme
    bdouble prev = (i - 1)/(exp2((bdouble)i) - 2);
    if (prev < r_goal) return i - 1;
    //it could also be the case that the very last viable 2^t has a ratio exactly
    //equal to r_goal, which is bad.  If that's the case, we must use the next range
    bdouble next = i/(exp2((bdouble)(i + 1)) - 2);
    if (next == r_goal){
      if (i < 59) return i + 1; //sanity check that we don't return 60
      else return 0;
    }
    return i;
  } //if for some reason we don't make it, return fail
  return 0;
}

//get the right TwoT from the range.  Assumes the range is correct.
lint RatioKCalculator::getTwoTInRange(bdouble r_goal, int range) const {
  //it should be noted here that, assuming r_goal meets the necessary requirements of
  //0 < r_goal < 1 and the rest of the program is working properly, that
  //1 < range < 60.
  if (0 < r_goal && r_goal < 1 && range < 1 && range < 60) return 0;
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
