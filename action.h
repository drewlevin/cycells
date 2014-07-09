
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
 * file action.h                                                        *
 * Declarations for virtual Action class and its derived classes	*
 * Each action object carries out a specific cell activity.		*
 ************************************************************************/

#ifndef ACTION_H
#define ACTION_H

class Cells;
class Cell;
class Molecule;
class Rate;
class TallyActions;

// virtual class
class Action {
  public:
    Action() {};
    virtual ~Action() {};   

    virtual void doAction(Cell *cell, double deltaT) = 0;

  protected:

  private:
    // not used
    Action(const Action &ra);
    //    Action operator = (const Action &ra);
};

// derived classes

class ActionComposite : public Action {
  public:
    ActionComposite(Action *pa1, Action *pa2) : m_pa1(pa1), m_pa2(pa2) {}; 		
    // copy constructor not used
    // use Action's destructor only - nothing else to delete         

    void doAction(Cell *cell, double deltaT) {
      m_pa1->doAction(cell, deltaT);
      m_pa2->doAction(cell, deltaT);
    };
  
  private:
    Action *m_pa1, *m_pa2;

    // not used
    ActionComposite(const ActionComposite &as);
    ActionComposite operator = (const ActionComposite &as);
};

// ActionDie
class ActionDie : public Action {
  public:
    explicit ActionDie();
    // copy constructor not used
    // use Action's destructor only - nothing else to delete         

    void doAction(Cell *cell, double deltaT);
  
  private:
    TallyActions *m_tap;	// object that tallies number of 'deaths'
    int m_id;			// id# to use with TallyAction object

    // not used
    ActionDie(const ActionDie &as);
    ActionDie operator = (const ActionDie &as);
};

// ActionInfect
// This function will check to see if the molecule concentration at the cell's
// location is enough to represent at least one molecule.  If so, the molecule
// will 'infect' the cell if the condition is satisfied, causing it to change 
// to the new cell type.
class ActionInfect : public Action {
  public:
    ActionInfect(Molecule *pm, int index, double radius); 
    // copy constructor not used
    // use Action's destructor only - nothing else to delete

    void doAction(Cell *cell, double deltaT);

  private:
    int m_index;   // type index of Cell's new CellType
    Molecule *m_pm;  // Molecule that will infect the cell
    double m_radius;
    TallyActions *m_tap;	// object that tallies number of 'deaths'
    int m_id;			// id# to use with TallyAction object

    // not used
    ActionInfect(const ActionInfect &as);
    ActionInfect operator = (const ActionInfect &as);
};

// ActionChange
// This function is designed to implement cell differentiation, activation,
// or other 'type' change.  It is potentially dangerous; a primary difference
// between different CellTypes is that they interpret a Cell's internal values
// differently.  It is up to the user to ensure that the source and target
// types involved in a Change share the same attributes, or at least both
// have all the same attributes, even if they are only used by one of the
// CellTypes.  The routine below does not actually know anything about
// CellTypes, and simply changes the type index of the Cell passed in.
class ActionChange : public Action {
  public:
    ActionChange(int index); 
    // copy constructor not used
    // use Action's destructor only - nothing else to delete

    void doAction(Cell *cell, double deltaT);

  private:
    int m_index;                   // type index of Cell's new CellType
    TallyActions *m_tap;	// object that tallies number of 'deaths'
    int m_id;			// id# to use with TallyAction object

    // not used
    ActionChange(const ActionChange &as);
    ActionChange operator = (const ActionChange &as);
};

class ActionChangeIndex : public Action {
  public:
    ActionChangeIndex(int cellindex, Cells *cells); 
    // copy constructor not used
    // use Action's destructor only - nothing else to delete

    void doAction(Cell *cell, double deltaT);

  private:
    int m_cellindex;                   // type index of Cell's new CellType
    TallyActions *m_tap;	// object that tallies number of 'deaths'
    int m_id;			// id# to use with TallyAction object
    Cells *m_cells;  // access to getNeighbors

    // not used
    ActionChangeIndex(const ActionChange &as);
    ActionChangeIndex operator = (const ActionChange &as);
};

// ActionMoveRandomly
// from FisherLauffenburgerDaniele88:
// random cell movement is described by cell speed and persistence time, where
// the latter is the average length of time between changes in direction.  
// This function chooses a new direction randomly.
// Condition for calling this should be a probability of deltaT/persistance time
class ActionMoveRandomly : public Action {
  public:
    ActionMoveRandomly() : Action() {};
    // copy constructor not used
    // use Action's destructor 

    void doAction(Cell *cell, double deltaT);
  
  private:

    // not used
    ActionMoveRandomly(const ActionMoveRandomly &as);
    ActionMoveRandomly operator = (const ActionMoveRandomly &as);
};

// ActionMoveRandomly2D
// This is the same as ActionMoveRandomly, but with movement in the
// z direction always set to 0.
class ActionMoveRandomly2D : public Action {
  public:
    ActionMoveRandomly2D() : Action() {}; 		
    // copy constructor not used
    // use Action's destructor 

    void doAction(Cell *cell, double deltaT);
  
  private:

    // not used
    ActionMoveRandomly2D(const ActionMoveRandomly2D &as);
    ActionMoveRandomly2D operator = (const ActionMoveRandomly2D &as);
};


// ActionTurnRandomly
// from FisherLauffenburgerDaniele88:
// random cell movement is described by cell speed and persistence time, where
// the latter is the average length of time between changes in direction.  
// This function chooses a new direction randomly.
// Condition for calling this should be a probability of deltaT/persistance time
class ActionTurnRandomly : public Action {
  public:
    ActionTurnRandomly(double std);
    // copy constructor not used
    // use Action's destructor 

    void doAction(Cell *cell, double deltaT);
  
  private:
		double m_std;

    // not used
    ActionTurnRandomly(const ActionTurnRandomly &as);
    ActionTurnRandomly operator = (const ActionTurnRandomly &as);
};

// ActionTurnRandomly2D
// This is the same as ActionTurnRandomly, but with movement in the
// z direction always set to 0.
class ActionTurnRandomly2D : public Action {
  public:
    ActionTurnRandomly2D(double std); 		
    // copy constructor not used
    // use Action's destructor 

    void doAction(Cell *cell, double deltaT);
  
  private:
		double m_std;

    // not used
    ActionTurnRandomly2D(const ActionTurnRandomly2D &as);
    ActionTurnRandomly2D operator = (const ActionTurnRandomly2D &as);
};

// ActionDivide replaces the cell passed in with two new cells.  The
// new cells may be of a different type, to allow for division with 
// differentiation or to distinguish between cycling and noncycling cells.
// Positions are offset by a small amount arbitrarily added to the x position.
class ActionDivide : public Action {
  public:
    ActionDivide(Cells *cells, int typeIndex); 
    // copy constructor not used
    // use Action's destructor only - nothing else to delete         

    void doAction(Cell *cell, double deltaT);
  
  private:
    Cells *m_cells;
    int m_typeIndex;		// specifies type of daughter cells
    TallyActions *m_tap;
    int m_id;

    // not used
    ActionDivide(const ActionDivide &as);
    ActionDivide operator = (const ActionDivide &as);
};


// ActionAdmit 'creates' a single cell of the type specified; this
// represents migration from circulation (or some other unmodeled compartment).
// The new cell is placed at the specified distance from this cell's center
// in a random direction.
class ActionAdmit : public Action {
  public:
    ActionAdmit(int typeIndex, double dist, bool birth, Cells *cells);
    // copy constructor not used
    // use Action's destructor only - don't want to delete CellType! 

    void doAction(Cell *cell, double deltaT);
  
  private:
    int m_typeIndex;		// identifies cell type to add
    double m_dist;		// offset distance 
    bool m_flag;		// birth flag - which initialization to use
    Cells *m_cells;
    TallyActions *m_tap;
    int m_id;

    // not used
    ActionAdmit(const ActionAdmit &as);
    ActionAdmit operator = (const ActionAdmit &as);
};


class ActionAdmit2D : public Action {
  public:
    ActionAdmit2D(int typeIndex, double dist, bool birth, Cells *cells);
    // copy constructor not used
    // use Action's destructor only - don't want to delete CellType! 

    void doAction(Cell *cell, double deltaT);
  
  private:
    int m_typeIndex;		// identifies cell type to add
    double m_dist;		// offset distance 
    bool m_flag;		// birth flag - which initialization to use
    Cells *m_cells;
    TallyActions *m_tap;
    int m_id;

    // not used
    ActionAdmit2D(const ActionAdmit2D &as);
    ActionAdmit2D operator = (const ActionAdmit2D &as);
};


// AdmitMult
// This version admits multiple cells of the type specified
// Really designed for release of intracellular pathogens when host cell dies.
class ActionAdmitMult : public Action {
  public:
    ActionAdmitMult(int typeIndex, double dist, bool birth, Cells *cells, Rate *pr);
    // copy constructor not used
    // use Action's destructor only - don't want to delete CellType! 

    void doAction(Cell *cell, double deltaT);
  
  private:
    int m_typeIndex;		// identifies cell type to add
    double m_dist;		// distance from original cell to put new cells
    bool m_flag;		// initialize or randomize?
    Cells *m_cells;
    Rate *m_pr;

    // not used
    ActionAdmitMult(const ActionAdmitMult &as);
    ActionAdmitMult operator = (const ActionAdmitMult &as);
};

// AdmitRand
// This version admits multiple cells of the type specified and places them
// uniformly throughout the entire simulation space.
class ActionAdmitRand : public Action {
  public:
    ActionAdmitRand(int typeIndex, bool birth, Cells *cells, Rate *pr);
    // copy constructor not used
    // use Action's destructor only - don't want to delete CellType! 

    void doAction(Cell *cell, double deltaT);
  
  private:
    int m_typeIndex;		// identifies cell type to add
    bool m_flag;		// initialize or randomize?
    Cells *m_cells;
    Rate *m_pr;

    // not used
    ActionAdmitRand(const ActionAdmitMult &as);
    ActionAdmitRand operator = (const ActionAdmitMult &as);
};

// AdmitRand2D
// This version admits multiple cells of the type specified and places them
// uniformly throughout the entire simulation space on the same z plane as
// the action cell.
class ActionAdmitRand2D : public Action {
  public:
    ActionAdmitRand2D(int typeIndex, bool birth, Cells *cells, Rate *pr);
    // copy constructor not used
    // use Action's destructor only - don't want to delete CellType! 

    void doAction(Cell *cell, double deltaT);
  
  private:
    int m_typeIndex;		// identifies cell type to add
    bool m_flag;		// initialize or randomize?
    Cells *m_cells;
    Rate *m_pr;

    // not used
    ActionAdmitRand2D(const ActionAdmitMult &as);
    ActionAdmitRand2D operator = (const ActionAdmitMult &as);
};

// ActionAdmitGradient 'creates' a single cell of the type specified; this
// represents migration from circulation (or some other unmodeled compartment).
// The new cell is placed at the specified distance from this cell's center,
// with the offset chosen in the direction of the gradient of a specified
// Molecule (or randomly if gradient is 0).
class ActionAdmitGradient : public Action {
  public:
    ActionAdmitGradient(int typeIndex, Molecule *pm, double dist, bool birth, 
		    Cells *cells);
    // copy constructor not used
    // use Action's destructor only - don't want to delete CellType! 

    void doAction(Cell *cell, double deltaT);
  
  private:
    int m_typeIndex;		// identifies cell type to add
    Molecule *m_pm;		// pointer to Molecule for gradient access
    double m_dist;		// offset distance 
    bool m_flag;		// birth flag - which initialization to use
    Cells *m_cells;
    TallyActions *m_tap;
    int m_id;

    // not used
    ActionAdmitGradient(const ActionAdmitGradient &as);
    ActionAdmitGradient operator = (const ActionAdmitGradient &as);
};

// Recirculate
// This simulates the cell leaving and reentering the simulation
// at a new random point (keeping its z coordinate the same).
class ActionRecirculate : public Action {
  public:
    ActionRecirculate(int typeIndex, bool birth, Cells *cells);
    // copy constructor not used
    // use Action's destructor only - don't want to delete CellType! 

    void doAction(Cell *cell, double deltaT);
  
  private:
    int m_typeIndex;		// identifies cell type to add
    bool m_flag;		// initialize or randomize?
    Cells *m_cells;

    // not used
    ActionRecirculate(const ActionRecirculate &as);
    ActionRecirculate operator = (const ActionRecirculate &as);
};

// Recirculate2D
// This simulates the cell leaving and reentering the simulation
// at a new random point (keeping its z coordinate the same).
class ActionRecirculate2D : public Action {
  public:
    ActionRecirculate2D(int typeIndex, bool birth, Cells *cells);
    // copy constructor not used
    // use Action's destructor only - don't want to delete CellType! 

    void doAction(Cell *cell, double deltaT);
  
  private:
    int m_typeIndex;		// identifies cell type to add
    bool m_flag;		// initialize or randomize?
    Cells *m_cells;

    // not used
    ActionRecirculate2D(const ActionRecirculate2D &as);
    ActionRecirculate2D operator = (const ActionRecirculate2D &as);
};

// Recirculate2D0
// This simulates the cell leaving and reentering the simulation
// at a location not explicitly represented by the simulation.  The
// cell is relocated at x,y = (0,0) to essentially place it out of
// the way (a bit of a hack).
class ActionRecirculate2D0 : public Action {
  public:
    ActionRecirculate2D0(int typeIndex, bool birth, Cells *cells);
    // copy constructor not used
    // use Action's destructor only - don't want to delete CellType! 

    void doAction(Cell *cell, double deltaT);
  
  private:
    int m_typeIndex;		// identifies cell type to add
    bool m_flag;		// initialize or randomize?
    Cells *m_cells;

    // not used
    ActionRecirculate2D0(const ActionRecirculate2D0 &as);
    ActionRecirculate2D0 operator = (const ActionRecirculate2D0 &as);
};

// ActionSecreteFixed implements constitutive secretion of some molecule at
// a fixed rate.  
class ActionSecreteFixed : public Action {   
  public:
    ActionSecreteFixed(Molecule *field, double rate); 
    // copy constructor not used
    // use Action's destructor only - don't want to delete Molecule!

    void doAction(Cell *cell, double deltaT);

  private:
    Molecule * m_field;
    double m_rate;

    // not used
    ActionSecreteFixed(const ActionSecreteFixed &as);
    ActionSecreteFixed operator = (const ActionSecreteFixed &as);
};

// ActionSecreteVar implements constitutive secretion of some molecule at
// a rate determined by some internal cell variable.  
class ActionSecreteVar : public Action {   
  public:
    ActionSecreteVar(Molecule *field, int index); 
    // copy constructor not used
    // use Action's destructor only - don't want to delete Molecule!

    void doAction(Cell *cell, double deltaT);

  private:
    Molecule * m_field;
    int m_index;

    // not used
    ActionSecreteVar(const ActionSecreteVar &as);
    ActionSecreteVar operator = (const ActionSecreteVar &as);
};

// ActionSecreteBurst implements secretion of a fixed amount - determined
// by some internal cell value -- of some molecule 
class ActionSecreteBurst : public Action {   
  public:
    ActionSecreteBurst(Molecule *field, int index); 
    // copy constructor not used
    // use Action's destructor only - don't want to delete Molecule!

    void doAction(Cell *cell, double deltaT);

  private:
    Molecule * m_field;
    int m_index;

    // not used
    ActionSecreteBurst(const ActionSecreteBurst &as);
    ActionSecreteBurst operator = (const ActionSecreteBurst &as);
};


// ActionSecrete implements constitutive secretion of some molecule at
// a rate dependent on Cell variables.  Burst secretion, since it would
// be independent of the timestep size, should be handled separately.
class ActionSecrete : public Action {
  public:
    //--------------------------- CREATORS ---------------------------------
    ActionSecrete(Rate * rateFunc, Molecule *field);
    // copy constructor not used
    // use Action's destructor only - don't want to delete Molecule!

    void doAction(Cell *cell, double deltaT);

  private:
    Rate *m_rateFunc;
    Molecule * m_field;

    // not used
    ActionSecrete(const ActionSecrete &as);
    ActionSecrete operator = (const ActionSecrete &as);
};

// Chemotaxis is described by cell speed and persistence time, as for random 
// motion, but the direction is determined by the spatial gradient of some
// molecular substance.  Here, the direction is chosen to match the 
// direction of the sensed gradient; the 'chemotactic index' used in 
// FisherLauffenburgerDaniele88 is currently not used here.
class ActionMoveChemotaxis : public Action {
  public:
    ActionMoveChemotaxis(Molecule *source, double min, double radius); 
    // copy constructor not used
    // use Action's destructor 

    void doAction(Cell *cell, double deltaT);
  
  private:
    Molecule *m_source;         // molecule type we're tracking
    double m_min;		// min concentration for chemotaxis
    double m_r;			// radius of cell type (need for getGradient)

    // not used
    ActionMoveChemotaxis(const ActionMoveChemotaxis &as);
    ActionMoveChemotaxis operator = (const ActionMoveChemotaxis &as);
};

class ActionMoveChemotaxis2D : public Action {
  public:
    ActionMoveChemotaxis2D(Molecule *source, double min, double radius); 
    // copy constructor not used
    // use Action's destructor 

    void doAction(Cell *cell, double deltaT);
  
  private:
    Molecule *m_source;         // molecule type we're tracking
    double m_min;		// min concentration for chemotaxis
    double m_r;			// radius of cell type (need for getGradient)

    // not used
    ActionMoveChemotaxis2D(const ActionMoveChemotaxis2D &as);
    ActionMoveChemotaxis2D operator = (const ActionMoveChemotaxis2D &as);
};

// Same as ActionMoveChemotaxis, but with z direction always set to 0.
class ActionBiasMoveChemotaxis2D : public Action {
  public:
    ActionBiasMoveChemotaxis2D(Molecule *source, double min, double radius, double bias); 
    // copy constructor not used
    // use Action's destructor 

    void doAction(Cell *cell, double deltaT);
  
  private:
    Molecule *m_source;         // molecule type we're tracking
    double m_min;		// min concentration for chemotaxis
    double m_r;			// radius of cell type (need for getGradient)
    double m_bias;

    // not used
    ActionBiasMoveChemotaxis2D(const ActionBiasMoveChemotaxis2D &as);
    ActionBiasMoveChemotaxis2D operator = (const ActionBiasMoveChemotaxis2D &as);
};

#endif

