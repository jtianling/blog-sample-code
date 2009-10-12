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

  本工程是从《OpenGL 编程指南》（《OpenGL Programming Guide》）的示例
  代码mvarray.c改过来的。其中的宏GL_VERSION_1_3是由glew定义用来表示支
  持OpenGL1.3版本，其中的函数glMultiDrawElementsEXT就是Windows
  本身不支持，用了glew后才能使用的OpenGL扩展接口（首先要显卡支持啊）。
  glut的使用那就更不用说了。提供的目的是为了检验glew和glut的安装

  对应的博客文章为《Win32 OpenGL编程(2) 寻找缺失的OpenGL函数 》
  http://blog.csdn.net/vagrxie/archive/2009/09/29/4617556.aspx

  本工程用Google Project Host保存，用Mercurial管理
  Mercurial的使用方法可以参考
  http://blog.csdn.net/vagrxie/archive/2009/09/25/4593687.aspx

 *******************************************************************/
