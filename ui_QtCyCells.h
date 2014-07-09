/********************************************************************************
** Form generated from reading UI file 'QtCyCells.ui'
**
** Created: Tue Apr 24 13:13:13 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCYCELLS_H
#define UI_QTCYCELLS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_QtCyCells
{
public:
    QPushButton *pbDefineFromFile;
    QPushButton *pbInitFromFile;
    QPushButton *pbRun;
    QPushButton *pbSetSeed;
    QPushButton *pbWriteHistory;
    QPushButton *pbWriteSnapshot;
    QPushButton *pbTimestep;
    QPushButton *pbView;
    QPushButton *pbDisplayUpdate;
    QLabel *lblMoleculeTypes;
    QLabel *lblGeometry;
    QLabel *lblCellTypes;
    QPushButton *pbDuration;
    QLineEdit *txtMoleculeTypes;
    QLineEdit *txtCellTypes;
    QTextEdit *txtGeometry;
    QLabel *lblTimeElapsed;
    QGraphicsView *gfxView;

    void setupUi(QDialog *QtCyCells)
    {
        if (QtCyCells->objectName().isEmpty())
            QtCyCells->setObjectName(QString::fromUtf8("QtCyCells"));
        QtCyCells->resize(602, 650);
        pbDefineFromFile = new QPushButton(QtCyCells);
        pbDefineFromFile->setObjectName(QString::fromUtf8("pbDefineFromFile"));
        pbDefineFromFile->setGeometry(QRect(0, 10, 121, 27));
        pbInitFromFile = new QPushButton(QtCyCells);
        pbInitFromFile->setObjectName(QString::fromUtf8("pbInitFromFile"));
        pbInitFromFile->setGeometry(QRect(0, 40, 121, 27));
        pbRun = new QPushButton(QtCyCells);
        pbRun->setObjectName(QString::fromUtf8("pbRun"));
        pbRun->setGeometry(QRect(0, 70, 121, 27));
        pbSetSeed = new QPushButton(QtCyCells);
        pbSetSeed->setObjectName(QString::fromUtf8("pbSetSeed"));
        pbSetSeed->setGeometry(QRect(480, 10, 121, 27));
        pbWriteHistory = new QPushButton(QtCyCells);
        pbWriteHistory->setObjectName(QString::fromUtf8("pbWriteHistory"));
        pbWriteHistory->setGeometry(QRect(480, 40, 121, 27));
        pbWriteSnapshot = new QPushButton(QtCyCells);
        pbWriteSnapshot->setObjectName(QString::fromUtf8("pbWriteSnapshot"));
        pbWriteSnapshot->setGeometry(QRect(480, 70, 121, 27));
        pbTimestep = new QPushButton(QtCyCells);
        pbTimestep->setObjectName(QString::fromUtf8("pbTimestep"));
        pbTimestep->setGeometry(QRect(170, 610, 121, 27));
        pbView = new QPushButton(QtCyCells);
        pbView->setObjectName(QString::fromUtf8("pbView"));
        pbView->setGeometry(QRect(300, 610, 121, 27));
        pbDisplayUpdate = new QPushButton(QtCyCells);
        pbDisplayUpdate->setObjectName(QString::fromUtf8("pbDisplayUpdate"));
        pbDisplayUpdate->setGeometry(QRect(430, 610, 121, 27));
        lblMoleculeTypes = new QLabel(QtCyCells);
        lblMoleculeTypes->setObjectName(QString::fromUtf8("lblMoleculeTypes"));
        lblMoleculeTypes->setGeometry(QRect(150, 10, 101, 31));
        lblGeometry = new QLabel(QtCyCells);
        lblGeometry->setObjectName(QString::fromUtf8("lblGeometry"));
        lblGeometry->setGeometry(QRect(150, 40, 61, 31));
        lblCellTypes = new QLabel(QtCyCells);
        lblCellTypes->setObjectName(QString::fromUtf8("lblCellTypes"));
        lblCellTypes->setGeometry(QRect(330, 10, 101, 31));
        pbDuration = new QPushButton(QtCyCells);
        pbDuration->setObjectName(QString::fromUtf8("pbDuration"));
        pbDuration->setGeometry(QRect(40, 610, 121, 27));
        txtMoleculeTypes = new QLineEdit(QtCyCells);
        txtMoleculeTypes->setObjectName(QString::fromUtf8("txtMoleculeTypes"));
        txtMoleculeTypes->setEnabled(true);
        txtMoleculeTypes->setGeometry(QRect(250, 10, 51, 29));
        txtMoleculeTypes->setReadOnly(true);
        txtCellTypes = new QLineEdit(QtCyCells);
        txtCellTypes->setObjectName(QString::fromUtf8("txtCellTypes"));
        txtCellTypes->setGeometry(QRect(400, 10, 51, 29));
        txtCellTypes->setReadOnly(true);
        txtGeometry = new QTextEdit(QtCyCells);
        txtGeometry->setObjectName(QString::fromUtf8("txtGeometry"));
        txtGeometry->setEnabled(true);
        txtGeometry->setGeometry(QRect(220, 40, 231, 45));
        txtGeometry->setReadOnly(true);
        lblTimeElapsed = new QLabel(QtCyCells);
        lblTimeElapsed->setObjectName(QString::fromUtf8("lblTimeElapsed"));
        lblTimeElapsed->setGeometry(QRect(10, 590, 581, 17));
        gfxView = new QGraphicsView(QtCyCells);
        gfxView->setObjectName(QString::fromUtf8("gfxView"));
        gfxView->setGeometry(QRect(0, 100, 601, 481));

        retranslateUi(QtCyCells);

        QMetaObject::connectSlotsByName(QtCyCells);
    } // setupUi

    void retranslateUi(QDialog *QtCyCells)
    {
        QtCyCells->setWindowTitle(QApplication::translate("QtCyCells", "CyCells", 0, QApplication::UnicodeUTF8));
        pbDefineFromFile->setText(QApplication::translate("QtCyCells", "Define From File", 0, QApplication::UnicodeUTF8));
        pbInitFromFile->setText(QApplication::translate("QtCyCells", "Initialize From File", 0, QApplication::UnicodeUTF8));
        pbRun->setText(QApplication::translate("QtCyCells", "Run", 0, QApplication::UnicodeUTF8));
        pbSetSeed->setText(QApplication::translate("QtCyCells", "Set Seed", 0, QApplication::UnicodeUTF8));
        pbWriteHistory->setText(QApplication::translate("QtCyCells", "Write History", 0, QApplication::UnicodeUTF8));
        pbWriteSnapshot->setText(QApplication::translate("QtCyCells", "Write Snapshot", 0, QApplication::UnicodeUTF8));
        pbTimestep->setText(QApplication::translate("QtCyCells", "Timestep", 0, QApplication::UnicodeUTF8));
        pbView->setText(QApplication::translate("QtCyCells", "View", 0, QApplication::UnicodeUTF8));
        pbDisplayUpdate->setText(QApplication::translate("QtCyCells", "Display Update", 0, QApplication::UnicodeUTF8));
        lblMoleculeTypes->setText(QApplication::translate("QtCyCells", "Molecule Types: ", 0, QApplication::UnicodeUTF8));
        lblGeometry->setText(QApplication::translate("QtCyCells", "Geometry", 0, QApplication::UnicodeUTF8));
        lblCellTypes->setText(QApplication::translate("QtCyCells", "Cell Types	", 0, QApplication::UnicodeUTF8));
        pbDuration->setText(QApplication::translate("QtCyCells", "Duration", 0, QApplication::UnicodeUTF8));
        txtGeometry->setHtml(QApplication::translate("QtCyCells", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        lblTimeElapsed->setText(QApplication::translate("QtCyCells", "Elapsed Time", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QtCyCells: public Ui_QtCyCells {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCYCELLS_H
