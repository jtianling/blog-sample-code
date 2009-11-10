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

  本工程用Google Project Host保存，用Mercurial管理，在VS2008 SP1下编译通过
  Mercurial的使用方法可以参考
  http://blog.csdn.net/vagrxie/archive/2009/09/25/4593687.aspx
 *********************************************************************/

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

//定义程序链接时所需要调用的OpenGL程序库,简化工程配置
#pragma comment( lib, "opengl32.lib" ) 
#pragma comment( lib, "glu32.lib" )  
#pragma comment( lib, "glew32.lib" )  
#pragma comment( lib, "glew32s.lib" )  

// DEFINES ////////////////////////////////////////////////

// defines for windows 
#define WINDOW_CLASS_NAME _T("WINCLASS1")
#define WINDOW_TITLE _T("OpenGL")
// MACROS /////////////////////////////////////////////////

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// GLOBALS ////////////////////////////////////////////////
HWND      ghWnd; // 窗口句柄
HINSTANCE ghInstance; // 程序实例句柄
HDC ghDC;					// GDI设备环境句柄
HGLRC ghRC;           // 渲染器环境句柄

#define FRAME_PER_SECOND (60)
#define TIME_IN_FRAME (1000/FRAME_PER_SECOND)
#define WIDTH (800)
#define HEIGHT (600)

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
		PFD_SUPPORT_OPENGL;
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

}
void DrawSmoothColorPyramid(GLfloat adSize)
{
	static GLfloat fPyramidDatas[] = {	0.0, 1.0, 0.0,	// 三角锥上顶点
		-1.0, 0.0, 1.0,	// 底面左前顶点
		1.0, 0.0, 1.0,	// 底面右前下顶点
		0.0, 0.0, -1.0}; // 底面后下顶点

	GLfloat fPyramidSizeDatas[sizeof(fPyramidDatas)/sizeof(GLfloat)] = {0};

	// 计算大小
	for( int i = 0; i < 12; ++i)
	{
		fPyramidSizeDatas[i] = fPyramidDatas[i] * adSize;
	}

	static GLfloat fPyramidColors[] = { 1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0};

	static GLubyte ubyIndices[] = {	0, 1, 2,	// 正面
		0, 1, 3,	// 左侧面
		0, 2, 3,	// 右侧面
		1, 2, 3};	// 底面

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, fPyramidSizeDatas);
	glColorPointer(3, GL_FLOAT, 0, fPyramidColors);

	for(int i = 0; i < 4; ++i)
	{
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, ubyIndices+i*3);
	}
}

//这里进行所有的绘图工作
void SceneShow(GLvoid)        
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glPushMatrix();
	DrawSmoothColorPyramid(0.5);
	glPopMatrix();

	glRotatef(1.0, 0.0, 1.0, 0.0);

	glFlush();
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
