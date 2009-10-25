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

  本工程用Google Project Host保存，用Mercurial管理
  Mercurial的使用方法可以参考
  http://blog.csdn.net/vagrxie/archive/2009/09/25/4593687.aspx
 *********************************************************************/
/***********************************************************************
	文件信息：
	创建日期:	2009-10-20
	文件名: 	GLShape.h
	文件说明:	CGLShape头文件
 *********************************************************************/
#ifndef __GLSHAPE_H__
#define __GLSHAPE_H__
#include <GL/glew.h>
#include <GL/wglew.h>
#include "Defines.h"
// 此类实现移动，旋转，
class CGLShape
{
public:
	CGLShape(void)
	{
		mfPosX = 0.0;
		mfPosY = 0.0;
		memset(mfvColor, 0, sizeof(mfvColor));
		mfDegree = 0.0;
		mfSize = 1.0;
	}
	virtual ~CGLShape(void) { }

	void SetSize(GLfloat afSize) { mfSize = afSize; }

	void SetColor(GLfloat afRed, GLfloat afGreen, GLfloat afBlue, GLfloat afAlpha = 1.0)
	{
		mfvColor[0] = afRed;
		mfvColor[1] = afGreen;
		mfvColor[2] = afBlue;
		mfvColor[3] = afAlpha;
	}

	// 相对偏移(外部坐标系长度)
	void Move(int aiPosX, int aiPosY) 
	{
		mfPosX += 2.0f * aiPosX/(float)WIDTH;
		mfPosY += -(2.0f * aiPosY/(float)HEIGHT);
	}

	// 移动到的位置(Windows坐标系点)
	void MoveTo(int aiPosX, int aiPosY)
	{
		mfPosX = (2.0f * aiPosX - (float)WIDTH) / (float)WIDTH;
		mfPosY = -(2.0f * aiPosY - (float)HEIGHT) / (float)HEIGHT;
	}

	// 旋转,以逆时针为正方向
	void Rotate(GLfloat aiDegree) { mfDegree += aiDegree; }

	// 旋转到
	void RotateTo(GLfloat aiDegree) { mfDegree = aiDegree; }

	// OpenGL坐标系
	void SetPos(GLfloat afPosX, GLfloat afPosY) { mfPosX = afPosX; mfPosY = afPosY; }
	void GetPos(GLfloat& afPosX, GLfloat& afPosY) { afPosX = mfPosX; afPosY = mfPosY; }

	void Draw()
	{
		glLoadIdentity();
		glColor4fv(mfvColor);

		glPushMatrix();
		glTranslatef(mfPosX, mfPosY, 0.0);
		glRotatef(mfDegree, 0.0, 0.0, 1.0);

		DrawImp();

		glPopMatrix();
	}

protected:
	// 重绘时需要调用的函数,由各子类实现
	virtual void DrawImp() = 0;

	// 位置信息,没有用POINT是为了将来方便移植
	GLfloat mfPosX;
	GLfloat mfPosY;

	// 颜色
	GLfloat mfvColor[4];

	// 旋转度数
	GLfloat mfDegree;

	// 大小
	GLfloat mfSize;
};

#endif
