/***********************************************************************

  版权所有(C) 2009 九天雁翎
  Copyright (C) 2009 JTianLing

  *********************************************************************
  这一程序是自由软件，你可以遵照自由软件基金会出版的 GNU 通用公共许可
  证条款来修改和重新发布这一程序。或者用许可证的第二版，或者（根据你的选
  择）用任何更新的版本。
  发布这一程序的目的是希望它有用，但没有任何担保。甚至没有适合特定目
  的的隐含的担保。更详细的情况请参阅 GNU 通用公共许可证。
  你应该已经和程序一起收到一份 GNU 通用公共许可证的副本。如果还没有，
	写信给：
    The Free Software Foundation, Inc.,  675  Mass Ave,  Cambridge,
    MA02139,  USA
 *********************************************************************
    欢迎大家在下述网页发帖或来信说明讨论该软件的BUG和可以改进之处

  	Webs	: groups.google.com/group/jiutianfile
  	Blog	: blog.csdn.net/vagrxie
  	E-mail	: JTianLing@GMail.com
  	QQ	: 375454
  
 *********************************************************************

  本工程是一个Win32 OpenGL 动画程序模板,从Andre LaMothe 的T3D Game Console
  加上OpenGL相关内容改编而来,用Visual Studio 2008 SP1管理工程。
	
  对应的博客文章是《Win32 OpenGL 编程（1）Win32下的OpenGL编程必须步骤》
  http://blog.csdn.net/vagrxie/archive/2009/09/28/4602961.aspx

  本工程用Google Project Host保存，用Mercurial管理
  Mercurial的使用方法可以参考
  http://blog.csdn.net/vagrxie/archive/2009/09/25/4593687.aspx
 *******************************************************************/
/*********************************************************************
	文件信息：
	创建日期:	2009-9-27   7:32
	文件名: 	Win32OpenGLTemplate.cpp
	文件说明:	本文件是一个Win32 OpenGL 动画程序模板主文件,从Andre LaMothe 的T3D Game Console
  加上OpenGL相关内容改编而来,用Visual Studio 2008 SP1管理工程。
 ********************************************************************/
// INCLUDES ///////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN  // just say no to MFC

#include <tchar.h>
#include <windows.h>   // include important windows stuff
#include <windowsx.h> 
#include <mmsystem.h>
#include <iostream> // include important C/C++ stuff
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h> 
#include <math.h>
#include <io.h>
#include <fcntl.h>

// OpenGL1.1以后版本需要的头文件
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>

//定义程序链接时所需要调用的OpenGL程序库,简化工程配置
#pragma comment( lib, "glew32.lib" )  
#pragma comment( lib, "glew32s.lib" )  
#pragma comment( lib, "glut32.lib")
  

// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME _T("WINCLASS1")
#define WINDOW_TITLE _T("OpenGL")
// MACROS /////////////////////////////////////////////////

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// GLOBALS ////////////////////////////////////////////////
HWND      ghWnd = NULL; // globally track main window
HINSTANCE ghInstance      = NULL; // globally track hinstance
HDC ghDC;					// GDI设备环境
HGLRC ghRC=NULL;           // 渲染环境
GLuint gTexName;

#define FRAME_PER_SECOND (60.0)
#define TIME_IN_FRAME (1000.0/FRAME_PER_SECOND)
#define WIDTH (600)
#define HEIGHT (600)
/*	Create checkerboard texture	*/
BITMAP gBmp; 

GLfloat	xrot;				// X Rotation ( NEW )
GLfloat	yrot;				// Y Rotation ( NEW )
GLfloat	zrot;				// Z Rotation ( NEW )


//激活创建OpenGL窗口
void EnableOpenGL()
{
	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;

	ghDC = GetDC( ghWnd );

	ZeroMemory( &pfd, sizeof( pfd ) );
	pfd.nSize = sizeof( pfd );  
	pfd.nVersion = 1;      //版本，一般设为1
	pfd.dwFlags =   PFD_DRAW_TO_WINDOW | //一组表明象素缓冲特性的标志位
		PFD_SUPPORT_OPENGL  | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;   //明象素数据类型是RGBA还是颜色索引;
	pfd.cColorBits = 32;     //每个颜色缓冲区中颜色位平面的数目，对颜色索引方式是缓冲区大小
	pfd.iLayerType = PFD_MAIN_PLANE; //被忽略，为了一致性而包含的

	iFormat = ChoosePixelFormat( ghDC, &pfd );//选择一个像素格式

	SetPixelFormat( ghDC, iFormat, &pfd ); //设置到DC中

	ghRC = wglCreateContext( ghDC );    //创建绘图描述表
	wglMakeCurrent( ghDC, ghRC );     //使之成为当前绘图描述表
}

//OpenGL初始化开始
void SceneInit(int w,int h)
{
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		MessageBox(NULL, _T("Error"), _T("Glew init failed."), MB_OK);
		exit(-1);
	}

	wglSwapIntervalEXT(0);

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	glViewport(0,0,WIDTH,HEIGHT);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix


	HBITMAP hBmp=(HBITMAP)LoadImageW( NULL, L"tiger.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE );

	if (!hBmp)         
	{
		exit(3);   
	}

	GetObject(hBmp, sizeof(gBmp), &gBmp);   
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glGenTextures(1, &gTexName);
	glBindTexture(GL_TEXTURE_2D, gTexName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gBmp.bmWidth, gBmp.bmHeight,
		0, GL_BGR, GL_UNSIGNED_BYTE, gBmp.bmBits);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);


	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}

 //这里进行所有的绘图工作
void SceneShow(GLvoid)        
{
   //glClear(GL_COLOR_BUFFER_BIT);
   //glEnable(GL_TEXTURE_2D);
   //glBegin(GL_QUADS);
   //glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
   //glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
   //glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
   //glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 0.0);
   //glEnd();

   //SwapBuffers(ghDC);
   //glDisable(GL_TEXTURE_2D);


   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	glTranslatef(0.0f,0.0f,-5.0f);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);
	glRotatef(zrot,0.0f,0.0f,1.0f);

	glBindTexture(GL_TEXTURE_2D, gTexName);

	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

	xrot+=0.3f;
	yrot+=0.2f;
	zrot+=0.4f;

	SwapBuffers(ghDC);
}  

// 取消 OpenGL ，在程序结束前调用，释放渲染环境，设备环境以及最终窗口句柄。
void DisableOpenGL()
{
	wglMakeCurrent( NULL, NULL );
	wglDeleteContext( ghRC );
	ReleaseDC( ghWnd, ghDC );
}


// FUNCTIONS //////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, 
							UINT msg, 
							WPARAM wparam, 
							LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT		ps;		// used in WM_PAINT
	HDC				hdc;	// handle to a device context

	// what is the message 
	switch(msg)
	{	
	case WM_CREATE: 
		{
			// do initialization stuff here
			// return success
			return(0);
		} break;

	case WM_PAINT: 
		{
			// simply validate the window 
			hdc = BeginPaint(hwnd,&ps);	 

			// end painting
			EndPaint(hwnd,&ps);

			// return success
			return(0);
		} break;

	case WM_DESTROY: 
		{

			// kill the application, this sends a WM_QUIT message 
			PostQuitMessage(0);

			// return success
			return(0);
		} break;

	default:break;

	} // end switch

	// process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));

} // end WinProc

///////////////////////////////////////////////////////////

int Game_Main(void *parms = NULL, int num_parms = 0)
{
	DWORD dwStartTime;

	dwStartTime = GetTickCount();
	// this is the main loop of the game, do all your processing
	// here

	// for now test if user is hitting ESC and send WM_CLOSE
	if (KEYDOWN(VK_ESCAPE))
		SendMessage(ghWnd,WM_CLOSE,0,0);

	SceneShow();

	// 控制帧率
	while(GetTickCount() - dwStartTime < TIME_IN_FRAME)
	{
		Sleep(1);
	}

	// return success or failure or your own return code here
	return(1);

} // end Game_Main

////////////////////////////////////////////////////////////

int Game_Init(void *parms = NULL, int num_parms = 0)
{
	// this is called once after the initial window is created and
	// before the main event loop is entered, do all your initialization
	// here
	ghDC = GetDC(ghWnd);

	EnableOpenGL();
	SceneInit(WIDTH, HEIGHT);

	// return success or failure or your own return code here
	return(1);

} // end Game_Init

/////////////////////////////////////////////////////////////

int Game_Shutdown(void *parms = NULL, int num_parms = 0)
{
	// this is called after the game is exited and the main event
	// loop while is exited, do all you cleanup and shutdown here
	DisableOpenGL();

	// return success or failure or your own return code here
	return(1);

} // end Game_Shutdown

// WINMAIN ////////////////////////////////////////////////
int WINAPI WinMain(	HINSTANCE hinstance,
				   HINSTANCE hprevinstance,
				   LPSTR lpcmdline,
				   int ncmdshow)
{

	WNDCLASSEX winclass; // this will hold the class we create
	HWND	   hwnd;	 // generic window handle
	MSG		   msg;		 // generic message

	// first fill in the window class stucture
	winclass.cbSize         = sizeof(WNDCLASSEX);
	winclass.style			= CS_DBLCLKS | CS_OWNDC | 
		CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL;
	winclass.lpszClassName	= WINDOW_CLASS_NAME;
	winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

	// save hinstance in global
	ghInstance = hinstance;

	// register the window class
	if (!RegisterClassEx(&winclass))
		return(0);

	// create the window
	if (!(hwnd = CreateWindowEx(NULL,                  // extended style
		WINDOW_CLASS_NAME,     // class
		WINDOW_TITLE, // title
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0,0,	  // initial x,y
		WIDTH,HEIGHT,  // initial width, height
		NULL,	  // handle to parent 
		NULL,	  // handle to menu
		hinstance,// instance of this application
		NULL)))	// extra creation parms
		return(0);

	// save main window handle
	ghWnd = hwnd;

	// initialize game here
	Game_Init();

	// enter main event loop
	while(TRUE)
	{
		// test if there is a message in queue, if so get it
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			// test if this is a quit
			if (msg.message == WM_QUIT)
				break;

			// translate any accelerator keys
			TranslateMessage(&msg);

			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if

		// main game processing goes here
		Game_Main();

	} // end while

	// closedown game here
	Game_Shutdown();

	// return to Windows like this
	return(msg.wParam);

} // end WinMain

///////////////////////////////////////////////////////////

 
