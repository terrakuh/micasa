/********************************************************************************
** Form generated from reading UI file 'glhKphjX.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GLHKPHJX_H
#define GLHKPHJX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
	QWidget * centralwidget;
	QHBoxLayout *horizontalLayout;
	QGraphicsView *graphicsView;

	void setupUi(QMainWindow *MainWindow)
	{
		if (MainWindow->objectName().isEmpty())
			MainWindow->setObjectName(QStringLiteral("MainWindow"));
		MainWindow->resize(800, 600);
		centralwidget = new QWidget(MainWindow);
		centralwidget->setObjectName(QStringLiteral("centralwidget"));
		horizontalLayout = new QHBoxLayout(centralwidget);
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		horizontalLayout->setContentsMargins(0, 0, 0, 0);
		graphicsView = new QGraphicsView(centralwidget);
		graphicsView->setObjectName(QStringLiteral("graphicsView"));

		horizontalLayout->addWidget(graphicsView);

		MainWindow->setCentralWidget(centralwidget);

		retranslateUi(MainWindow);

		QMetaObject::connectSlotsByName(MainWindow);
	} // setupUi

	void retranslateUi(QMainWindow *MainWindow)
	{
		MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Micasa", nullptr));
	} // retranslateUi

};

namespace Ui
{
class MainWindow : public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GLHKPHJX_H
