/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTreeWidget *treeWidget;
    QLabel *label;
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QComboBox *comboBox;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 768);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("Program:"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem4);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem6);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem8);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem10 = new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem10);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(0, 100, 1024, 650));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 131, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 40, 161, 16));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 60, 398, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setDuplicatesEnabled(false);

        horizontalLayout->addWidget(comboBox);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        comboBox_2 = new QComboBox(layoutWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setDuplicatesEnabled(true);

        horizontalLayout->addWidget(comboBox_2);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 22));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("MainWindow", "Students:", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "Hours:", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Acedemic Year:", 0));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(3, QApplication::translate("MainWindow", "808", 0));
        ___qtreewidgetitem1->setText(2, QApplication::translate("MainWindow", "1620", 0));
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "PME", 0));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(3, QApplication::translate("MainWindow", "250", 0));
        ___qtreewidgetitem2->setText(2, QApplication::translate("MainWindow", "500", 0));
        ___qtreewidgetitem2->setText(1, QApplication::translate("MainWindow", "2012-2013", 0));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem2->child(0);
        ___qtreewidgetitem3->setText(3, QApplication::translate("MainWindow", "120", 0));
        ___qtreewidgetitem3->setText(2, QApplication::translate("MainWindow", "125", 0));
        ___qtreewidgetitem3->setText(1, QApplication::translate("MainWindow", "Faculty 1", 0));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem2->child(1);
        ___qtreewidgetitem4->setText(3, QApplication::translate("MainWindow", "80", 0));
        ___qtreewidgetitem4->setText(2, QApplication::translate("MainWindow", "125", 0));
        ___qtreewidgetitem4->setText(1, QApplication::translate("MainWindow", "Faculty 2", 0));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem2->child(2);
        ___qtreewidgetitem5->setText(3, QApplication::translate("MainWindow", "50", 0));
        ___qtreewidgetitem5->setText(2, QApplication::translate("MainWindow", "250", 0));
        ___qtreewidgetitem5->setText(1, QApplication::translate("MainWindow", "Faculty 3", 0));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem6->setText(3, QApplication::translate("MainWindow", "258", 0));
        ___qtreewidgetitem6->setText(2, QApplication::translate("MainWindow", "480", 0));
        ___qtreewidgetitem6->setText(1, QApplication::translate("MainWindow", "2013-2014", 0));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem6->child(0);
        ___qtreewidgetitem7->setText(3, QApplication::translate("MainWindow", "258", 0));
        ___qtreewidgetitem7->setText(2, QApplication::translate("MainWindow", "480", 0));
        ___qtreewidgetitem7->setText(1, QApplication::translate("MainWindow", "Faculty 1", 0));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem8->setText(3, QApplication::translate("MainWindow", "300", 0));
        ___qtreewidgetitem8->setText(2, QApplication::translate("MainWindow", "640", 0));
        ___qtreewidgetitem8->setText(1, QApplication::translate("MainWindow", "2014-2015", 0));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(3, QApplication::translate("MainWindow", "300", 0));
        ___qtreewidgetitem9->setText(2, QApplication::translate("MainWindow", "640", 0));
        ___qtreewidgetitem9->setText(1, QApplication::translate("MainWindow", "Faculty 1", 0));
        QTreeWidgetItem *___qtreewidgetitem10 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem10->setText(3, QApplication::translate("MainWindow", "498", 0));
        ___qtreewidgetitem10->setText(2, QApplication::translate("MainWindow", "1500", 0));
        ___qtreewidgetitem10->setText(0, QApplication::translate("MainWindow", "UME", 0));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem10->child(0);
        ___qtreewidgetitem11->setText(3, QApplication::translate("MainWindow", "498", 0));
        ___qtreewidgetitem11->setText(2, QApplication::translate("MainWindow", "1500", 0));
        ___qtreewidgetitem11->setText(1, QApplication::translate("MainWindow", "2013-2014", 0));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem11->child(0);
        ___qtreewidgetitem12->setText(3, QApplication::translate("MainWindow", "498", 0));
        ___qtreewidgetitem12->setText(2, QApplication::translate("MainWindow", "1500", 0));
        ___qtreewidgetitem12->setText(1, QApplication::translate("MainWindow", "Faculty 3", 0));
        QTreeWidgetItem *___qtreewidgetitem13 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem13->setText(3, QApplication::translate("MainWindow", "300", 0));
        ___qtreewidgetitem13->setText(2, QApplication::translate("MainWindow", "1200", 0));
        ___qtreewidgetitem13->setText(0, QApplication::translate("MainWindow", "CME", 0));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem13->child(0);
        ___qtreewidgetitem14->setText(3, QApplication::translate("MainWindow", "300", 0));
        ___qtreewidgetitem14->setText(2, QApplication::translate("MainWindow", "1200", 0));
        ___qtreewidgetitem14->setText(1, QApplication::translate("MainWindow", "2012-2013", 0));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem14->child(0);
        ___qtreewidgetitem15->setText(3, QApplication::translate("MainWindow", "300", 0));
        ___qtreewidgetitem15->setText(2, QApplication::translate("MainWindow", "1200", 0));
        ___qtreewidgetitem15->setText(1, QApplication::translate("MainWindow", "Faculty 1", 0));
        QTreeWidgetItem *___qtreewidgetitem16 = treeWidget->topLevelItem(3);
        ___qtreewidgetitem16->setText(3, QApplication::translate("MainWindow", "121", 0));
        ___qtreewidgetitem16->setText(2, QApplication::translate("MainWindow", "800", 0));
        ___qtreewidgetitem16->setText(0, QApplication::translate("MainWindow", "Other", 0));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem16->child(0);
        ___qtreewidgetitem17->setText(3, QApplication::translate("MainWindow", "121", 0));
        ___qtreewidgetitem17->setText(2, QApplication::translate("MainWindow", "800", 0));
        ___qtreewidgetitem17->setText(1, QApplication::translate("MainWindow", "2014-2015", 0));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem17->child(0);
        ___qtreewidgetitem18->setText(3, QApplication::translate("MainWindow", "121", 0));
        ___qtreewidgetitem18->setText(2, QApplication::translate("MainWindow", "800", 0));
        ___qtreewidgetitem18->setText(1, QApplication::translate("MainWindow", "Faculty 4", 0));
        treeWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QApplication::translate("MainWindow", "Teaching Summary", 0));
        label_2->setText(QApplication::translate("MainWindow", "Department of Medicine", 0));
        label_3->setText(QApplication::translate("MainWindow", "Date Range:", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "2009", 0)
         << QApplication::translate("MainWindow", "2010", 0)
         << QApplication::translate("MainWindow", "2011", 0)
         << QApplication::translate("MainWindow", "2012", 0)
         << QApplication::translate("MainWindow", "2013", 0)
         << QApplication::translate("MainWindow", "2014", 0)
        );
        label_4->setText(QApplication::translate("MainWindow", "to", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "2010", 0)
         << QApplication::translate("MainWindow", "2011", 0)
         << QApplication::translate("MainWindow", "2012", 0)
         << QApplication::translate("MainWindow", "2013", 0)
         << QApplication::translate("MainWindow", "2014", 0)
         << QApplication::translate("MainWindow", "2015", 0)
        );
        pushButton->setText(QApplication::translate("MainWindow", "Graph", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
