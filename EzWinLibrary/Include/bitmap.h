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
// $Revision: 1.4 $
// $Name: $
//
//**************************************************************************

#ifndef BITMAP_H
#define BITMAP_H

// MSVC++ 4.0 does not have a string class
#ifdef MSVC40
#include "dstring.h"
#else
#include <string>
#endif

#include "ezwin.h"

using namespace std;

// Possible bitmap status
typedef enum { NoBitMap, BitMapOkay, NoWindow } BitMapStatus;

// BitMap: user class for manipulating (load, draw, erase, & isinside) bitmaps

class BitMap {
	public:
		BitMap(SimpleWindow *DisplayWindow);
		BitMap(SimpleWindow& DisplayWindow);
		BitMap();

		BitMapStatus Load(const char *Filename);
		BitMapStatus Load(const string &Filename);
		void SetWindow(SimpleWindow &Window);

		bool Draw();
		bool Erase();
		bool IsInside(const Position &AtPosn) const;

		BitMapStatus GetStatus() const;

		// it is very convenient to get the individual components of
		// (X,Y) for position and size with direct accessor members
		float GetXPosition() const;
		float GetYPosition() const;
		float GetWidth() const;
		float GetHeight() const;
		void GetSize(float &Width, float &Height) const;
		void SetPosition(const Position &NewPosn);

		// get position and bitmap size as points (X,Y) or
		// (Width, Height)
		Position GetPosition() const;
	private:
		BMBuffer *Bmp;
		BitMapStatus Status;
		Position Posn;
		SimpleWindow *W;
};

#endif
