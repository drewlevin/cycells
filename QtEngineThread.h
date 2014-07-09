#ifndef _QTENGINETHREAD_H_
#define _QTENGINETHREAD_H_
 
#include <QtGui>
#include <QDialog>
#include <QWidget>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QStringList>
#include <QThread>
#include <QtCore>
#include "tissue.h"

class SimView;
class Tissue;
class History;

enum State { BLANK, DEFINED, INITIALIZED, RUNNING, STOPPED };

class QtEngineThread : public QThread
{
    Q_OBJECT
 
  public:
    QtEngineThread(QObject *parent);
    void run() {exec();}; // Immediately start execution loop upon entry

    State  getStatus();			// Thread-safe access to m_status
    int    getSeed();				// Thread-safe access to m_tissuep->getSeed()
		int    getInterval();		// Thread-safe access to m_viewInterval
		double getTimestep();		// Thread-safe access to m_timestep
		long   getDuration();   // Thread-safe access to m_duration
		int    getGridSize();   // Thread-safe access to m_tissuep->getGridSize()
		double getMaxDiffRate();// Thread-safe access to m_tissuep->getMaxDiffRate()
    Tissue *getTissue();

  public slots:

    //----------------------- EVENT HANDLERS ------------------------------- 
    void onLoadDef(QString qsFileName);
    void onLoadInit(QString qsFileName);
    void onSetSeed(int seed);
    void onSetDur(int duration);
    void onSetUpdate(int update);
    void onSetStep(double timestep);
    void onSetView(QString qsView, QWidget *widget);
    void onWriteHistory(QString qsFileName);
    void onWriteDetail(QString qsFileName);
    void toggleRun();
    void onIdle();

	signals:

		void updateTypes(int cells, int mols);
		void updateGeometry(QString geometry);
		void updateTime(QString time);
		void updateStatus(QString status);
		void updateDialog(Tissue *tissue);

  private:
    QTimer *m_idleTimer;    // Fires when there are no QT events
		
		QReadWriteLock m_lock;	// To provide locking capabilities for cross-thread data

    State m_status;         // Current state of simulation

    SimView *m_viewp;	      // Viewing Area

    Tissue *m_tissuep;      // Model

    History *m_historyp;    // Holds aggregate sim data

    int    m_viewInterval;  // How often to update displays
    double m_timestep;      // Time elapsed in one sim loop
    long   m_duration;      // Amount of time to run simulation (in seconds)

    // Private functions to manage simulation
    void getGeometryInfo(QString& str);
    void setupHistory();    // Creates & initializes History object
    void update();	        // Directs various display updates

		void setStatus(State status); // Thread-safe function to set status
};
 
 
#endif // _QTENGINETHREAD_H_

