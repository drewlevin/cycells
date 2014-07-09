
/************************************************************************
 * 									*
 * Copyright (C) 2004  Christina Warrender				*
 * 									*
 * This file is part of CyCells.					*
 *									*
 * CyCells is free software; you can redistribute it and/or modify it 	*
 * under the terms of the GNU General Public License as published by	*
 * the Free Software Foundation; either version 2 of the License, or	*
 * (at your option) any later version.					*
 *									*
 * CyCells is distributed in the hope that it will be useful,		*
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	*
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	*
 * GNU General Public License for more details.				*
 *									*
 * You should have received a copy of the GNU General Public License	*
 * along with CyCells; if not, write to the Free Software Foundation, 	*
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA	*
 *									*
 ************************************************************************/
/************************************************************************
 * file random.cc                                                       *
 * Routines for random number generation and sampling                   * 
 ************************************************************************/

#include <math.h>
#include "random.h"

// Initialize static variables
unsigned long RandK::state[n] = {0x0UL};
int 					RandK::p 				= 0;
bool 					RandK::init 		= false;

/************************************************************************
 * gen_state																														*
 *    Generates a new state vector.																			*
 ************************************************************************/
void RandK::gen_state() 
{ 
  for (int i = 0; i < (n - m); ++i)
    state[i] = state[i + m] ^ twiddle(state[i], state[i + 1]);
  for (int i = n - m; i < (n - 1); ++i)
    state[i] = state[i + m - n] ^ twiddle(state[i], state[i + 1]);
  state[n - 1] = state[m - 1] ^ twiddle(state[n - 1], state[0]);
  p = 0; // reset position
}

/************************************************************************
 * setSeed																															*
 *    Initializes the generator with a new seed.												*
 *                                                                      *
 * Parameters:                                                          *
 *    unsigned long s:	the new seed																		*
 ************************************************************************/
void RandK::setSeed(unsigned long s) 
{  
  state[0] = s & 0xFFFFFFFFUL; // for > 32 bit machines
  for (int i = 1; i < n; ++i) {
    state[i] = 1812433253UL * (state[i - 1] ^ (state[i - 1] >> 30)) + i;
    state[i] &= 0xFFFFFFFFUL; // for > 32 bit machines
  }
  p = n;
}

/************************************************************************
 * sampleBernoulli                                                      *
 *    Routine to 'flip a weighted coin' - gets a random uniform deviate *
 * and compares it to an input probability to determine whether an      *
 * with that probability of occurence should happen.                    *
 * Random number generator (randk) should be initialized before calling *
 * sampleBernoulli.                                                     *
 *                                                                      *
 * Parameters:                                                          *
 *    double prob:	the probability of 'success'                        *
 *                                                                      *
 * Returns:  boolean - true if random number is < prob                  *
 ************************************************************************/
bool sampleBernoulli(double prob)
{
  double x = RandK::randk();
  return (x<prob);
}

/************************************************************************
 * gasdev                                                               *
 *    Routine to return a normally distributed variate with zero        *
 * mean and unit variance.  Based on Numerical Recipes routine -        *
 * This version does not take a seed - random number generator (randk)  *
 * should be initialized before calling gasdev.                         *
 *                                                                      *
 * Parameters:  none                                                    *
 *                                                                      *
 * Returns:  value with specified distribution                          *
 ************************************************************************/
double gasdev()
{
  static int iset=0;
  static double gset;
  double fac, rsq, v1, v2;
 
  if (iset == 0)		// no deviate already generated
  {
    do { // until get pair in unit circle
      // pick two uniform numbers in the square extending from -1 to + 1 
      // in each direction
      v1=2.0*RandK::randk()-1.0;
      v2=2.0*RandK::randk()-1.0;
      rsq = v1*v1 + v2*v2;
    } while (rsq >= 1.0 || rsq == 0.0);

    fac = sqrt(-2.0*log(rsq)/rsq);

    // Box-Muller transformation gives two deviates, save one
    gset = v1*fac;
    iset = 1;
    return v2*fac;
  }
  else				// use deviate generated last time
  {
    iset = 0;
    return gset;
  }
}

/************************************************************************
 * sampleGaussian                                                       *
 *    Routine to return a normally distributed variate with arbitrary   *
 * mean and variance.  Just uses gasdev and adjusts deviate to fit      *
 * specified distribution.						*
 *                                                                      *
 * Parameters:                                                          *
 *   double mean, variance:	describes sample distribution           *
 *                                                                      *
 * Returns:  value with specified distribution                          *
 ************************************************************************/
double sampleGaussian(double mean, double variance)
{
  if (variance == 0)
    return mean;
  else
    // get deviate from standard Gaussian, convert
    return variance*gasdev() + mean;
}


