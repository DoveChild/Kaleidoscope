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
// Class Position interface


#ifndef POSITION_H
#define POSITION_H

class Position {
	public:
		Position(const float x = 0.0, const float y = 0.0);
		float GetXDistance() const;
		float GetYDistance() const;
		void SetXDistance(const float x);
		void SetYDistance(const float y);

	private:
		float XDistance;
		float YDistance;
};

Position operator+(const Position &x, const Position &y);
Position operator-(const Position &x, const Position &y);
#endif

