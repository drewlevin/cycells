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
 * File simView.cc                                                      * 
 * Routines for SimView class                                           *    
 * Generic tissue display - derived classes must define render()        * 
 ************************************************************************/
                                                                        
#include "simView.h"
#include <GL/gl.h>  

/************************************************************************ 
 * SimView()                                                            *
 *   Constructor                                                        *
 *   Sets up (hard-coded) color palettes                                *
 *                                                                      *
 * Parameters                                                           *
 *   QWidget *parent:     window containing this view                   *
 *   int x, y, w, h:      position (x,y) and size (w,h) of view         *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
SimView::SimView(QWidget *parent, int x, int y, int w, int h)
	: QGLWidget(parent), width(w), height(h)
{
	save_image = false;
  draw_time = true;

	setGeometry(x, y, w, h);

  int alpha = 63;		// Used for blending molecule colors

  // Molecule colors
  mol_palette.push_back(Color(128,128,128,alpha));
  mol_palette.push_back(Color(128,128,0,alpha));
  mol_palette.push_back(Color(0,128,128,alpha));
  mol_palette.push_back(Color(128,0,128,alpha));
  mol_palette.push_back(Color(0,0,128,alpha));
  mol_palette.push_back(Color(0,128,0,alpha));
  mol_palette.push_back(Color(128,0,0,alpha));

  // Cell colors
  cell_palette.push_back(Color(0xC0, 0xC0, 0xC0));
  cell_palette.push_back(Color(0xFF, 0xE8, 0x00));
  cell_palette.push_back(Color(0xFF, 0x5F, 0x00));
  cell_palette.push_back(Color(0x77, 0x2F, 0x00));
  cell_palette.push_back(Color(0xCC, 0x00, 0x00));
  cell_palette.push_back(Color(0x00, 0x80, 0x00));
  cell_palette.push_back(Color(0x3A, 0x9F, 0xCF));
  cell_palette.push_back(Color(0x3A, 0x9F, 0xCF));
  cell_palette.push_back(Color(0x3A, 0x9F, 0xCF));
  cell_palette.push_back(Color(255,128,255));
  cell_palette.push_back(Color(128,128,128));
  cell_palette.push_back(Color(255,255,255));
  cell_palette.push_back(Color(255,255,255));
}

/************************************************************************ 
 * initializeGL()                                                       *
 *   Event handler for resizing window	                                *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/

void SimView::initializeGL()
{
	return;
}

/************************************************************************ 
 * sizeGL()                                                             *
 *   Event handler for resizing window	                                *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/

void SimView::resizeGL(int w, int h)
{
  width = w;
	height = h;
}

/************************************************************************ 
 * paintGL()                                                            *
 *   Event handler for (re)drawing view                                 *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/

void SimView::paintGL()
{
  render();			// OpenGL code for this view (subclasses only)
}


