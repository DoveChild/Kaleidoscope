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
// Class Shape interface


#ifndef SHAPE_H
#define SHAPE_H
#include "wobject.h"
//
// Shape - base class for shapes that can be displayed
//         in a window. Shape is derived from
//         WindowObject
//
class Shape : public WindowObject {
	public:
		Shape(SimpleWindow &Window, const Position &p,
		 const color &c = Red);
		color GetColor() const;
		bool HasBorder() const;
		void SetColor(const color &c);
		void SetBorder();
		void ClearBorder();
		virtual void Draw() = 0;
		virtual void Erase() = 0;
	private:
		color Color;
		bool Border;
};
#endif

