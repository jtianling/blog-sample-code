#include "opengl.h"

OpenGL::OpenGL(QGLWidget *parent)
    : QGLWidget(parent)
{
	ui.setupUi(this);
}

OpenGL::~OpenGL()
{

}

void OpenGL::initializeGL()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// 启用顶点数组
	glEnableClientState(GL_VERTEX_ARRAY);

	// 颜色数组也需要启用
	glEnableClientState(GL_COLOR_ARRAY);

	// 默认就是此参数，可忽略，为了明确说明特意指定
	glShadeModel(GL_SHADE_MODEL);

	// 顶点数组数据
	static GLfloat fVertices[] = {	-0.5, -0.5,
									 0.5, -0.5,
									 0.5,  0.5,
									-0.5,  0.5,
									 0.0,  0.0};	// 添加的原点

	// 颜色数组
	static GLfloat fColor[] = { 1.0, 0.0, 0.0,
								0.0, 1.0, 0.0,
								0.0, 0.0, 1.0,
								0.0, 0.0, 0.0,
								1.0, 1.0, 1.0};		// 原点颜色为白色

	// 指定顶点数组数据
	glVertexPointer(2, GL_FLOAT, 0, fVertices);

	// 制定颜色数组
	glColorPointer(3, GL_FLOAT, 0, fColor);

}

void OpenGL::resizeGL(int, int)
{

}

void OpenGL::paintGL()
{
	draw();
}

void OpenGL::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);	// 清空颜色缓冲区

	static GLubyte byTopIndices[] = { 2, 3, 4};
	static GLubyte byLeftIndices[] = { 3, 0, 4};
	static GLubyte byBottomIndices[] = { 0, 1, 4};
	static GLubyte byRightIndices[] = { 1, 2, 4};

	// 上述函数调用与下面的效果一样
	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, byTopIndices);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, byLeftIndices);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, byBottomIndices);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, byRightIndices);
	glPopMatrix();

}
