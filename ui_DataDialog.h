/********************************************************************************
** Form generated from reading UI file 'DataDialog.ui'
**
** Created: Tue Apr 24 13:13:13 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATADIALOG_H
#define UI_DATADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_dlgDataDialog
{
public:
    QTableWidget *tblAttributes;
    QTableWidget *tblCellType;
    QTableWidget *tblMolType;

    void setupUi(QDialog *dlgDataDialog)
    {
        if (dlgDataDialog->objectName().isEmpty())
            dlgDataDialog->setObjectName(QString::fromUtf8("dlgDataDialog"));
        dlgDataDialog->resize(313, 634);
        tblAttributes = new QTableWidget(dlgDataDialog);
        if (tblAttributes->columnCount() < 3)
            tblAttributes->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblAttributes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblAttributes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblAttributes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tblAttributes->setObjectName(QString::fromUtf8("tblAttributes"));
        tblAttributes->setGeometry(QRect(0, 420, 311, 211));
        tblAttributes->setSelectionMode(QAbstractItemView::NoSelection);
        tblCellType = new QTableWidget(dlgDataDialog);
        if (tblCellType->columnCount() < 2)
            tblCellType->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblCellType->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblCellType->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        tblCellType->setObjectName(QString::fromUtf8("tblCellType"));
        tblCellType->setGeometry(QRect(0, 210, 311, 201));
        tblCellType->setSelectionMode(QAbstractItemView::NoSelection);
        tblMolType = new QTableWidget(dlgDataDialog);
        if (tblMolType->columnCount() < 2)
            tblMolType->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tblMolType->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tblMolType->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        tblMolType->setObjectName(QString::fromUtf8("tblMolType"));
        tblMolType->setEnabled(true);
        tblMolType->setGeometry(QRect(0, 0, 311, 201));
        tblMolType->setSelectionMode(QAbstractItemView::NoSelection);

        retranslateUi(dlgDataDialog);

        QMetaObject::connectSlotsByName(dlgDataDialog);
    } // setupUi

    void retranslateUi(QDialog *dlgDataDialog)
    {
        dlgDataDialog->setWindowTitle(QApplication::translate("dlgDataDialog", "Data Summary", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tblAttributes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("dlgDataDialog", "Cell Type", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tblAttributes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("dlgDataDialog", "Attribute", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tblAttributes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("dlgDataDialog", "Value", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tblCellType->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("dlgDataDialog", "Cell Type", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tblCellType->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("dlgDataDialog", "Population", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tblMolType->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QApplication::translate("dlgDataDialog", "Mol. Type", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tblMolType->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QApplication::translate("dlgDataDialog", "Moles/ml", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgDataDialog: public Ui_dlgDataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATADIALOG_H
