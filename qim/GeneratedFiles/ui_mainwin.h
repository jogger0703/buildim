/********************************************************************************
** Form generated from reading UI file 'mainwin.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_H
#define UI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwinClass
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;

    void setupUi(QDialog *mainwinClass)
    {
        if (mainwinClass->objectName().isEmpty())
            mainwinClass->setObjectName(QString::fromUtf8("mainwinClass"));
        mainwinClass->resize(281, 500);
        mainwinClass->setMinimumSize(QSize(280, 500));
        QIcon icon;
        icon.addFile(QString::fromUtf8("C:/Users/eyou/Downloads/im_2.ico"), QSize(), QIcon::Normal, QIcon::Off);
        mainwinClass->setWindowIcon(icon);
        tabWidget = new QTabWidget(mainwinClass);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 80, 241, 411));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(mainwinClass);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(mainwinClass);
    } // setupUi

    void retranslateUi(QDialog *mainwinClass)
    {
        mainwinClass->setWindowTitle(QApplication::translate("mainwinClass", "pim", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("mainwinClass", "Tab 1", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("mainwinClass", "Tab 2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mainwinClass: public Ui_mainwinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H
