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
// $Name: E2 $
//
//**************************************************************************
// Class Label interface


#ifndef LABEL_H
#define LABEL_H

// MSVC++ 4.0 does not support the string class
#ifdef MSVC40
#include "dstring.h"
#else
#include <string>
#endif

#include "shape.h"

using namespace std;

class Label : public WindowObject 
{
public:

	Label(SimpleWindow &Window, const Position &p,
		 const string &Text, const color &TextColor = Black,
         const color &c = White);
	
	Label(SimpleWindow &Window, float XCoord, float YCoord,
		 const string &Text, const color &TextColor = Black,
         const color &c = White);

	Label(SimpleWindow &Window, const Position &p,
	     const char *Text, const color &TextColor = Black,
         const color &c = White);

	Label(SimpleWindow &Window, float XCoord, float YCoord,
		 const char *Text, const color &TextColor = Black,
         const color &c = White);

    ~Label();

	color GetColor() const;
	void SetColor(const color &c);
	  
	void Draw();
    void Erase();
    
	//Add by LeiYM 2014-03-31
	void SetFont(const string& name, int siz);

private:
	color  TextColor;
    color  BackgroundColor;
    string Text;

	//Add by LeiYM 2014-03-31
	string fontName;
	int    textSize;
};
#endif

