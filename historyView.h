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
 * file historyView.h                                                   *
 * Declarations for HistoryView class                                   * 
 * Shows graph of population levels and average concentrations          * 
 * Derived from abstract class SimView                                  *
 ************************************************************************/

#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <QPaintEvent>
#include <QPainter>

#include "simView.h"

class History;

class HistoryView : public SimView   
{
  public:
    HistoryView(QWidget *parent, int x, int y, int w, int h, 
		              const History *hist);
		void render();

	protected:
		void paintEvent(QPaintEvent *event);

	private:
		const History *history;
		bool m_first;

		int m_height;		// Height of viewing area
		int m_width;		// Width of viewing area
		int m_border;		// Width of area outside graph axes

		void drawAxes(QPainter &painter, double maxTime, 
		                int maxCells, double maxConc);
};

#endif

