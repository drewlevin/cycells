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
 * File simView3D.cc                                                    * 
 *   render() routine for SimView3D                                     *    
 *   Allows 3D display of tissue model                                  * 
 ************************************************************************/
#include <GL/gl.h>                                                                          
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include "simView3D.h"
#include "tissue.h"
#include "cellType.h"

using namespace std;

#define MAX(x,y) x > y ? x : y

#define TURN_SENSITIVITY 200.0
#define ZOOM_SENSITIVITY 2400.0

/************************************************************************ 
 * SimView3D()                                                          *
 *   Constructor                                                        *
 *                                                                      *
 * Parameters                                                           *
 *   QWidget *parent:   Window containing this view                     *
 *   int x, y, w, h:    Position (x,y) and size (w,h) of view           *
 *   const Tissue *t;	  Pointer to model tissue                         *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
SimView3D::SimView3D(QWidget *parent, int x, int y, int w, int h, 
	const Tissue *t) 
	: SimView(parent, x, y, w, h), 
	  m_tissuep(t), m_first(true), m_mousedown(false), oldPos(0,0),
		m_anglex(0.0), m_angley(0.0), m_zoom(1.0), frame(0)
{
  // Get tissue size info (do once at beginning rather than repeatedly)
  m_xsize = m_tissuep->getXSize();
  m_ysize = m_tissuep->getYSize();
  m_zsize = m_tissuep->getZSize();
	m_maxlength = MAX(MAX(m_xsize, m_ysize), m_zsize);

  // Get some info about types of cells & molecules to display
  int numCellTypes = m_tissuep->getNumCellTypes();
  m_cellSizes = new double[numCellTypes];
  for (int i=0; i<numCellTypes; i++)
    m_cellSizes[i] = m_tissuep->getCellType(i)->getRadius();

  // For drawing cells as spheres
  quadratic=gluNewQuadric();  
  gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals
  gluQuadricTexture(quadratic, GL_TRUE);      // Create Texture Coords ( NEW )
}

/************************************************************************ 
 * render()                                                             *
 *   OpenGL code to draw current view of model                          *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void SimView3D::render()
{
  if (m_first)
  {
    // set up lighting 
    GLfloat light_position[] = { 1.0, 1.0, m_zsize*2, 0.0 };
		GLfloat light_position2[] = { m_xsize, m_ysize, m_zsize*2, 0.0};
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodel_ambient[] = { 0.9, 0.9, 0.9, 0.9 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);		
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glClearColor(1.0, 1.0, 1.0, 0.0);	// set white background; no blending
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    // set size/projection - should be in resize routine?
    glViewport(0, 0, width, height);	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-m_xsize/2*m_zoom, m_xsize/2*m_zoom, -m_ysize/2*m_zoom, m_ysize/2*m_zoom, 9*m_maxlength, 11*m_maxlength);

    m_first = false;
  }

  // clear; get ready to do model/view transformations
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Position and orient the camera
	gluLookAt(10*m_maxlength*sin(m_anglex)*cos(m_angley)+m_xsize/2, 
            10*m_maxlength*sin(m_angley)+m_ysize/2, 
            -10*m_maxlength*cos(m_anglex)*cos(m_angley)+m_zsize/2, 
            m_xsize/2, m_ysize/2, m_zsize/2, 0.0, 1.0, 0.0);

//	gluLookAt(10*m_maxlength*sin(m_anglex)*cos(m_angley)+m_xsize*(7.0/16), 
//            10*m_maxlength*sin(m_angley)+m_ysize*(7.0/16), 
//            -10*m_maxlength*cos(m_anglex)*cos(m_angley)+m_zsize/2, 
//            m_xsize*(7.0/16), m_ysize*(7.0/16), m_zsize/2, 0.0, 1.0, 0.0);

  renderCells();

  renderMolecules();   

	drawBorder();

  if (draw_time) drawTime();

  glFlush();

	if (save_image)	saveImage();

  swapBuffers();

	frame++;
}

/************************************************************************ 
 * saveImage()                                                          *
 *   private function to save current frame as an image file.           *
 *                                                                      *
 * Parameters - none                                                    *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void SimView3D::saveImage()
{
	makeCurrent();

	int pid = (int)getpid();

	printf("Frame: %5d\n", frame);
	QImage *screen = new QImage(grabFrameBuffer());
	screen->save(QString("/nfs/adaptive/drew/cycells2/cycells/frames/frame_%1_%2.png").arg(pid).arg(frame, 6, 10, QChar('0')), "PNG");
	delete screen;
}



/************************************************************************ 
 * renderCells()                                                        *
 *   OpenGL code to draw visible cells in model                         *
 *                                                                      *
 * Parameters - none                                                    *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void SimView3D::renderCells()
{
	glPolygonMode(GL_FRONT, GL_FILL);

  // set blending for opaque cells
  glBlendFunc(GL_ONE, GL_ZERO);

  // we want cell's material properties to be determined by color setting
  glEnable(GL_COLOR_MATERIAL);

  // get current list of cells
  vector<Cell *> cell_list = m_tissuep->getCellList();

  // display each cell in list
  for (unsigned int i=0; i<cell_list.size(); i++)
  {
    // get necessary info
    Cell *pc = cell_list[i];
    int type_index = pc->getTypeIndex();
    SimPoint pos = pc->getPosition();
    double radius = m_cellSizes[type_index];
    Color color = cell_palette[type_index];

    // set color, translate, scale & display
    glColor3fv(color.getfv());
    glPushMatrix();
      glTranslatef(pos.getX(), pos.getY(), pos.getZ());
      glScalef(radius, radius, radius);
      gluSphere(quadratic,1,12,12);
//			gluDisk(quadratic,0,1,12,1);
    glPopMatrix();
  }

  glDisable(GL_COLOR_MATERIAL);
}

/************************************************************************ 
 * renderMolecules()                                                    *
 *                                                                      *
 * Parameters - none                                                    *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void SimView3D::renderMolecules()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  // set blending for translucent molecules
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_MATERIAL);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  int numTypes = m_tissuep->getNumMolTypes();
  double max = 1E-18;
//  double max = 1.0;				

	int xnum = m_tissuep->getXSize()/m_tissuep->getGridSize();
	int ynum = m_tissuep->getYSize()/m_tissuep->getGridSize();
	int znum = m_tissuep->getZSize()/m_tissuep->getGridSize();
	  
  for (int n=0; n<numTypes; n++)
  {
    // get concentration data for this molecule type
    const Array3D<Molecule::Conc>& conc = m_tissuep->getConc(n);

    // get base color
    Color color = mol_palette[n];

    // loop through grid cells
    for (int i=1; i<=xnum; i++)
      for (int j=1; j<=ynum; j++)
        for (int k=1; k<=znum; k++)
        {
          double c = conc.at(i, j, k);

          // scale color according to concentration 
          if (c == 0)                     // nothing to draw
            continue;                     
          else if (c >= max)              // use unadjusted base color
            glColor4fv((color).getfv());
          else                            // scale color by concentration
					{
            glColor4fv((color*(c/max)).getfv());
					}

          // scale, translate by grid cell indices & draw
          glPushMatrix();
    	      glScalef(m_tissuep->getGridSize(), m_tissuep->getGridSize(), m_tissuep->getGridSize());
            glTranslatef(i-1.0, j-1.0, k-1.0);
            drawGrid();   
          glPopMatrix();
        }

  }	// end for each molecule type
	glDisable(GL_BLEND);
  glDisable(GL_COLOR_MATERIAL);
}

/************************************************************************ 
 * drawGrid()                                                           *
 *   OpenGL code to draw a grid cell; calling routine must handle       *
 * translation to appropriate location                                  *
 *                                                                      *
 * Parameters - none                                                    *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void SimView3D::drawGrid()
{
//	glPolygonMode(GL_FRONT);

  glBegin(GL_QUADS);
		// back
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);		
		// top
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);		
		// left
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);		
		// right
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);		
		// bottom
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, 0.0);		
		// front
		glVertex3f(0.0, 0.0, 1.0);
		glVertex3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(0.0, 1.0, 1.0);		
  glEnd();

//  glDisable(GL_COLOR_MATERIAL);
}

/************************************************************************ 
 * drawBorder()                                                         *
 *   OpenGL code to draw border box around the limits of the simulation *
 *                                                                      *
 * Parameters - none                                                    *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void SimView3D::drawBorder()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.4, 0.4, 0.4);

  glBegin(GL_QUADS);
		// back
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(m_xsize, 0.0, 0.0);
		glVertex3f(m_xsize, m_ysize, 0.0);
		glVertex3f(0.0, m_ysize, 0.0);		
		// top
		glVertex3f(0.0, m_ysize, m_zsize);
		glVertex3f(m_xsize, m_ysize, m_zsize);
		glVertex3f(m_xsize, m_ysize, 0.0);
		glVertex3f(0.0, m_ysize, 0.0);		
		// left
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, m_zsize);
		glVertex3f(0.0, m_ysize, m_zsize);
		glVertex3f(0.0, m_ysize, 0.0);		
		// right
		glVertex3f(m_xsize, 0.0, 0.0);
		glVertex3f(m_xsize, 0.0, m_zsize);
		glVertex3f(m_xsize, m_ysize, m_zsize);
		glVertex3f(m_xsize, m_ysize, 0.0);		
		// bottom
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, m_zsize);
		glVertex3f(m_xsize, 0.0, m_zsize);
		glVertex3f(m_xsize, 0.0, 0.0);		
		// front
		glVertex3f(0.0, 0.0, m_zsize);
		glVertex3f(m_xsize, 0.0, m_zsize);
		glVertex3f(m_xsize, m_ysize, m_zsize);
		glVertex3f(0.0, m_ysize, m_zsize);		
  glEnd();

  glDisable(GL_COLOR_MATERIAL);
}

/************************************************************************ 
 * drawTime  ()                                                         *
 *   OpenGL code to draw the simulation time in the upper left corner.  *
 *                                                                      *
 * Parameters - none                                                    *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void SimView3D::drawTime()
{
  const char *c;

  double time;
  int days, hours, minutes, seconds;
  char str_days[256];

  time = m_tissuep->getTime();
  days = (int)floor(time/86400);
  time -= days*86400;
  hours = (int)floor(time/3600);
  time -= hours*3600;
  minutes = (int)floor(time/60);
  seconds = (int)time-(minutes*60);

  if (days > 0) {
    sprintf(str_days, "Day %d ", days);
  } else {
    sprintf(str_days, "");
  }

  sprintf(time_string, "%s %d:%02d:%02d", str_days, hours, minutes, seconds);

  glEnable(GL_COLOR_MATERIAL);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
  glScalef(1, -1, 1);
  glTranslatef(0, -height, 0);
  glMatrixMode(GL_MODELVIEW);

  glPushMatrix();
  glLoadIdentity();

    glColor3d(0.1, 0.1, 0.1);

    glRasterPos2f(10, 28);
    for (c=time_string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glColor3d(0.9, 0.9, 0.9);

    glRasterPos2f(11, 29);
    for (c=time_string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

/************************************************************************ 
 * mousePressEvent()                                                    *
 *   QT4 function to track mouse dragging.                              *
 *                                                                      *
 * Parameters - event                                                   *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void SimView3D::mousePressEvent(QMouseEvent *event)
{
	oldPos = event->pos();
}

/************************************************************************ 
 * mouseMoveEvent()                                                     *
 *   QT4 function to track mouse dragging.  Only functions if the       *
 *   mouse button is pressed.  Reorients the OpenGL view.               *
 *                                                                      *
 * Parameters - event                                                   *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void SimView3D::mouseMoveEvent(QMouseEvent *event)
{
	// Only react to mouse dragging, not regular movement.
	if ((event->buttons() & Qt::LeftButton))
	{
		QPoint dxy = event->pos() - oldPos;
		oldPos = event->pos();

		m_anglex += dxy.x() / TURN_SENSITIVITY;
		m_angley += dxy.y() / TURN_SENSITIVITY;
		render();
	}
}

/************************************************************************ 
 * wheelEvent()                                                         *
 *   QT4 function to track the mouse wheel.  Zooms in and out by        *
 *   narrowing or widening the view frustum.                            *
 *                                                                      *
 * Parameters - event                                                   *
 *                                                                      *
 * Returns - nothing                                                    *
 ************************************************************************/
void SimView3D::wheelEvent(QWheelEvent *event)
{
	// Get mouse wheel rotation in 1/8 of a degree.
	// Most mouse wheels click every 15 degrees, or 120 delta units.
	double delta = (double)(event->delta());

	if (delta > 0) // Zoom in
		m_zoom *= 1 - (delta / ZOOM_SENSITIVITY);
	else           // Zoom Out		
		m_zoom /= 1 - (-delta / ZOOM_SENSITIVITY);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-m_xsize/2*m_zoom, m_xsize/2*m_zoom, -m_ysize/2*m_zoom, m_ysize/2*m_zoom, 9*m_maxlength, 11*m_maxlength);

	render();
}
