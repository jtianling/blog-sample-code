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


#ifndef __GLTRIANGLE_H__
#define __GLTRIANGLE_H__
#include "GLShape.h"

class CGLTriangle : public CGLShape
{
public:
	CGLTriangle() { }
	virtual ~CGLTriangle() { }

	// 重绘时需要调用的函数,由各子类实现
	virtual void DrawImp()
	{
		static GLfloat fvTop[3] = { 0.0, (1.0/3.0), 0.0};
		static GLfloat fvLeftBottom[3] = { -0.5, -(1.0/6.0), 0.0};
		static GLfloat fvRightBottom[3] = { 0.5, -(1.0/6.0), 0.0};

		GLfloat fvSizeTop[3] = {fvTop[0], fvTop[1] * mfSize, fvTop[2]};
		GLfloat fvSizeLeftBottom[3] = {fvLeftBottom[0] * mfSize, fvLeftBottom[1] * mfSize, fvLeftBottom[2]};
		GLfloat fvSizeRightBottom[3] = {fvRightBottom[0] * mfSize, fvRightBottom[1] * mfSize, fvRightBottom[2]};

		glBegin(GL_TRIANGLES);
		glVertex3fv(fvSizeTop);
		glVertex3fv(fvSizeLeftBottom);
		glVertex3fv(fvSizeRightBottom);
		glEnd();

	}
};




#endif