/********************************************************************************
** Form generated from reading UI file 'designerqLXrpX.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DESIGNERQLXRPX_H
#define DESIGNERQLXRPX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Image
{
public:
	QVBoxLayout * verticalLayout;
	QLabel *label;

	void setupUi(QWidget *Image)
	{
		if (Image->objectName().isEmpty())
			Image->setObjectName(QStringLiteral("Image"));
		Image->resize(648, 764);
		QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(Image->sizePolicy().hasHeightForWidth());
		Image->setSizePolicy(sizePolicy);
		verticalLayout = new QVBoxLayout(Image);
		verticalLayout->setSpacing(0);
		verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
		verticalLayout->setContentsMargins(0, 0, 0, 0);
		label = new QLabel(Image);
		label->setObjectName(QStringLiteral("label"));
		QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
		sizePolicy1.setHorizontalStretch(0);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
		label->setSizePolicy(sizePolicy1);
		label->setPixmap(QPixmap(QString::fromUtf8("P:/test.jpg")));
		label->setScaledContents(true);

		verticalLayout->addWidget(label);


		retranslateUi(Image);

		QMetaObject::connectSlotsByName(Image);
	} // setupUi

	void retranslateUi(QWidget *Image)
	{
		Image->setWindowTitle(QApplication::translate("Image", "Image", nullptr));
		label->setText(QString());
	} // retranslateUi

};

namespace Ui
{
class Image : public Ui_Image {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNERQLXRPX_H
