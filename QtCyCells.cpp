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
 * File: QtCyCells.cpp                                                  *
 * Main Dialog functionality for QtCyCells                              *
 *   Will trap GUI events and send them to the QtEngineThread for       *
 * handling.                                                            *
 ************************************************************************/

#include <cassert>
#include <iostream>

#include "QtCyCells.h"
#include "tissue.h"
#include "history.h"
#include "fileDef.h"
#include "fileInit.h"
#include "dataDialog.h"
#include "simView3D.h"
#include "historyView.h"

/************************************************************************ 
 * QtCyCells()                                                          *
 *   Constructor                                                        *
 *                                                                      *
 * Parameters                                                           *
 *   QWidget *parent			Parent Widget (Default NULL for no parent)    *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
QtCyCells::QtCyCells(QWidget *parent)
	: QDialog(parent), m_dialog(0)
{ 	
	// Initialize the Dialog Form defined in ui_QtCyCells.h
	setupUi(this);

	// Initialize display values
//	txtMoleculeTypes->setText(QString::number(m_tissuep->getNumMolTypes()));
//	txtCellTypes->setText(QString::number(m_tissuep->getNumCellTypes()));

//	QString geometry;
//	getGeometryInfo(geometry);
//	txtGeometry->setText(geometry);

  // Engine Thread
	m_engine = new QtEngineThread(this);

	// Events: Connects buttons to their respective functions
	connect(pbDefineFromFile, SIGNAL(clicked()), this, SLOT(onLoadDef()));
	connect(pbInitFromFile, SIGNAL(clicked()), this, SLOT(onLoadInit()));
	connect(pbRun, SIGNAL(clicked()), this, SLOT(onRun()));
	connect(pbSetSeed, SIGNAL(clicked()), this, SLOT(onSetSeed()));
	connect(pbDuration, SIGNAL(clicked()), this, SLOT(onSetDur()));
	connect(pbDisplayUpdate, SIGNAL(clicked()), this, SLOT(onSetUpdate()));
	connect(pbTimestep, SIGNAL(clicked()), this, SLOT(onSetStep()));
	connect(pbView, SIGNAL(clicked()), this, SLOT(onSetView()));
	connect(pbWriteHistory, SIGNAL(clicked()), this, SLOT(onWriteHistory()));
	connect(pbWriteSnapshot, SIGNAL(clicked()), this, SLOT(onWriteDetail()));

	// More Events: Connect the GUI events to their engine counterparts
	connect(this, SIGNAL(loadDef(QString)), m_engine, SLOT(onLoadDef(QString)));
	connect(this, SIGNAL(loadInit(QString)), m_engine, SLOT(onLoadInit(QString)));
	connect(this, SIGNAL(setSeed(int)), m_engine, SLOT(onSetSeed(int)));
	connect(this, SIGNAL(setDur(int)), m_engine, SLOT(onSetDur(int)));
	connect(this, SIGNAL(setUpdate(int)), m_engine, SLOT(onSetUpdate(int)));
	connect(this, SIGNAL(setStep(double)), m_engine, SLOT(onSetStep(double)));
	connect(this, SIGNAL(setView(QString,QWidget*)), m_engine, SLOT(onSetView(QString,QWidget*)));
	connect(this, SIGNAL(writeHistory(QString)), m_engine, SLOT(onWriteHistory(QString)));
	connect(this, SIGNAL(writeDetail(QString)), m_engine, SLOT(onWriteDetail(QString)));
	connect(this, SIGNAL(toggleRun()), m_engine, SLOT(toggleRun()));

  // Even More Events: Connect display updates to the engine thread
	connect(m_engine, SIGNAL(updateTypes(int,int)), this, SLOT(updateTypes(int,int)));
	connect(m_engine, SIGNAL(updateGeometry(QString)), this, SLOT(updateGeometry(QString)));
	connect(m_engine, SIGNAL(updateTime(QString)), this, SLOT(updateTime(QString)));
	connect(m_engine, SIGNAL(updateStatus(QString)), this, SLOT(updateStatus(QString)));

	gfxView->hide();

	// Run the engine's main execution loop
	m_engine->start();
}

/************************************************************************ 
 * ~QtCyCells()                                                         *
 *   Destructor - Ends the engine thread when the program is closed.    *
 *                                                                      *
 * Returns - Nothing                                                    *
 ***********************************************************************/
QtCyCells::~QtCyCells()
{
	m_engine->quit();
}

/************************************************************************ 
 * onLoadDef()                                                          *
 *   Event handler for Define From File button                          *
 * Get the file name and send it to the engine thread.                  *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtCyCells::onLoadDef()
{
	QMessageBox::StandardButton choice;
	QString qsFileName;

  if (m_engine->getStatus())		// should only define from file if status is BLANK (0)
  {
    // Prompt to proceed by deleting Tissue and starting over, or cancel
		choice = QMessageBox::question(this, "Warning", 
		                "Redefining model will discard existing model.  Continue?",
		                QMessageBox::Cancel | QMessageBox::Ok, QMessageBox::Ok);

		if (choice == QMessageBox::Cancel)
      return;  
	}

	// Get the path of the definition file
	qsFileName = QFileDialog::getOpenFileName(this, tr("Load Model Definition"), 
	               "", tr("Definition Files (*.def)"));

	// Load the definition (if one is found)
  if (qsFileName != tr(""))
		emit loadDef(qsFileName);
}

/************************************************************************ 
 * onLoadInit()              m_viewInterval(100)                        *
 *   Event handler for Initialize From File button                      *
 * Get the file name and send it to the engine thread.                  *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtCyCells::onLoadInit()
{
	QString qsFileName;

	// If Tissue hasn't been defined, initializing from file won't work 
  if (m_engine->getStatus() == BLANK)	
  {
		QMessageBox::warning(this, tr("Warning"), 
		                     tr("Model must be defined before initializing"), 
		                     QMessageBox::Ok, QMessageBox::Ok);
    return;
  }

	// Reinitialization
  if (m_engine->getStatus() > DEFINED)
  { 
		// Just warn - option to cancel given below
		QMessageBox::warning(this, tr("Warning"), 
		                     tr("Reinitializing"), 
		                     QMessageBox::Ok, QMessageBox::Ok);
  }

	// Get the path of the initialization file
	qsFileName = QFileDialog::getOpenFileName(this, 
	               tr("Load Model Initialization"), 
	               "", tr("Initialization Files (*.init)"));

  if (qsFileName != tr(""))
		emit loadInit(qsFileName);
}


/************************************************************************ 
 * update()                                                             *
 *   Updates display(s)                                                 *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
//void QtCyCells::update()
//{
  // update time display
//  QString str;
//	str.sprintf("Elapsed time = %.1f seconds", m_tissuep->getTime());
//  lblTimeElapsed->setText(str);

//  // update view & msg about what view this is
//  if (m_viewp)
//    m_viewp->update();

//  // update text display of cell counts & concentration data
//  m_dialog->update(*m_historyp);
//}

/************************************************************************ 
 * onRun()                                                              *
 *   onRun is the actual Event handler for the Run button               *
 * Sends the signal to the engine thread if the model is initialized    *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtCyCells::onRun()
{
	// Can't Run without initialization
	if (m_engine->getStatus() == BLANK || m_engine->getStatus() == DEFINED)
			QMessageBox::warning(this, tr("Warning"), 
		                     tr("Model has not been initialized"), 
		                     QMessageBox::Ok, QMessageBox::Ok);
	else
		emit toggleRun();
}

/************************************************************************ 
 * onSetSeed()                                                          *
 *   Event handler for Set Seed button                                  *
 * Brings up dialog box to set RNG seed, sends value to the engine      *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtCyCells::onSetSeed()
{
	bool ok;
	int seed = QInputDialog::getInteger(this, tr("Enter Seed"), tr("Set Seed"), 
	             m_engine->getSeed(), 0, 2000000000, 1, &ok);
	if (ok)
		emit setSeed(seed);
}

/************************************************************************ 
 * onSetDur()                                                           *
 *   Event handler for Set Duration button                              *
 * Brings up dialog box to set simulation timestep, sends value to the  *
 *   engine thread.                                                     *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtCyCells::onSetDur()
{

	bool ok;
	int duration = QInputDialog::getInteger(this, tr("Enter Duration"), 
	                 tr("Set Duration"), m_engine->getDuration(), 1, 10000000, 1, &ok);
	if (ok)
		emit setDur(duration);
}

/************************************************************************ 
 * onSetUpdate()                                                        *
 *   Event handler for Set Display Update Rate                          *
 * Brings up dialog box to set display update interval                  *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtCyCells::onSetUpdate()
{
	bool ok;
	int interval = QInputDialog::getInteger(this, tr("Enter Update Interval"), 
	                 tr("Set Update Rate"), m_engine->getInterval(), 1, 1000000, 1, &ok);
	if (ok)
		emit setUpdate(interval);
}

/************************************************************************ 
 * onSetStep()                                                          *
 *   Event handler for Set Timestep button                              *
 *   Brings up dialog box to set simulation timestep                    *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtCyCells::onSetStep()
{
	QStringList items;
	bool ok;
  double temp;
	double constraint;
	int size;
	
	items << tr("1 Second") << tr("6 Seconds") << tr("10 Seconds") 
        << tr("1 Minute") << tr("1 Hour");

	QString item = QInputDialog::getItem(this, tr("Select Timestep"),
                                  tr("Select Timestep"), items, 0, false, &ok);
	if (ok) {
		if (item == tr("1 Second")) 
			temp = 1;
		else if (item == tr("6 Seconds")) 
			temp = 6;
		else if (item == tr("10 Seconds")) 
			temp = 10;
		else if (item == tr("1 Minute")) 
			temp = 60;
		else if (item == tr("1 Hour")) 
			temp = 3600;
	}
	else
		return;

	// Make sure timestep not too big for spatial resolution:
  size = m_engine->getGridSize();
  if (size)
  {
    constraint = size*size / m_engine->getMaxDiffRate();
    if (temp > constraint)
    {
			QMessageBox::warning(this, tr("Warning"), 
		                       tr("Timestep too big for grid size; not changed"), 
		                       QMessageBox::Ok, QMessageBox::Ok);      
    }
		else
			emit setStep(temp);
  }
	else
		emit setStep(temp);
}

/************************************************************************ 
 * onSetView()                                                          *
 *   Event handler for Set View button                                  *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtCyCells::onSetView()
{
	QStringList items;
  Tissue *tissue;
  char mol_name[256];
	bool ok;


  tissue = m_engine->getTissue();

	items << tr("History View") << tr("3D View") << tr("None");

  if (tissue)
  {
    for (int i=0; i<tissue->getNumMolTypes(); i++)
    {
      items << tr(tissue->getMolecule(i).getName().c_str());
    }
  }

	QString item = QInputDialog::getItem(this, tr("Select View"),
	                               tr("Select View"), items, 0, false, &ok);
	if (ok)
		emit setView(item, this);
}

/************************************************************************ 
 * onWriteHistory                                                       *
 *   Event handler for WriteHistory button                              *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtCyCells::onWriteHistory()
{
	QString qsFileName;
	QByteArray baFileName;
	const char *pzFileName;

	if (m_engine->getStatus() == BLANK || m_engine->getStatus() == DEFINED) {
		QMessageBox::warning(this, tr("Error"), 
		                 tr("Must initialize model first"), 
		                 QMessageBox::Ok, QMessageBox::Ok);     
		return;
	}

	// Get the path for the history file
	qsFileName = QFileDialog::getSaveFileName(this, tr("Save History"), 
	               "", tr("History Files (*.hist)"));

	// Convert from QString to char*
	baFileName = qsFileName.toLatin1();	pzFileName = baFileName.data();

	if (qsFileName != tr(""))
	{
		ofstream outfile(pzFileName);
		if (!outfile) {
			QMessageBox::warning(this, tr("Error"), 
			                 tr("Not a valid filename"), 
			                 QMessageBox::Ok, QMessageBox::Ok);     
			outfile.close();
		}
		else 
		{
			outfile.close();		
			emit writeHistory(qsFileName);
		}
	}
}

/************************************************************************ 
 * onWriteDetail                                                        *
 *   Event handler for WriteDetail button                               *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtCyCells::onWriteDetail()
{
	QString qsFileName;
	QByteArray baFileName;
	const char *pzFileName;

	if (m_engine->getStatus() == BLANK || m_engine->getStatus() == DEFINED) {
		QMessageBox::warning(this, tr("Error"), 
		                 tr("Must initialize model first"), 
		                 QMessageBox::Ok, QMessageBox::Ok);     
		return;
	}

	// Get the path for the history file
	qsFileName = QFileDialog::getSaveFileName(this, tr("Save Snapshot"), 
	               "", tr("Detail Files (*.detail)"));

	// Convert from QString to char*
	baFileName = qsFileName.toLatin1();	pzFileName = baFileName.data();

	if (qsFileName != tr(""))
	{
		ofstream outfile(pzFileName);
		if (!outfile)
		{
			QMessageBox::warning(this, tr("Error"), 
			                 tr("Not a valid filename"), 
			                 QMessageBox::Ok, QMessageBox::Ok);      
			outfile.close();		
		}
		else
		{
			outfile.close();
			emit writeDetail(qsFileName);
		}
	}
}

/************************************************************************ 
 * updateTypes()                                                        *
 *   Updates GUI display of number of different cell and molecule types *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtCyCells::updateTypes(int cells, int mols)
{
  // update info on Model Definition page
  txtMoleculeTypes->setText(QString::number(mols));
  txtCellTypes->setText(QString::number(cells));
}

/************************************************************************ 
 * updateGeometry()                                                     *
 *   Updates GUI display of simulation size and resolution              *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtCyCells::updateGeometry(QString geometry)
{
	txtGeometry->setText(geometry);
}

/************************************************************************ 
 * updateTime()                                                         *
 *   Updates GUI display of number of timesteps the simulation has run  *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtCyCells::updateTime(QString time)
{
  lblTimeElapsed->setText(time);
}

/************************************************************************ 
 * updateStatus()                                                       *
 *   Updates the text on the 'Run' button                               *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtCyCells::updateStatus(QString status)
{
  	pbRun->setText(status);
}
