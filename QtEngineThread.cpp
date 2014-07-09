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
 * File: QtEngineThread.cpp                                             *
 * Separate thread for engine execution                                 *
 ************************************************************************/

#include <cassert>
#include <iostream>
#include <gsl/gsl_statistics_double.h>

#include "QtEngineThread.h"
#include "tissue.h"
#include "history.h"
#include "fileDef.h"
#include "fileInit.h"
#include "dataDialog.h"
#include "simView.h"
#include "simView3D.h"
#include "simMolView3D.h"
#include "historyView.h"
#include "cells.h"

int counter = 0;

/************************************************************************ 
 * QtEngineThread()                                                     *
 *   Constructor                                                        *
 *                                                                      *
 * Parameters                                                           *
 *   QWidget *parent			Parent Widget (Default NULL for no parent)    *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
QtEngineThread::QtEngineThread(QObject *parent)
    : QThread(parent), m_status(BLANK), m_viewp(0), m_tissuep(0), m_historyp(0),
	  m_viewInterval(100), m_timestep(10), m_duration(86400)
{ 	
	// Setup the Idle Timer
	m_idleTimer = new QTimer(this);

	// Create tissue model - Sets seed & default model
	m_tissuep = new Tissue();

	// Initialize display values
	emit updateTypes(m_tissuep->getNumCellTypes(), m_tissuep->getNumMolTypes());

	QString geometry;
	getGeometryInfo(geometry);
	emit updateGeometry(geometry);

	// Idle Event Setup
	connect(m_idleTimer, SIGNAL(timeout()), this, SLOT(onIdle()));

	m_idleTimer->start();
}

/************************************************************************ 
 * onLoadDef()                                                          *
 *   Event handler for Define From File button                          *
 * Receives file name from main GUI
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtEngineThread::onLoadDef(QString qsFileName)
{
	QByteArray baFileName;
	const char *pzFileName;
  FileDef parser;

  if (m_status)		// Reset all values if there is a model already defined
  {
    setStatus(BLANK);
		delete(m_tissuep); 
    m_tissuep = new Tissue();
    delete(m_historyp); m_historyp = 0;
    delete(m_viewp); m_viewp = 0;
	}

	// Convert from QString to char*
	baFileName = qsFileName.toLatin1();	pzFileName = baFileName.data();

	// Define from file
  parser.defineFromFile(m_tissuep, pzFileName);
  setStatus(DEFINED);

  // Update cell and molecule type info
	emit updateTypes(m_tissuep->getNumCellTypes(), m_tissuep->getNumMolTypes());
}

/************************************************************************ 
 * onLoadInit()                                                         *
 *   Event handler for Initialize From File button                      *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtEngineThread::onLoadInit(QString qsFileName)
{
	QString geometry;
	QByteArray baFileName;
	const char *pzFileName;
  FileInit parser;

	// Reinitialization
  if (getStatus() > DEFINED)
  { 
    // reset simtime
    m_tissuep->setTime(0);

    // delete existing history; reinitialize it below           
    delete(m_historyp); 

    // have to delete view in case it's a history view
    delete(m_viewp); m_viewp = 0;
  }

	// Convert from QString to char*
	baFileName = qsFileName.toLatin1();	pzFileName = baFileName.data();

	// Initialize from file
  parser.initFromFile(m_tissuep, pzFileName);
  setStatus(INITIALIZED);
  setupHistory();

  // Update geometry info 
  getGeometryInfo(geometry);
	emit updateGeometry(geometry);


//    // also set up text display of current data
//    if (!m_dialog)
//      m_dialog = new QtDataDialog(this);
//
//   m_dialog->initialize(*m_tissuep);
//
//    update();
//
//		m_dialog->show();
}

/************************************************************************ 
 * getGeometryInfo(QString)                                             *
 *   Gets geometry description from Tissue object, assembles a string   *
 *   suitable for display on Model Definition page                      *
 *                                                                      *
 * Parameters                                                           *
 *   QString& str: 	string to display                              	    *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtEngineThread::getGeometryInfo(QString& str)
{
  str = QString("%1 x %2 x %3 microns\n%4 microns/grid edge")
		.arg(m_tissuep->getXSize()) .arg(m_tissuep->getYSize())
		.arg(m_tissuep->getZSize()) .arg(m_tissuep->getGridSize());
}

/************************************************************************ 
 * setupHistory()                                                       *
 *   Creates History object to record data during run and takes first   *
 *   sample - should only be called after Tissue initialized and        *
 *   before running.                                                    *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtEngineThread::setupHistory()
{
    assert(m_tissuep);
    m_historyp = new History(*m_tissuep, 0);
    m_historyp->sample(*m_tissuep);
}

/************************************************************************ 
 * update()                                                             *
 *   Updates display(s)                                                 *
 *                                                                      *
 * Returns - Nothing                                                    *
 ************************************************************************/
void QtEngineThread::update()
{
  // update time display
  QString str;
	str.sprintf("Elapsed time = %.1f seconds", m_tissuep->getTime());
  emit updateTime(str);

  // update view & msg about what view this is
  if (m_viewp)
    m_viewp->update();

//  // update text display of cell counts & concentration data
//  m_dialog->update(*m_historyp);
}

/************************************************************************ 
 * toggleRun()                                                          *
 *   toggleRun flips the status between RUNNING and STOPPED             *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtEngineThread::toggleRun()
{
  assert(m_tissuep);
  switch (getStatus())
  {
    case INITIALIZED: 	
      // Fall through to actually start sim running
    case STOPPED:	
      setStatus(RUNNING);
      emit updateStatus(tr("Stop"));
      break; 
    case RUNNING:
      setStatus(STOPPED);
			emit updateStatus(tr("Run"));
      update(); 		// display should reflect last changes to sim 
      break;
    default:				// Should be handled in the GUI thread
			break;
  }
}

/************************************************************************ 
 * onIdle                                                               *
 *   Actual simulation loop, but interruptable                          *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtEngineThread::onIdle()
{
  if (getStatus() == RUNNING)
  {
    int t = int(m_tissuep->getTime());
    if (t < m_duration)
    {
			m_lock.lockForWrite();
      m_tissuep->update(m_timestep);            // t now t + deltaT
      m_historyp->sample(*m_tissuep);
			m_lock.unlock();

      int n = int((t+m_timestep)/m_timestep);   // Number of steps taken
      if ((n % m_viewInterval) == 0)
        update();
    }
    else
    {
      if (counter < 0)
      {
        t = t % m_duration;
        onLoadInit(tr("/nfs/adaptive/drew/cycells2/cycells/models/plaque_single.init"));
        setStatus(RUNNING);
        counter++;
      }
      else
      {
        double mean, std;
        toggleRun();	// Stop automatically at specified duration
        Cells* cells = m_tissuep->getCellsPtr();
/*
// Comment START
        cout << "Fuzzy" << endl << "----------" << endl;
//        for (int i=0; i<50; i++)
//          cout << cells->fuzzy[i] << endl;
        mean = gsl_stats_mean(cells->fuzzy, 1, 50);
        std = gsl_stats_sd(cells->fuzzy, 1, 50);
        cout << mean << " " << std << endl << endl;
        cout << "Inside" << endl << "----------" << endl;
//        for (int i=0; i<50; i++)
//          cout << cells->inside[i] << endl;
        mean = gsl_stats_mean(cells->inside, 1, 50);
        std = gsl_stats_sd(cells->inside, 1, 50);
        cout << mean << " " << std << endl << endl;
        cout << "Perimeter" << endl << "----------" << endl;
//        for (int i=0; i<50; i++)
//          cout << cells->perimeter[i] << endl;
        mean = gsl_stats_mean(cells->perimeter, 1, 50);
        std = gsl_stats_sd(cells->perimeter, 1, 50);
        cout << mean << " " << std << endl << endl; 

        mean = gsl_stats_mean(cells->cell_count, 1, 50);
        std = gsl_stats_sd(cells->cell_count, 1, 50);
        cout << "Total Cells: " << mean << " " << std << endl;
        counter = 0;  
// Comment END
*/
      } 
    }
  }
}

/************************************************************************ 
 * onSetSeed()                                                          *
 *   Event handler for Set Seed button                                  *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtEngineThread::onSetSeed(int seed)
{
	m_tissuep->setSeed(seed);
}

/************************************************************************ 
 * onSetDur()                                                           *
 *   Event handler for Set Durationupdate                               *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtEngineThread::onSetDur(int duration)
{
	m_duration = duration;
}

/************************************************************************ 
 * onSetUpdate()                                                        *
 *   Event handler for Set Display Update Rate                          *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtEngineThread::onSetUpdate(int update)
{
	m_viewInterval = update;
}

/************************************************************************ 
 * onSetStep()                                                          *
 *   Event handler for Set Timestep button                              *
 *   Brings up dialog box to set simulation timestep                    *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtEngineThread::onSetStep(double timestep)
{
	m_timestep = timestep;
}

/************************************************************************ 
 * onSetView()                                                          *
 *   Event handler for Set View button                                  *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtEngineThread::onSetView(QString qsView, QWidget *widget)
{
	if (qsView == tr("History View")) {
		delete m_viewp;
		m_viewp = new HistoryView(widget, 0, 100, 601, 481, m_historyp);
//		gfxView->hide();
		m_viewp->show();
	}
	else if (qsView == tr("3D View")) {
		delete m_viewp;
		m_viewp = new SimView3D(widget, 0, 100, 601, 481, m_tissuep);
//		gfxView->hide();
		m_viewp->show();
	}	
	else if (qsView == tr("None")) {
		m_viewp->hide();
//		gfxView->hide();
	}
  else
  {
    for (int i=0; i<m_tissuep->getNumMolTypes(); i++)
    {
      if (qsView == tr(m_tissuep->getMolecule(i).getName().c_str()))
      {
        delete m_viewp;
        m_viewp = new SimMolView3D(widget, 0, 100, 601, 481, m_tissuep, i);
        m_viewp->show();
      }
    }
  }
}

/************************************************************************ 
 * onWriteHistory                                                       *
 *   Event handler for WriteHistory button                              *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtEngineThread::onWriteHistory(QString qsFileName)
{
	QByteArray baFileName;
	const char *pzFileName;

	// Convert from QString to char*
	baFileName = qsFileName.toLatin1();	pzFileName = baFileName.data();

	ofstream outfile(pzFileName);
	outfile << *m_historyp;
	outfile.close();		
}

/************************************************************************ 
 * onWriteDetail                                                        *
 *   Event handler for WriteDetail button                               *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtEngineThread::onWriteDetail(QString qsFileName)
{
	QByteArray baFileName;
	const char *pzFileName;
	char buf[400];

	// Convert from QString to char*
	baFileName = qsFileName.toLatin1();	pzFileName = baFileName.data();
	sprintf(buf, "%s", pzFileName);

	m_tissuep->writeData(buf);
}

/************************************************************************ 
 * getStatus                                                            *
 *   Thread-safe access to m_status                                     *
 *                                                                      *
 * Returns - State                                                      *
 ************************************************************************/
State QtEngineThread::getStatus()
{
	QReadLocker locker(&m_lock);
	return m_status;
}

/************************************************************************ 
 * getSeed                                                              *
 *   Thread-safe access to m_tissuep->getSeed()                         *
 *                                                                      *
 * Returns - int                                                        *
 ************************************************************************/
int QtEngineThread::getSeed()
{
	QReadLocker locker(&m_lock);
	return m_tissuep->getSeed();
}

/************************************************************************ 
 * getInterval                                                          *
 *   Thread-safe access to m_viewInterval                               *
 *                                                                      *
 * Returns - int                                                        *
 ************************************************************************/
int QtEngineThread::getInterval()
{
	QReadLocker locker(&m_lock);
	return m_viewInterval;
}

/************************************************************************ 
 * getTimestep                                                          *
 *   Thread-safe access to m_timestep                                   *
 *                                                                      *
 * Returns - double                                                     *
 ************************************************************************/
double QtEngineThread::getTimestep()
{
	QReadLocker locker(&m_lock);
	return m_timestep;
}

/************************************************************************ 
 * getDuration                                                          *
 *   Thread-safe access to m_duration                                   *
 *                                                                      *
 * Returns - long                                                       *
 ************************************************************************/
long QtEngineThread::getDuration()
{
	QReadLocker locker(&m_lock);
	return m_duration;
}

/************************************************************************ 
 * getGridSize                                                          *
 *   Thread-safe access to m_tissuep->getGridSize()                     *
 *                                                                      *
 * Returns - int                                                        *
 ************************************************************************/
int QtEngineThread::getGridSize()
{
	QReadLocker locker(&m_lock);
	return m_tissuep->getGridSize();
}

/************************************************************************ 
 * getMaxDiffRate                                                       *
 *   Thread-safe access to m_tissuep->getMaxDiffRate()                  *
 *                                                                      *
 * Returns - double                                                     *
 ************************************************************************/
double QtEngineThread::getMaxDiffRate()
{
	QReadLocker locker(&m_lock);
	return m_tissuep->getMaxDiffRate();
}

/************************************************************************ 
 * setStatus                                                            *
 *   Thread-safe access to m_status                                     *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void QtEngineThread::setStatus(State status)
{
	QWriteLocker locker(&m_lock);
	m_status = status;
}

/************************************************************************ 
 * setStatus                                                            *
 *   Thread-safe access to m_tissuep                                    *
 *                                                                      *
 * Returns - Tissue*                                                    *
 ************************************************************************/
Tissue* QtEngineThread::getTissue()
{
	QReadLocker locker(&m_lock);
	return m_tissuep;
}

