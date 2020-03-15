//**************************************************************************
//
// Copyright (c) 1997.
//      Richard D. Irwin, Inc.
//
// This software may not be distributed further without permission from
// Richard D. Irwin, Inc.
//
// This software is distributed WITHOUT ANY WARRANTY. No claims are made
// as to its functionality or purpose.
//
// Authors: James P. Cohoon and Jack W. Davidson
// Date: 7/15/96
// $Revision: 1.1 $
// $Name: P2 P1 $
//
//**************************************************************************
// Class Random interface


#ifndef RANDOM_H
#define RANDOM_H
class Random {
	public:
		// default constructor
		Random();
		// constructor for generating from interval (a,b)
		Random(int a, int b, unsigned int seed = 1);
		// mutators
		int Draw();
		unsigned int Randomize();
	protected:
		// mutators
		void SetInterval(int a, int b);
		void SetSeed(unsigned int s);
		// inspectors
		int GetLow();
		int GetHigh();
	private:
		// data members
		int Low;
		int High;
};
#endif

