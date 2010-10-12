/********************************************************************************
** Form generated from reading ui file 'opengl.ui'
**
** Created: Sat Oct 3 17:17:36 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_OPENGL_H
#define UI_OPENGL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenGLClass
{
public:

    void setupUi(QWidget *OpenGLClass)
    {
        if (OpenGLClass->objectName().isEmpty())
            OpenGLClass->setObjectName(QString::fromUtf8("OpenGLClass"));
        OpenGLClass->resize(400, 300);

        retranslateUi(OpenGLClass);

        QMetaObject::connectSlotsByName(OpenGLClass);
    } // setupUi

    void retranslateUi(QWidget *OpenGLClass)
    {
        OpenGLClass->setWindowTitle(QApplication::translate("OpenGLClass", "OpenGL", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(OpenGLClass);
    } // retranslateUi

};

namespace Ui {
    class OpenGLClass: public Ui_OpenGLClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENGL_H
