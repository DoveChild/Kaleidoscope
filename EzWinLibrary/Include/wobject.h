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
// $Revision: 1.3 $
// $Name: $
//
//**************************************************************************
// Class WindowObject interface


#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H
#include "ezwin.h"
//
// WindowObject - base class for objects that can be
//                displayed in a window
//
class WindowObject {
   public:
      WindowObject(SimpleWindow &w, const Position &p);
      Position GetPosition() const;
      void GetPosition(float &x, float &y) const ;
      SimpleWindow &GetWindow() const;
      void SetPosition(const Position &p);
      void SetPosition(float x, float y);
   private:
      SimpleWindow &Window;
      Position Location;
};

#endif

