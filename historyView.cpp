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
 * file historyView.cc                                                  * 
 * render() routine for HistoryView                                     *    
 * Graphs cell populations and molecular concentrations over time       * 
 * This version plots with wx/GTK instead of openGL - can use text      * 
 ************************************************************************/
                                                                        
#include "historyView.h"
#include <GL/gl.h>  
#include "history.h"

/************************************************************************ 
 * HistoryView()                                                        *
 *   Constructor                                                        *
 *                                                                      *
 * Parameters                                                           *
 *   int x, y, w, h:        position (x,y) and size (w,h) of view       *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
HistoryView::HistoryView(QWidget *parent, int x, int y, int w, int h, 
                           const History *hist) 
	: SimView(parent, x, y, w, h), history(hist), m_first(true)
{
  m_border = 100;
	QRect	geo = geometry();
	m_height = geo.height();
	m_width = geo.width();
}

void HistoryView::paintEvent(QPaintEvent * /* event */)
{
	QPainter painter(this);
	
  // get number of samples taken and max value for each axis
  const vector<double> times = history->getTimes();
  int numsamples = times.size();
  double maxTime = times[numsamples-1];
  int maxCells = history->getMaxCount();
  double maxConc = history->getMaxConc();

	// Set Painter Properties
	painter.setPen(Qt::black);
	painter.setFont(QFont("Modern", 10));

	// Draw the graph's axes
	drawAxes(painter, maxTime, maxCells, maxConc);

	// Only plot if there are two more more data points
	if (numsamples > 1)
	{
		// Get the data
		History::CellHistory counts;
		History::ConcHistory concs;

    int t0 = m_border;
    int tmax = m_width-m_border;
    double tscale = (tmax-t0)/maxTime;
    int y0 = m_height-m_border;
    int ymax = m_border;

    // Cell counts first - scale according to max count so far
    if (maxCells == 0)
    {
      if (int last = history->getNumCellTypes())  
      {
        // just draw one line (last color) along x axis
				painter.setPen(QColor(cell_palette[last].red(), 
				                      cell_palette[last].green(),
				                      cell_palette[last].blue()));
				painter.drawLine(t0, y0, tmax, y0);
      }
    }
		else {
			double yscale = (y0-ymax)/double(maxCells);

			// Each loop handles drawing one cell type
			for (int i=0; i<history->getNumCellTypes(); i++) {
				counts = history->getCounts(i);
				
				// Set color according to palette 
				painter.setPen(QColor(cell_palette[i].red(), cell_palette[i].green(),
				                cell_palette[i].blue()));

				for (int j=0; j<numsamples-1; j++)
					painter.drawLine(int(tscale*times[j]+t0), y0-int(yscale*counts[j]),
					              int(tscale*times[j+1] + t0), y0 - int(yscale*counts[j+1]));
      }	// end for loop
    }	// end if maxCells not 0

		// Rescale for molecular concentrations
		if (maxConc == 0)	{
			if (int last = history->getNumMolTypes()) {
        // Just draw one line (last color) along the x-axis
        painter.setPen(QColor(mol_palette[last].red(), mol_palette[last].green(),
				                        mol_palette[last].blue()));
				painter.drawLine(t0, y0, tmax, y0);
      }
    }
		else {
			double yscale = (y0-ymax)/maxConc;

			// Each loop handles drawing one molecule type
			for (int i=0; i<history->getNumMolTypes(); i++) {
				concs = history->getConc(i);

        // Set color according to palette 
        painter.setPen(QColor(mol_palette[i].red(), mol_palette[i].green(),
				                        mol_palette[i].blue()));
				for (int j=0; j<numsamples-1; j++)
					painter.drawLine(int(tscale*times[j] + t0), y0 - int(yscale*concs[j]),
					                   int(tscale*times[j+1] + t0), y0 - int(yscale*concs[j+1]));
      }	// end for loop
    } // end if maxConc not 0
	} // end if more than one sample
}

/************************************************************************ 
 * render()                                                             *
 *   Qt code to draw history of sim                                     *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void HistoryView::render()
{

}

/************************************************************************ 
 * drawAxes()                                                           *
 *   Sets up xaxis (time) and 2 yaxes (one for cells and one for        *
 *     molecules)                                                       *
 *                                                                      *
 * Parameters -                                                         *
 *   double maxTime:      max value on y axis                           *
 *   int maxCells:        max value on left y axis                      *
 *   double maxConc:      max value on right y axis                     *
 *                                                                      *
\ * Returns - nothing                                                   *
 ************************************************************************/
void HistoryView::drawAxes(QPainter &painter, double maxTime, 
                             int maxCells, double maxConc)
{
	QString str;

  // Draw lines for axes
	painter.drawLine(m_border, m_border, m_border, m_height - m_border);
	painter.drawLine(m_border, m_height - m_border, 
	                   m_width - m_border, m_height - m_border);
	painter.drawLine(m_width - m_border, m_height - m_border, 
	                   m_width - m_border, m_border);

	// X-Axis Label
	painter.drawText(m_width/2-100, 
	                 m_height-(3*m_border/4)-25, 
	                 200,
	                 50,
	                 Qt::AlignCenter,
	                 tr("Time (sec)"));

	painter.save();
	painter.rotate(-90);

	// Left Y-Axis Label
	painter.drawText(-m_height/2-100, 
  	               (3*m_border)/4-25, 
  	               200,
  	               50,
  	               Qt::AlignCenter,
	                 tr("# of Cells"));

	// Right Y-Axis Label
	painter.drawText(-m_height/2-100, 
	                 m_width-(3*m_border)/4-25, 
  	               200,
  	               50,
  	               Qt::AlignCenter,
  	               tr("Concentration (Moles/ml)"));

	painter.restore();

	// X-Axis Max Value
	str.sprintf("%.1f", maxTime);
	painter.drawText(m_width-m_border-100,
	                 height-4*m_border/5-25,
	                 200,
	                 50,
	                 Qt::AlignCenter,
	                 str);

	// Left Y-Axis Max Value
	str.sprintf("%d", maxCells);
	painter.drawText(m_border/2-100,
	                 m_border-25,
	                 200,
	                 50,
	                 Qt::AlignCenter,
	                 str);

	// Right Y-Axis Max Value
	str.sprintf("%.1e", maxConc);
	painter.drawText(m_width-m_border/2-100,
	                 m_border-25,
	                 200,
	                 50,
	                 Qt::AlignCenter,
	                 str);
}

