/*
 * utils.cpp
 *
 *  Created on: 8 déc. 2011
 *      Author: clement
 */
#include <stdlib.h>

#include "includes/utils.h"
#include "includes/types.h"

/**
 * Generate pseudo-random unsigned integer between in [min, max]
 */
uint
randMinMax(uint min, uint max)
{
  if (min >= max)
    return min;

  ++max;
  return (rand() % (max - min)) + min;
}


int
min(int a, int b)
{
  return (a < b)? a : b;
}

int
max(int a, int b)
{
  return (a > b)? a : b;
}

