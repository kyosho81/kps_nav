/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of a Qt Solutions component.
**
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#include <QtGui/QApplication>
#include <QtCore/QDate>
#include <QtCore/QLocale>
#include "property/qtpropertymanager.h"
#include "property/qtvariantproperty.h"
#include "property/qttreepropertybrowser.h"

#include <iostream>
#include <climits>

int main2(int argc, char **argv)
{
	using namespace std;
	//init max value
	int i = INT_MAX;
	short sh = SHRT_MAX;
	long lg = LONG_MAX;
	long long ll = LLONG_MAX;

	cout<< "int is "<< sizeof(i) << " bytes"<<endl;
	cout<< "short is " << sizeof(sh) << " bytes"<<endl;
	cout<< "long is " << sizeof(lg) << " bytes"<<endl;
	cout<< "long long is " << sizeof(ll) << " bytes"<<endl;

	cout<< "int max values:"<<i<<endl;
	cout<< "short max values:"<<sh<<endl;
	cout<< "long max values:"<<lg<<endl;
	cout<< "long long max values:"<<ll<<endl;


	cout<< "int min values:"<<INT_MIN<<endl;


	system("pause");

	short sh_max = SHRT_MAX;
	short sh_min = SHRT_MIN;
	cout<< "short max values:"<<sh_max<<endl;
	cout<< "short min values:"<<sh_min<<endl;
	
	system("pause");
	short sh_max_1 = sh_max + 1;
	cout<< "short max + 1 values:"<<sh_max_1<<endl;

	system("pause");
	short diff = sh_min - sh_max;
	cout<<"diff min - max values:"<<sh_min - sh_max  <<endl;
	cout<<"diff min - max values:"<<diff<<endl;
	system("pause");

	return 0;
}
	
int main(int argc, char **argv)
{	
    QApplication app(argc, argv);

    QtVariantPropertyManager *variantManager = new QtVariantPropertyManager();

    int i = 0;
    QtProperty *topItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(),
                QString::number(i++) + QLatin1String(" Group Property"));

    QtVariantProperty *item = variantManager->addProperty(QVariant::Bool, QString::number(i++) + QLatin1String(" Bool Property"));
    item->setValue(true);
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Int, QString::number(i++) + QLatin1String(" Int Property"));
    item->setValue(20);
    item->setAttribute(QLatin1String("minimum"), 0);
    item->setAttribute(QLatin1String("maximum"), 100);
    item->setAttribute(QLatin1String("singleStep"), 10);
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Double, QString::number(i++) + QLatin1String(" Double Property"));
    item->setValue(1.2345);
    item->setAttribute(QLatin1String("singleStep"), 0.1);
    item->setAttribute(QLatin1String("decimals"), 3);
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::String, QString::number(i++) + QLatin1String(" String Property"));
    item->setValue("Value");
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Date, QString::number(i++) + QLatin1String(" Date Property"));
    item->setValue(QDate::currentDate().addDays(2));
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Time, QString::number(i++) + QLatin1String(" Time Property"));
    item->setValue(QTime::currentTime());
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::DateTime, QString::number(i++) + QLatin1String(" DateTime Property"));
    item->setValue(QDateTime::currentDateTime());
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::KeySequence, QString::number(i++) + QLatin1String(" KeySequence Property"));
    item->setValue(QKeySequence(Qt::ControlModifier | Qt::Key_Q));
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Char, QString::number(i++) + QLatin1String(" Char Property"));
    item->setValue(QChar(386));
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Locale, QString::number(i++) + QLatin1String(" Locale Property"));
    item->setValue(QLocale(QLocale::Polish, QLocale::Poland));
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Point, QString::number(i++) + QLatin1String(" Point Property"));
    item->setValue(QPoint(10, 10));
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::PointF, QString::number(i++) + QLatin1String(" PointF Property"));
    item->setValue(QPointF(1.2345, -1.23451));
    item->setAttribute(QLatin1String("decimals"), 3);
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Size, QString::number(i++) + QLatin1String(" Size Property"));
    item->setValue(QSize(20, 20));
    item->setAttribute(QLatin1String("minimum"), QSize(10, 10));
    item->setAttribute(QLatin1String("maximum"), QSize(30, 30));
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::SizeF, QString::number(i++) + QLatin1String(" SizeF Property"));
    item->setValue(QSizeF(1.2345, 1.2345));
    item->setAttribute(QLatin1String("decimals"), 3);
    item->setAttribute(QLatin1String("minimum"), QSizeF(0.12, 0.34));
    item->setAttribute(QLatin1String("maximum"), QSizeF(20.56, 20.78));
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Rect, QString::number(i++) + QLatin1String(" Rect Property"));
    item->setValue(QRect(10, 10, 20, 20));
    topItem->addSubProperty(item);
    item->setAttribute(QLatin1String("constraint"), QRect(0, 0, 50, 50));

    item = variantManager->addProperty(QVariant::RectF, QString::number(i++) + QLatin1String(" RectF Property"));
    item->setValue(QRectF(1.2345, 1.2345, 1.2345, 1.2345));
    topItem->addSubProperty(item);
    item->setAttribute(QLatin1String("constraint"), QRectF(0, 0, 50, 50));
    item->setAttribute(QLatin1String("decimals"), 3);

    item = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(),
                    QString::number(i++) + QLatin1String(" Enum Property"));
    QStringList enumNames;
    enumNames << "Enum0" << "Enum1" << "Enum2";
    item->setAttribute(QLatin1String("enumNames"), enumNames);
    item->setValue(1);
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QtVariantPropertyManager::flagTypeId(),
                    QString::number(i++) + QLatin1String(" Flag Property"));
    QStringList flagNames;
    flagNames << "Flag0" << "Flag1" << "Flag2";
    item->setAttribute(QLatin1String("flagNames"), flagNames);
    item->setValue(5);
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::SizePolicy, QString::number(i++) + QLatin1String(" SizePolicy Property"));
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Font, QString::number(i++) + QLatin1String(" Font Property"));
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Cursor, QString::number(i++) + QLatin1String(" Cursor Property"));
    topItem->addSubProperty(item);

    item = variantManager->addProperty(QVariant::Color, QString::number(i++) + QLatin1String(" Color Property"));
    topItem->addSubProperty(item);
	std::cout<<"color"<<item->value().toString().toStdString()<<std::endl;

    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory();

    QtTreePropertyBrowser *variantEditor = new QtTreePropertyBrowser();
    variantEditor->setFactoryForManager(variantManager, variantFactory);
    variantEditor->addProperty(topItem);
    variantEditor->setPropertiesWithoutValueMarked(true);
    variantEditor->setRootIsDecorated(false);

    variantEditor->show();

    int ret = app.exec();

    delete variantManager;
    delete variantFactory;
    delete variantEditor;

    return ret;
}
