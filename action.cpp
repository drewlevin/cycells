
/************************************************************************
 * 									*
 * Copyright (C) 2004  Christina Warrender				*
 * 									*
 * This file is part of CyCells.					*
 *									*
 * CyCells is free software; you can redistribute it and/or modify it 	*
 * under the terms of the GNU General Public License as published by	*
 * the Free Software Foundation; either version 2 of the License, or	*
 * (at your option) any later version.					*
 *									*
 * CyCells is distributed in the hope that it will be useful,		*
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	*
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	*
 * GNU General Public License for more details.				*
 *									*
 * You should have received a copy of the GNU General Public License	*
 * along with CyCells; if not, write to the Free Software Foundation, 	*
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA	*
 *									*
 ************************************************************************/
/************************************************************************
 * file action.cc                                                       *
 * Definitions for constructors and doAction() member functions of 	*
 * various Action classes.  						*
 * Each action object carries out a specific cell activity. 		*
 ************************************************************************/

#include "action.h"
#include "cellType.h"
#include "cells.h"
#include "cell.h"
#include "molecule.h"
#include "random.h"
#include "tallyActions.h"
#include "rate.h"
#include "simPoint.h"
#include <cmath>
#include <cassert>

#define MIN(x, y) ( x < y ? x : y )
#define MAX(x, y) ( x < y ? y : x )

using namespace std;

/************************************************************************
 * class ActionDie                                                      *
 ************************************************************************/
ActionDie::ActionDie()
{ 
  m_tap = TallyActions::getInstance();
  m_id = m_tap->addName("ActionDie"); 
} 		

void ActionDie::doAction(Cell *cell, double deltaT) 
{
  cell->die();
  m_tap->update(m_id);
}
  

/************************************************************************
 * class ActionInfect                                                   *
 ************************************************************************/
ActionInfect::ActionInfect(Molecule *pm, int index, double radius) : m_index(index), 
  m_pm(pm), m_radius(radius)
{ 
  m_tap = TallyActions::getInstance();
  m_id = m_tap->addName("ActionInfect"); 
} 		

void ActionInfect::doAction(Cell *cell, double deltaT) 
{
  if (m_pm->getTotalMols() > 1.0)
  {
//    double num_mols = m_pm->getInterpNumMolecules(6.9282*m_radius*m_radius, cell->getPosition());
//    if ((double)rand()/(RAND_MAX) < num_mols)
//    {
      cell->setTypeIndex(m_index);
      m_pm->removeMols(1, cell->getPosition());
//%    }
  }
  m_tap->update(m_id);
}

/************************************************************************
 * class ActionChange                                                   *
 ************************************************************************/
ActionChange::ActionChange(int index) : m_index(index) 
{ 
  m_tap = TallyActions::getInstance();
  m_id = m_tap->addName("ActionChange"); 
} 		

void ActionChange::doAction(Cell *cell, double deltaT) 
{
  cell->setTypeIndex(m_index);
  m_tap->update(m_id);
}

/************************************************************************
 * class ActionChangeIndex                                              *
 ************************************************************************/
ActionChangeIndex::ActionChangeIndex(int index, Cells *cells) : 
  m_cellindex(index), m_cells(cells)
{ 
  m_tap = TallyActions::getInstance();
  m_id = m_tap->addName("ActionChangeIndex"); 
} 		

void ActionChangeIndex::doAction(Cell *cell, double deltaT) 
{
  double tempDist;
  double minDist = 1e99;
  int attrIndex;
  int newIndex = 0;

  vector<Cell*> clist;
  vector<Cell*>::iterator itr;  
    
  m_cells->getNeighbors(cell, clist);

  for (itr = clist.begin(); itr != clist.end(); itr++)
  {
    attrIndex = m_cells->getCellType((*itr)->getTypeIndex())->getAttributeIndex("index");

    if (attrIndex > -1)
    {
      if ((*itr)->getValue(attrIndex) > 0)
      {
        tempDist = (*itr)->getPosition().dist(cell->getPosition());
        if (tempDist < minDist)
        {
          minDist = tempDist;
          newIndex = (*itr)->getValue(attrIndex);
        }
      }
    }
  }

  cell->setTypeIndex(m_cellindex);
  cell->setValue(m_cells->getCellType(m_cellindex)->getAttributeIndex("index"), newIndex);
  m_tap->update(m_id);
}

/************************************************************************
 * class ActionMoveRandomly                                             *
 ************************************************************************/
void ActionMoveRandomly::doAction(Cell *cell, double deltaT) 
{
  // pick new velocity vector
  // choose a random direction - values between -1 and 1    
  double x = 2*RandK::randk() - 1;
  double y = 2*RandK::randk() - 1;
  double z = 2*RandK::randk() - 1;

  // scale to unit magnitude 
  double sf = 1 / sqrt( x*x + y*y + z*z );
  cell->setDirection(SimPoint(x*sf, y*sf, z*sf));
}
  

/************************************************************************
 * class ActionMoveRandomly2D                                           *
 ************************************************************************/
void ActionMoveRandomly2D::doAction(Cell *cell, double deltaT) 
{
  // pick new velocity vector
  // choose a random direction - values between -1 and 1    
  double x = 2*RandK::randk() - 1;
  double y = 2*RandK::randk() - 1;

  // scale to unit magnitude                    
  double sf = 1 / sqrt( x*x + y*y );
  cell->setDirection(SimPoint(x*sf, y*sf, 0));
};


/************************************************************************
 * class ActionTurnRandomly                                             *
 ************************************************************************/
ActionTurnRandomly::ActionTurnRandomly(double std)
{
	m_std = std;
}

void ActionTurnRandomly::doAction(Cell *cell, double deltaT) 
{
  // pick new velocity vector
  // choose a random direction - values between -1 and 1    
  double x = 2*RandK::randk() - 1;
  double y = 2*RandK::randk() - 1;
  double z = 2*RandK::randk() - 1;

  // scale to unit magnitude 
  double sf = 1 / sqrt( x*x + y*y + z*z );
  cell->setDirection(SimPoint(x*sf, y*sf, z*sf));
}
  

/************************************************************************
 * class ActionTurnRandomly2D                                           *
 ************************************************************************/
ActionTurnRandomly2D::ActionTurnRandomly2D(double std)
{
	m_std = std;
}

void ActionTurnRandomly2D::doAction(Cell *cell, double deltaT) 
{
  // pick new velocity vector
  // choose a random direction based on the standard deviation of radians
	double angle = sampleGaussian(0, m_std);
	double theta, x, y;

	theta = atan2(cell->getDirection().getY(), cell->getDirection().getX()) + angle;

  cell->setDirection(SimPoint(cos(theta), sin(theta), 0));
};

/************************************************************************
 * class ActionDivide                                                   *
 ************************************************************************/
ActionDivide::ActionDivide(Cells *cells, int typeIndex) : 
	m_cells(cells), m_typeIndex(typeIndex) 
{ 
  m_tap = TallyActions::getInstance();
  m_id = m_tap->addName("ActionDivide"); 
} 	

void ActionDivide::doAction(Cell *cell, double deltaT) 
{
  // "kill" original cell and replace with two new cells
  SimPoint pos = cell->getPosition();
  m_cells->addCell(m_typeIndex, pos+SimPoint(0.1,0,0), true);
  m_cells->addCell(m_typeIndex, pos+SimPoint(-0.1,0,0), true);
  cell->die();
  m_tap->update(m_id);
}
  

/************************************************************************
 * class ActionAdmit                                                    *
 ************************************************************************/
ActionAdmit::ActionAdmit(int typeIndex, double dist, bool birth, Cells *cells) : 
	m_typeIndex(typeIndex), m_dist(dist), m_flag(birth), m_cells(cells) 
{ 
  assert(m_typeIndex>=0); 		
  m_tap = TallyActions::getInstance();
  m_id = m_tap->addName("ActionAdmit"); 
} 	

void ActionAdmit::doAction(Cell *cell, double deltaT) 
{
  // choose a random direction - values between -1 and 1    
  double x = 2*RandK::randk() - 1;
  double y = 2*RandK::randk() - 1;
  double z = 2*RandK::randk() - 1;
	                             
  // scale to appropriate magnitude 
  double sf = m_dist / sqrt( x*x + y*y + z*z );
  SimPoint newpos = cell->getPosition() + SimPoint(x*sf, y*sf, z*sf);
  m_cells->addCell(m_typeIndex, newpos, m_flag);
  m_tap->update(m_id);
}
  

/************************************************************************
 * class ActionAdmit2D                                                  *
 ************************************************************************/
ActionAdmit2D::ActionAdmit2D(int typeIndex, double dist, bool birth, Cells *cells) : 
	m_typeIndex(typeIndex), m_dist(dist), m_flag(birth), m_cells(cells) 
{ 
  assert(m_typeIndex>=0); 		
  m_tap = TallyActions::getInstance();
  m_id = m_tap->addName("ActionAdmit2D"); 
} 	

void ActionAdmit2D::doAction(Cell *cell, double deltaT) 
{
  // choose a random direction - values between -1 and 1    
  double x = 2*RandK::randk() - 1;
  double y = 2*RandK::randk() - 1;
	                             
  // scale to appropriate magnitude 
  double sf = m_dist / sqrt( x*x + y*y );
  SimPoint newpos = cell->getPosition() + SimPoint(x*sf, y*sf, 0);
  m_cells->addCell(m_typeIndex, newpos, m_flag);
  m_tap->update(m_id);
}
  

/************************************************************************
 * class ActionAdmitMult                                                *
 ************************************************************************/
ActionAdmitMult::ActionAdmitMult(int typeIndex, double dist, bool birth, 
	Cells *cells, Rate *pr) : m_typeIndex(typeIndex), m_dist(dist), 
	m_flag(birth), m_cells(cells), m_pr(pr)
{
  assert(m_typeIndex>=0); 
  assert(m_dist>0);
} 		

void ActionAdmitMult::doAction(Cell *cell, double deltaT) 
{
	int num_cells;

  // can't create fractional cells; truncate rate
  double n = m_pr->calculate(cell->getInternals()) * deltaT;
	double remainder = n - (int)n;
	
  double r = RandK::randk();	

	if (r < remainder)
		num_cells = (int)n+1;
	else
		num_cells = (int)n;

  // want to distribute new cells around this cell's position
  SimPoint pos = cell->getPosition();
  // first cell
  if (num_cells)
    m_cells->addCell(m_typeIndex, pos + SimPoint(m_dist,0,0), m_flag);

  // remaining cells
  double inc = 6.28 / n;		// (2*pi)/n
  for (int i=1; i<num_cells; i++)
  {
    double xoffset = m_dist*cos(i*inc);
    double yoffset = m_dist*sin(i*inc);
    m_cells->addCell(m_typeIndex, pos+SimPoint(xoffset,yoffset,0), m_flag);
  }
}
  

/************************************************************************
 * class ActionAdmitRand                                                *
 ************************************************************************/
ActionAdmitRand::ActionAdmitRand(int typeIndex, bool birth, 
	Cells *cells, Rate *pr) : m_typeIndex(typeIndex), 
	m_flag(birth), m_cells(cells), m_pr(pr)
{
  assert(m_typeIndex>=0); 
} 		

void ActionAdmitRand::doAction(Cell *cell, double deltaT) 
{
  int num_cells;
  // can't create fractional cells; truncate rate
  double n = m_pr->calculate(cell->getInternals()) * deltaT;
	double remainder = n - (int)n;
	
	if (RandK::randk() < remainder)
		num_cells = (int)n+1;
	else
		num_cells = (int)n;

  // Distribute randomly across whole volume
  for (int i=0; i<num_cells; i++)
  {
    double x = RandK::randk() * m_cells->getXRange();
    double y = RandK::randk() * m_cells->getYRange();
    double z = RandK::randk() * m_cells->getZRange();
    m_cells->addCell(m_typeIndex, SimPoint(x,y,z), m_flag);
  }
}


/************************************************************************
 * class ActionAdmitRand2D                                              *
 ************************************************************************/
ActionAdmitRand2D::ActionAdmitRand2D(int typeIndex, bool birth, 
	Cells *cells, Rate *pr) : m_typeIndex(typeIndex), 
	m_flag(birth), m_cells(cells), m_pr(pr)
{
  assert(m_typeIndex>=0); 
} 		

void ActionAdmitRand2D::doAction(Cell *cell, double deltaT) 
{
  int num_cells;
  // can't create fractional cells; truncate rate
  double n = m_pr->calculate(cell->getInternals()) * deltaT;
	double remainder = n - (int)n;
	
	if (RandK::randk() < remainder)
		num_cells = (int)n+1;
	else
		num_cells = (int)n;

  // want to distribute new cells around the entire grid
  for (int i=0; i<num_cells; i++)
  {
    double x = RandK::randk() * m_cells->getXRange();
    double y = RandK::randk() * m_cells->getYRange();
    double z = cell->getPosition().getZ();
    m_cells->addCell(m_typeIndex, SimPoint(x,y,z), m_flag);
  }
}


/************************************************************************
 * class ActionRecirculate                                              *
 ************************************************************************/
ActionRecirculate::ActionRecirculate(int typeIndex, bool birth, 
	Cells *cells) : m_typeIndex(typeIndex), m_flag(birth), m_cells(cells)
{
	assert(m_typeIndex >= 0);
}

void ActionRecirculate::doAction(Cell *cell, double deltaT) 
{
  // place cell in new position (with same z-coordinate)
  double x = RandK::randk() * m_cells->getXRange();
  double y = RandK::randk() * m_cells->getYRange();
  double z = RandK::randk() * m_cells->getZRange();

  cell->die();
	m_cells->addCell(m_typeIndex, SimPoint(x,y,z), m_flag);
}


/************************************************************************
 * class ActionRecirculate2D                                            *
 ************************************************************************/
ActionRecirculate2D::ActionRecirculate2D(int typeIndex, bool birth, 
	Cells *cells) : m_typeIndex(typeIndex), m_flag(birth), m_cells(cells)
{
	assert(m_typeIndex >= 0);
}

void ActionRecirculate2D::doAction(Cell *cell, double deltaT) 
{
  // place cell in new position (with same z-coordinate)
  double x = RandK::randk() * m_cells->getXRange();
  double y = RandK::randk() * m_cells->getYRange();
  double z = cell->getPosition().getZ();

  cell->die();
  m_cells->addCell(m_typeIndex, SimPoint(x,y,z), m_flag);
}

/************************************************************************
 * class ActionRecirculate2D0                                           *
 ************************************************************************/
ActionRecirculate2D0::ActionRecirculate2D0(int typeIndex, bool birth, 
	Cells *cells) : m_typeIndex(typeIndex), m_flag(birth), m_cells(cells)
{
	assert(m_typeIndex >= 0);
}

void ActionRecirculate2D0::doAction(Cell *cell, double deltaT) 
{
  // place cell at (0,0) (with same z-coordinate)
  cell->die();
  m_cells->addCell(m_typeIndex, SimPoint(0, 0, cell->getPosition().getZ()), m_flag);
}

/************************************************************************
 * class ActionAdmitGradient                                            *
 ************************************************************************/
ActionAdmitGradient::ActionAdmitGradient(int typeIndex, Molecule *pm, 
		double dist, bool birth, Cells *cells) : 
	Action(), m_typeIndex(typeIndex), m_pm(pm), m_dist(dist), m_flag(birth),
    		m_cells(cells) 
{ 
  assert(m_typeIndex>=0); 		
  m_tap = TallyActions::getInstance();
  m_id = m_tap->addName("ActionAdmitGradient"); 
} 	

void ActionAdmitGradient::doAction(Cell *cell, double deltaT) 
{
  SimPoint gradient = m_pm->getGradient(cell->getPosition(), m_dist);
  double mag = gradient.dist(SimPoint(0,0,0));
  if (mag)
  {
    // scale to appropriate magnitude
    double sf = m_dist / mag;
    SimPoint newpos = cell->getPosition() + gradient*sf;
    m_cells->addCell(m_typeIndex, newpos, m_flag);
  }
  else      // choose direction randomly
  {
    // choose a random direction - values between -1 and 1    
    double x = 2*RandK::randk() - 1;
    double y = 2*RandK::randk() - 1;
    double z = 2*RandK::randk() - 1;
                             
    // scale to appropriate magnitude 
    double sf = m_dist / sqrt( x*x + y*y + z*z );
    SimPoint newpos = cell->getPosition() + SimPoint(x*sf, y*sf, z*sf);
    m_cells->addCell(m_typeIndex, newpos, m_flag);
  }

  m_tap->update(m_id);
}
  

/************************************************************************
 * class ActionSecreteFixed                                             *
 ************************************************************************/
ActionSecreteFixed::ActionSecreteFixed(Molecule *field, double rate) : 
	m_field(field), m_rate(rate) 
{  assert(rate);  } 

void ActionSecreteFixed::doAction(Cell *cell, double deltaT)
{
  double amount = m_rate * deltaT;
  m_field->changeConc(amount, cell->getPosition());
}


/************************************************************************
 * class ActionSecreteVar                                               *
 ************************************************************************/
ActionSecreteVar::ActionSecreteVar(Molecule *field, int index) : 
	m_field(field), m_index(index) 
{} 

void ActionSecreteVar::doAction(Cell *cell, double deltaT)
{
  double amount = deltaT * cell->getValue(m_index);
  m_field->changeConc(amount, cell->getPosition());
}


/************************************************************************
 * class ActionSecreteBurst                                             *
 ************************************************************************/
ActionSecreteBurst::ActionSecreteBurst(Molecule *field, int index) : 
	m_field(field), m_index(index) 
{} 

void ActionSecreteBurst::doAction(Cell *cell, double deltaT)
{
  double amount = cell->getValue(m_index);
  m_field->changeConc(amount, cell->getPosition());
}


/************************************************************************
 * class ActionSecrete                                                  *
 ************************************************************************/
ActionSecrete::ActionSecrete(Rate * rateFunc, Molecule *field) :
          m_rateFunc(rateFunc), m_field(field) 
{}

void ActionSecrete::doAction(Cell *cell, double deltaT)
{
  double amount = m_rateFunc->calculate(cell->getInternals()) * deltaT;
  if (amount>0)
     m_field->changeConc(amount, cell->getPosition());
}


/************************************************************************
 * class ActionMoveChemotaxis                                           *
 ************************************************************************/
ActionMoveChemotaxis::ActionMoveChemotaxis(Molecule *source, double min,
		double radius) : 
	m_source(source), m_min(min), m_r(radius)
{ assert(source); }

void ActionMoveChemotaxis::doAction(Cell *cell, double deltaT) 
{
  double conc = m_source->getConc(cell->getPosition());
  double mag = 0;

  // check that concentration is greater than min
  if (conc >= m_min)
  {
    // check gradient, use for new orientation if nonzero
    SimPoint gradient = m_source->getGradient(cell->getPosition(), m_r);
    mag = gradient.dist(SimPoint(0,0,0));
    if (mag)
    {
      // scale to unit magnitude
      double sf = 1 / mag;
      cell->setDirection(gradient*sf);
    }
  }

  if ( (conc < m_min) || (mag == 0) ) 	// choose direction randomly
  {
    // choose a random direction - values between -1 and 1    
    double x = 2*RandK::randk() - 1;
    double y = 2*RandK::randk() - 1;
    double z = 2*RandK::randk() - 1;
	
    // scale to unit magnitude 
    double sf = 1 / sqrt( x*x + y*y + z*z );
    cell->setDirection(SimPoint(x*sf, y*sf, z*sf));
  }
}
  

/************************************************************************
 * class ActionMoveChemotaxis2D                                         *
 ************************************************************************/
ActionMoveChemotaxis2D::ActionMoveChemotaxis2D(Molecule *source, double min,
		double radius) : 
	m_source(source), m_min(min), m_r(radius)
{ assert(source); }

void ActionMoveChemotaxis2D::doAction(Cell *cell, double deltaT) 
{
  double conc = m_source->getConc(cell->getPosition());
  double mag = 0;

  // check that concentration is greater than min
  if (conc >= m_min)
  {
    // check gradient, use for new orientation if nonzero
    SimPoint gradient = m_source->getGradient(cell->getPosition(), m_r);
    assert(gradient.getZ()==0);

    mag = gradient.dist(SimPoint(0,0,0));
    if (mag)
    {
      // scale to unit magnitude
      double sf = 1 / mag;
      cell->setDirection(gradient*sf);
    }
  }
  if ( (conc < m_min) || (mag == 0) ) 	// choose direction randomly
  {
    // choose a random direction - values between -1 and 1    
    double x = 2*RandK::randk() - 1;
    double y = 2*RandK::randk() - 1;
	
    // scale to unit magnitude 
    double sf = 1 / sqrt( x*x + y*y );
    cell->setDirection(SimPoint(x*sf, y*sf, 0));
  }
}
  

/************************************************************************
 * class ActionBiasMoveChemotaxis2D                                     *
 ************************************************************************/
ActionBiasMoveChemotaxis2D::ActionBiasMoveChemotaxis2D(Molecule *source, double min,
		double radius, double bias) : 
	m_source(source), m_min(min), m_r(radius), m_bias(MIN(MAX(bias, 0), 1))
{ assert(source); }

void ActionBiasMoveChemotaxis2D::doAction(Cell *cell, double deltaT) 
{
  double conc = m_source->getConc(cell->getPosition());
  double mag = 0;
  double sf = 0;

  // check that concentration is greater than min
  if (conc >= m_min)
  {
    SimPoint new_vel, new_dir;

    // check gradient, use for new orientation if nonzero
    SimPoint gradient = m_source->getGradient(cell->getPosition(), m_r);
    mag = gradient.dist(SimPoint(0,0,0));
    
    if (mag)
    {
      sf = deltaT * m_bias / mag;
      gradient = gradient*sf;

      // choose a random direction - values between -1 and 1    
      double x = 0, x_total = 0;
      double y = 0, y_total = 0;
      for (int i=0; i<deltaT; i++)
      {
        x = 2*RandK::randk() - 1;
        y = 2*RandK::randk() - 1;
        sf = 1 / sqrt( x*x + y*y );
        x_total += x*sf;
        y_total += y*sf;
      }
      SimPoint dir = SimPoint(x_total, y_total, 0);
      dir = dir * (1-m_bias) * (1/dir.dist(SimPoint(0,0,0)));
	
			dir = dir + gradient;
      dir = dir * (1/dir.dist(SimPoint(0,0,0)));			

      cell->setDirection(dir);
    }
  }
  if ( (conc < m_min) || (mag == 0) ) 	// choose direction randomly
  {
    // choose a random direction - values between -1 and 1    
    double x = 2*RandK::randk() - 1;
    double y = 2*RandK::randk() - 1;
	
    // scale to unit magnitude 
    double sf = 1 / sqrt( x*x + y*y );
    cell->setDirection(SimPoint(x*sf, y*sf, 0));
  }
}
