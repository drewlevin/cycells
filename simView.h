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
 * File simView.h                                                       *
 * Declarations for abstract SimView class -                            * 
 *   derived classes must define render()                               * 
 * Derived from QGLWidget; needed in order to use use openGL rendering  *
 *   commands in Qt window frame                                        *
 ************************************************************************/

#ifndef _SIMVIEW_H_
#define _SIMVIEW_H_

#include <QDialog>
#include <QWidget>
#include <QGLWidget>

#include <vector>
#include "color.h"

class SimView : public QGLWidget
{
	Q_OBJECT

	public:
		SimView(QWidget *parent = 0, int x = 0, int y = 0, int w = 0, int h = 0);
		virtual void render() = 0;    // specific to derived classes

	protected:
		int width, height;            
		vector<Color> mol_palette;    // Colors to use for molecules
		vector<Color> cell_palette;   // ... and cells (by index)

		bool save_image, draw_time;

		void initializeGL();
		void resizeGL(int w, int h);
		void paintGL();
};

#endif // _SIMVIEW_H_

