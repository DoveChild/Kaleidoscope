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
// $Revision: 1.5 $
// $Name: E2 $
//
//**************************************************************************

// 32-bit Version of EzWindows
#ifndef WINAPI_H
#define WINAPI_H
#include <vector>
using namespace std;
#include <windows.h>
#include <string>
#include "position.h"

// Miscellaneous prototypes
bool operator<(const Position &p, const Position &q);
bool operator==(const Position &p, const Position &q);

// d_to_l(): Convert device coordinate (pixels) to logical (centimeters)
float d_to_l(int device_coord);

// l_to_d(): Convert logical coordinate (centimeters) to device
//  coordinate (pixels)
int l_to_d(float logical_coord);

// Randomize(): Initialize random number generator
void Randomize();

// Uniform(): Generate a Uniform number between i and j inclusive
int Uniform(int i, int j);

// GetMilliseconds(): Read the millisecond timer
long GetMilliseconds();

// user functions called at program start-up and termination.

int ApiMain();
int ApiEnd();

class SimpleWindow;
class WindowManager;
class BitMapManager;

// BMBuffer - internally used class that represents a MS Windows bitmap (.BMP)
// that has been loaded into memory as a device independent bitmap.

enum BMBufferStatus { BitMapFailure, BitMapLoaded };

class BMBuffer {

	public:
		BMBuffer(const char *Filename);
		~BMBuffer();
 
		float GetWidth();
		float GetHeight();
		Position GetSize();

		BMBufferStatus GetStatus();

		// let the windows class have direct access to the bitmap
		// structures
		friend SimpleWindow;

	protected:
		HBITMAP create_bitmap(HDC hdc);
		BITMAPFILEHEADER FileHeader;
		int dstatus;
		WORD Width, Height;
		DWORD HeaderSize;
		BYTE *BM;
		BYTE *Bits;
		BITMAPINFOHEADER *Bmi;

	private:
		HGLOBAL hBM;
		BMBufferStatus Status;
};

// a list of allocated bitmaps -- the bitmap pointer serves as the handle
typedef struct BitMapListEntryTag {
	BitMapListEntryTag(BMBuffer *bmp, BitMapListEntryTag *next) :
		Bmp(bmp), Next(next) {};

  	// delete the bitmap itself
	~BitMapListEntryTag()
		{ if (Bmp) delete Bmp; };

	BMBuffer *Bmp;
	BitMapListEntryTag *Next;
} BitMapListEntry;

// BitMapManager - manages the allocation and deallocation of bitmap buffers
class BitMapManager {

	public:
		BitMapManager();
		~BitMapManager();
		BMBuffer *Allocate(const char *Filename);
		void Deallocate(BMBuffer *Bmp);

	private:

		BitMapListEntry *BitMapList;
		int NumAlloc;    // track number allocated
};

// User functions for loading and discarding bitmaps

BMBuffer *LoadBitMap(const char *Filename);
void DiscardBitMap(BMBuffer *Bmp);

// Window - a simple windowing api that hides details of MS Windows,
// X11, or whatever underlying window system.

enum WindowStatus { WindowClosed, WindowOpen, WindowFailure };

// The EzWindows API currently supports 8 colors. These correspond
// to the RGB colors. This should be portable across platforms.

const int MaxColors = 8;
enum color { Black, White, Red, Green, Blue, Yellow, Cyan, Magenta };
extern long ColorTable[];


// callback function pointers

typedef int (*TimerTickCallbackFunction)();
typedef int (*MouseClickCallbackFunction)(const Position &);
typedef int (*RefreshCallbackFunction)();
typedef int (*QuitCallbackFunction)();

// SimpleWindow - a simple API to hide the underlying window system.
class SimpleWindow {
	public:
		SimpleWindow(const char *WindowTitle = "Untitled",
		 float Width = 8.0f, float Height = 8.0f,
		 const Position &WindowPosition = Position(3.0f, 3.0f));
		SimpleWindow(const string &WindowTitle,
		 float Width = 8.0f, float Height = 8.0f,
		 const Position &WindowPosition = Position(3.0f, 3.0f));
		~SimpleWindow();
		SimpleWindow(const SimpleWindow&);
		SimpleWindow operator=(const SimpleWindow&);

		// Window opening and closing.
		// Always open the window before drawing to it!
		WindowStatus Open();
		WindowStatus Close();
		WindowStatus GetStatus() const;

		// Display object members (draw bitmaps, rectangle, etc).
		void DrawBitMap(const Position &UpperLeft, BMBuffer &B);
		void DrawBitMap(const Position &UpperLeft, BMBuffer *B);
		void EraseBitMap(const Position &UpperLeft, BMBuffer &B);
		void EraseBitMap(const Position &UpperLeft, BMBuffer *B);
		void Erase(const Position &UpperLeft, float Width, float Height);
		void RenderRectangle(const Position &UpperLeft,
		 const Position &LowerRight, const color &Color,
		 const bool Border = false);
		void RenderLine(const Position &Base, const Position &Endpoint,
		const color &Color, const float LineWidth);
		void RenderEllipse(const Position &UpperLeft,
		 const Position &LowerRight, const color &Color,
		 const bool Border = false);
		void RenderPolygon(const Position PolyPoints[], int NPoints,
		 const color &Color, const bool Border = false);
		void RenderPolygon(const vector<Position> &PolyPoints,
		 int NPoints, const color &Color, const bool Border = false);
	
		void RenderText(const Position &UpperLeft,
		 const Position &LowerRight, const string &t = "Message",
		 const color &TextColor = Black,
       const color &BackGroundColor = White);

		void RenderText(const Position &UpperLeft,
		 const Position &LowerRight, const char *t = "Message",
       const color &TextColor = Black,
		 const color &BackGroundColor = White);

		//Add by LeiYM 2014-03-31
		void RenderText(const Position &UpperLeft, const Position &LowerRight,	
			const string& fontName, int textSize, const string& t,  
			const color &TextColor = Black,
			const color &BackGroundColor = White);

		void Message(const string &m = "Message");
		void Message(const char *m = "Message");

		// sometimes it's convenient to access the individual
		// components of a window's
		// position or size (see winlogo.cpp for an example).
		float GetWidth() const;
		float GetHeight() const;
		float GetXPosition() const;
		float GetYPosition() const;

		// get position and center as (Width, Height) or (X, Y).
		Position GetPosition() const;
		Position GetCenter() const;

		// timer members
		bool StartTimer(int Interval);      // Interval is in uSecs
		void StopTimer();

		// set callback functions for window events (refresh,
		// quit, & mouseclick)
		void SetRefreshCallback(RefreshCallbackFunction Callback);
		void SetQuitCallback(QuitCallbackFunction Callback);
		void SetMouseClickCallback(MouseClickCallbackFunction Callback);
		void SetTimerCallback(TimerTickCallbackFunction Callback);

		friend WindowManager;

	protected:
		// the WindowManager uses these members to signal events.
		virtual int RefreshEvent();
		virtual int QuitEvent();
		virtual int MouseClickEvent(const Position &MousePosn);
		virtual int TimerEvent();

	private:

		// Update (X,Y) position automatically if the window is moved.
		int MoveEvent(int X, int Y);

		// Update size (Width,Height) automatically if the window
		// is resized.
		int ResizeEvent(int Width, int Height);

		// Internally used function to display device dependent
		// bitmaps.
		void draw_bitmap(HDC, HBITMAP, int, int);

		// Event callback function pointers
		RefreshCallbackFunction RefreshCallback;
		QuitCallbackFunction QuitCallback;
		MouseClickCallbackFunction MouseClickCallback;
		TimerTickCallbackFunction TimerCallback;

		char *Title;
		HWND hwnd;
		UINT TimerID; // the unique id for the timer for this window
		int TimerActive; // is a timer set and sending messages?

		// Stores image for screen refresh
		HDC BufferDC;
		HBITMAP Bitmap;

      // Stores Screen size
      int ScreenHeight;
      int ScreenWidth;

		// logical coordinates and size -- not valid after Open().
		float LogX, LogY, LogWidth, LogHeight;
		// device coordinates and size -- valid after Open() and
		// always thereafter.
		int WinWidth, WinHeight, WinX, WinY;
		WindowStatus Status;
};

typedef struct DispatchListEntryTag {
	DispatchListEntryTag(HWND H, SimpleWindow *Wp,
	 DispatchListEntryTag *N) : hwnd(H), W(Wp), Next(N) {
		// No code needed!
	};
	HWND hwnd;     		 // the MS Windows handle
	SimpleWindow *W;      // simple window to dispatch messages
	DispatchListEntryTag *Next;
} DispatchListEntry;



// WindowManager - dispatches messages from the MS Windows main loop to
// Window class objects (see below).  Each Window object must register
// with the WindowManager in order to receive Event messages (Refresh,
// Resize, Move, MouseClick, MouseMoved).

class WindowManager {

	public:

		WindowManager();
		~WindowManager();

		int DispatchMessage(HWND, UINT, UINT, LONG);
		int Register(HWND hwnd, SimpleWindow *W);
		int Unregister(HWND hwnd);
		void Terminate();

		// the program instance
		HANDLE ProgramInstance;

		// whether the program is an icon or window
		int Iconized;

  private:

		// MS Windows event dispatch table
		DispatchListEntry *DispatchList;
		void check_termination();
};

// Terminate(): user function to terminate and close all windows
void Terminate();

#endif
