
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
 * file random.h                                                        *
 * Declarations for psuedo-random number routines                       * 
 ***********************************************************************/

#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

#ifndef RANDOM_H
#define RANDOM_H

class RandK {
  public:
    static double randk() 
			{	return static_cast<double>(rand_int32()) * (1. / 4294967296.); }
		static void setSeed(unsigned long s);

  protected:
		RandK() { if (!init) setSeed(5489UL); init = true; }

  private:
	  static const int n = 624, m = 397; 	// compile time constants

	  static unsigned long state[n]; 			// state vector array
	  static int p; 											// position in state array
	  static bool init; 									// true if init function is called

		static unsigned long rand_int32();									 				// Generate ulong
	  static unsigned long twiddle(unsigned long, unsigned long); // used by gen_state()
	  static void gen_state(); 																	  // generate new state
};

// inline for speed, must therefore reside in header file
inline unsigned long RandK::twiddle(unsigned long u, unsigned long v) 
{
  return (((u & 0x80000000UL) | (v & 0x7FFFFFFFUL)) >> 1)
    ^ ((v & 1UL) ? 0x9908B0DFUL : 0x0UL);
}

inline unsigned long RandK::rand_int32() { // generate 32 bit random int
  if (p == n) gen_state(); // new state vector needed
// gen_state() is split off to be non-inline, because it is only called once
// in every 624 calls and otherwise irand() would become too big to get inlined
  unsigned long x = state[p++];
  x ^= (x >> 11);
  x ^= (x << 7) & 0x9D2C5680UL;
  x ^= (x << 15) & 0xEFC60000UL;
  return x ^ (x >> 18);
}

bool 	 sampleBernoulli(double prob);
double gasdev();
double sampleGaussian(double mean, double variance);

template<class T> void shuffle(vector<T>& vr)
{
  for (unsigned int j = vr.size()-1; j>0; j--)
  {
    double u = RandK::randk();
    int k = int(u*j);
    T temp = vr[j];
    vr[j] = vr[k];
    vr[k] = temp;
  }
}

#endif // RANDOM_H

