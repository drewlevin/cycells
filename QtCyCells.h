/************************************************************************
 *                                                                      *
 * Copyright (C) 2007  Christina Warrender and Drew Levin               *
 *                                                                      *
 * This file is part of QtCyCells.                                      *
 *                                                                      *
 * QtCyCells is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * QtCyCells is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with QtCyCells; if not, write to the Free Software Foundation, *
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA        *
 *                                                                      *
 ************************************************************************/
/************************************************************************
 * File: QtCyCells.h                                                    *
 *   Main Dialog Class for QtCyCells                                    *
 * Catches interface events and sends them to the engine thread.        *
 ************************************************************************/

#ifndef _QTCYCELLS_H_
#define _QTCYCELLS_H_

#include <QDialog>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QStringList>

#include "QtEngineThread.h"
#include "ui_QtCyCells.h"


class QtDataDialog;
class Tissue;

class QtCyCells : public QDialog, private Ui::QtCyCells
{
  Q_OBJECT

  public:

    QtCyCells(QWidget *parent = 0);
		~QtCyCells();

  //----------------------- EVENT HANDLERS ------------------------------- 
  public slots:
    void onLoadDef();
    void onLoadInit();
    void onRun();
    void onSetSeed();
    void onSetDur();
    void onSetUpdate();
    void onSetStep();
    void onSetView();
    void onWriteHistory();
    void onWriteDetail();

    // GUI Display Update Notifications
    void updateTypes(int cells, int mols);
    void updateGeometry(QString geometry);
    void updateTime(QString time);
    void updateStatus(QString status);
//		void updateDialog(Tissue *tissue);

  signals:
    void loadDef(QString qsFileName);
		void loadInit(QString qsFileName);
    void setSeed(int seed);
    void setDur(int dur);
    void setUpdate(int update);
    void setStep(double timestep);
    void setView(QString qsView, QWidget *widget);
    void writeHistory(QString qsFileName);
    void writeDetail(QString qsFileName);
    void toggleRun();

  private:

    QtEngineThread *m_engine;	// Run all computation in a separate thread
	
    QtDataDialog *m_dialog; // Display of current data
};

#endif // _QTCYCELLS_H_

