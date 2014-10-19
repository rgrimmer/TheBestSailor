/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 */

#pragma once

class Rand
{
public:

	/**
	 * Default constructor
	 */
	inline explicit Rand (unsigned int seed)
	{
		m_next = seed;
		computeNext();
	}

	/**
	 * Return a pseudo-random int between 0 and MAX_INT
	 */
	inline unsigned int getNextInt (void)
	{
		computeNext();
		return((unsigned int)(m_next >> 16));
	}

	/**
	 * Return a pseudo-random int between 0 and max (excluded)
	 */
	inline unsigned int getNextInt (unsigned int max)
	{
		return(getNextInt() % max);
	}

	/**
	 * Return a pseudo-random int between min and max (excluded)
	 */
	inline int getNextInt (int min, int max)
	{
		return((int)(getNextInt() % (unsigned int)(max - min)) + min);
	}

	/**
	 * Return a pseudo-random float between 0 and 1
	 */
	inline float getNextFloat (void)
	{
		return(getNextInt() / (float)(0xFFFFFFFF));
	}

	/**
	 * Return a pseudo-random float between 0 and max
	 */
	inline float getNextFloat (float max)
	{
		return(getNextFloat() * max);
	}

	/**
	 * Return a pseudo-random float between min and max
	 */
	inline float getNextFloat (float min, float max)
	{
		return((getNextFloat() * (max - min)) + min);
	}

private:

	/**
	 * Compute next random number using LCG
	 */
	inline void computeNext (void)
	{
		// X(n+1) = (a X(n) + c) % m

		// a, the "multiplier" 	=> 25214903917
		// c, the "increment"  	=> 11
		// m the "modulus" 		=> 2^48

		m_next = (unsigned long long int)(25214903917LL * m_next + 11LL) % (unsigned long long int)(1LL << 48);
	}

	unsigned long long int m_next;
	// TODO static assert sizeof(m_next) == 8
};